/*
 * ESP8266 driven matrix clock with weather
 * (c)2016 by Adam Kovesdi
 * version 2
 *
 * TODO: detect & handle lost network connection
 * TODO: detect & handle invalid weather data 
 * TODO: improvements 
 *
 */

// set these to your credentials (otherwise it will use mine - not included)

// #define MYSSID			"changeme"		// network SSID
// #define MYPASS			"meeto"				// WiFi PSK
// #define WEATHERKEY	"yourapikey"	// openweathermaps API key
// #define CITYID			"yourcity"		// openweathermaps city ID

#ifndef MYSSID
#include "credentials.h"
#endif

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

unsigned long lastwupdate=0;		// last weather update EPOCH timestamp
#define WEATHER_UPDATEINTERVAL		120 // in seconds

void refresh_weather()
{
	timeClient.update();
	if(timeClient.getEpochTime() > (lastwupdate+WEATHER_UPDATEINTERVAL))
	{
		lastwupdate=timeClient.getEpochTime();
		getWeatherData(WEATHERKEY, CITYID);
	}
}

void display_weather()
{
	refresh_weather();
	clr();
	int t=getTemp();
	char buf[6], *string;
	sprintf(buf,"%dC",t);
	drawString(0,font,buf);
	drawChar(24,weather_icons,getWeatherIcon());
	drawChar(18,winddir_icons,getWinddir());
	for(int i=0;i<getWindspeed();i++) setPixel(16+i,7,true);
	refreshAll();
}

void dispay_clock()
{
	timeClient.update();
	draw_clock(timeClient.getHours(),timeClient.getMinutes(),timeClient.getSeconds());
}

void setup()
{
	initMAX7219();
	drawString(0,font," Conn...");
	WiFi.begin(MYSSID, MYPASS);
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
	}
	timeClient.begin();
	drawString(0,font,"link up");
	timeClient.setTimeOffset(3600);
}

void loop()
{
	timeClient.update();
	uint8_t	timeslice=timeClient.getEpochTime() % 10;
	if ((timeslice >4) && (timeslice <8))
	{
		display_weather();
	}
	else
	{
		dispay_clock();
	}
	delay(100);
}


