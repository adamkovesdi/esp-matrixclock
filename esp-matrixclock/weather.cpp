#include "weather.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char *weatherHost = "api.openweathermap.org";
const char *weatherLang = "&lang=en";

WiFiClient client;
float temp, windspeed;
int winddir;
String iconid;

int getWinddir()
{
	if(winddir<45) return 1;
	if(winddir<90) return 2;
	if(winddir<135) return 3;
	if(winddir<180) return 4;
	if(winddir<225) return 5;
	if(winddir<270) return 6;
	if(winddir<315) return 7;
	else return 1;
}

int getWindspeed()
{
	// Beaufort scale converter
	if(windspeed<1) return 0;
	if(windspeed<6) return 1;
	if(windspeed<12) return 2;
	if(windspeed<20) return 3;
	if(windspeed<29) return 4;
	if(windspeed<39) return 5;
	if(windspeed<50) return 6;
	if(windspeed<62) return 7;
	if(windspeed>=62) return 8;
}

int getWeatherIcon()
{
	switch(iconid[0])
	{
		case '0':
			if(iconid[1]=='1') return 1;
			if(iconid[1]=='2') return 2;
			if(iconid[1]=='3') return 3;
			if(iconid[1]=='4') return 4;
			if(iconid[1]=='9') return 5;
			break;
		case '1':
			if(iconid[1]=='0') return 6;
			if(iconid[1]=='1') return 7;
			if(iconid[1]=='3') return 8;
			break;
		case '5':
			return 9;
			break;
	}
	return 0;
}

int getTemp()
{
	return (int)temp;
}

void getWeatherData(const char *weatherKey, const char* cityID)
{
	Serial.println(String("GET /data/2.5/weather?id=") + cityID + "&units=metric&appid=" + weatherKey + weatherLang);
	if (client.connect(weatherHost, 80))
	{
		client.println(String("GET /data/2.5/weather?id=") + cityID + "&units=metric&appid=" + weatherKey + weatherLang + "\r\n" +
				"Host: " + weatherHost + "\r\nUser-Agent: ArduinoWiFi/1.1\r\n" +
				"Connection: close\r\n\r\n");
	} else {
		Serial.println("connection failed");
		return;
	}
	String line;
	/* this code needs to be revised, it's blocking */
	int repeatCounter = 0;
	while (!client.available() && repeatCounter < 10) {
		delay(500);
		Serial.println("w.");
		repeatCounter++;
	}
	/* end of problem code */
	while (client.connected() && client.available()) {
		Serial.print("c");
		char c = client.read(); 
		if (c == '[' || c == ']') c = ' ';
		line += c;
	}
	Serial.print("Response :");
	Serial.println(line);

	client.stop();

	DynamicJsonBuffer jsonBuf;
	JsonObject &root = jsonBuf.parseObject(line);
	if (!root.success())
	{
		Serial.println("parseObject() failed");
		return;
	}
	temp = root["main"]["temp"];
	iconid = root["weather"]["icon"].as<String>();
	windspeed = root["wind"]["speed"];
	winddir = root["wind"]["deg"];
	Serial.print("w");

	// unused data
	// -----------------
	// humidity = root["main"]["humidity"];
	// pressure = root["main"]["pressure"];
	// clouds = root["clouds"]["all"];
}
