#include "weather.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *weatherHost = "http://api.openweathermap.org";
const char *weatherLang = "&lang=en";

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
	if(winddir<361) return 1;
	else return 0; // no wind I suppose
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
	return 0;
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
	String url = String(weatherHost) + "/data/2.5/weather?id=" + cityID + "&units=metric&appid=" + weatherKey + weatherLang;
	String line;
	// Serial.println(String("GET " + url)); // debug info

	if (WiFi.status() == WL_CONNECTED) // Check WiFi connection status
	{
		HTTPClient http;  // Declare an object of class HTTPClient
		http.begin(url);  // Specify request destination
		int httpCode = http.GET(); //Send the request
		if (httpCode > 0) // Check the returning code
		{
			line = http.getString();   // Get the request response payload
		}
		else
		{
			Serial.println("HTTP response code is no good");
			http.end();
			return;
		}
		http.end();   //Close connection
		// Serial.print("Response :"); Serial.println(line); // debug info
	}
	else
	{
		Serial.println("Wifi connection failed");
		return;
	}

	DynamicJsonBuffer jsonBuf;
	JsonObject &root = jsonBuf.parseObject(line);
	if (!root.success())
	{
		Serial.println("parseObject() failed");
		return;
	}
	temp = root["main"]["temp"];
	iconid = root["weather"][0]["icon"].as<String>();
	windspeed = root["wind"]["speed"];
	winddir = root["wind"]["deg"];
	Serial.println("Received weather data");

	// unused data
	// -----------------
	// humidity = root["main"]["humidity"];
	// pressure = root["main"]["pressure"];
	// clouds = root["clouds"]["all"];
}
