/*
 * ESP8266 driven matrix clock with weather
 * (c)2016 by Adam Kovesdi
 * version 2
 *
 * TODO: eliminate delays from display code 
 * TODO: improvements 
 *
 */

#define MYSSID			"changeme"		// network SSID
#define MYPASS			"meeto"				// WiFi PSK
#define WEATHERKEY	"yourapikey"	// openweathermaps API key
#define CITYID			"yourcity"		// openweathermaps city ID

// comment out this credentials.h include if you set the above
#include "credentials.h"

#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "fonts.h"
#include "max7219.h"
#include "display.h"
#include "weather.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

uint8_t hour, minute, second;

void setup(){
	initMAX7219();
	drawString(0,font," Conn...");
  WiFi.begin(MYSSID, MYPASS);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }
  timeClient.begin();
	drawString(0,font,"link up");
	timeClient.setTimeOffset(3600);
	getWeatherData(WEATHERKEY, CITYID);
}

void loop() {
  timeClient.update();
	hour=timeClient.getHours();
	minute=timeClient.getMinutes();
	second=timeClient.getSeconds();
	draw_clock(hour,minute,second);
	delay(100);

  delay(4000);

	int t=getTemp();
	char buf[10], *string;
	sprintf(buf,"%dC",t);
	drawString(0,font,buf);
	drawChar(24,weather_icons,getWeatherIcon());
	drawChar(18,winddir_icons,getWinddir());
	for(int i=0;i<getWindspeed();i++) setPixel(16+i,7,true);
	refreshAll();

  delay(4000);
}


