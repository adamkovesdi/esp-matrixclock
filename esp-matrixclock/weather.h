#ifndef _WEATHER_H
#define _WEATHER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

int getWinddir();
int getWindspeed();
int getWeatherIcon();
int getTemp();

void getWeatherData(const char*, const char*);

#endif
