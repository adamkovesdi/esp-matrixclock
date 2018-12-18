# Dot matrix clock with weather and NTP

This is my dot matrix clock made with ESP8266 WiFi capable MCU. Accurate time signal is acquired from NTP and weather information is available through Openweathermap.org API.

The firmware should be compiled on your computer using Arduino IDE and then uploaded to the ESP module. This is not a trivial task but there is a HOWTO section to make it easier with a step-by-step tutorial.

![esp-matrixclock](clock.jpg)

## Features
- 24 hour time display
- NTP sync
- Optional weather data from Openweathermap.org API
- Outside temperature display
- Wind speed display
- Wind direction display
- DST support (automatic change)
- Serially configurable wifi credentials 


## Prerequisites
- ESP8266 board (recommended: NodeMCU/compatible see HOWTO)
- MAX7219 based LED matrix display (order from China)
- Openweathermap account
- Arduino IDE + libraries (see below)

## Time display screen
![esp-matrixclock](pictures/clock-time.png)

## Weather display screen
Current weather is displayed 3 times per minute for 4 seconds.

![esp-matrixclock](pictures/clock-weather.png)

## Installation HOWTO

Updated from the previous version (courtesy of Vajk)

### Wiring between NodeMCU and matrix board

- NodeMCU 3.3V	-> Matrix Vcc
- NodeMCU GND		-> Matrix GND
- NodeMCU D8		-> Matrix DIN
- NodeMCU D7		-> Matrix CS
- NodeMCU D6		-> Matrix CLK

### Software installation

- Download & install latest Arduino IDE [https://www.arduino.cc/en/main/software](https://www.arduino.cc/en/main/software) 
- In Arduino IDE File, Preferences: Additional Boards Manager URLs: [http://arduino.esp8266.com/stable/package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json) 
- Tools/Manage Libraries: Search for ArduinoJSON by bblanchon install version 5 (NOT 6!)
- NTP Client lib is no longer a dependency (courtesy of @moeur)

Optional steps for weather info

- Openweathermap: [http://openweathermap.org/](http://openweathermap.org/) 
	- Register an account
	- Get your API key at: [https://home.openweathermap.org/api_keys](https://home.openweathermap.org/api_keys) 
	- Find your location/city id on here: [https://openweathermap.org/find?q=](https://openweathermap.org/find?q=) 

- Changes in file esp-matrixclock.ino needed for weather functionality
	- Add your api key from openweathermap
	- Add your city id from same
	- Save file

### Uploading

	- Tools, Board: select ESP8266 generic module
	- Tools, Port: select COM port
	- Tools, Reset method: set to NodeMCU
	- Click upload (arrow button below menu bar on the upper left)

### Configuration

	- If the clock fails to connect to an AP it will ask for credentials
	- Run serial monitor (Arduino IDE) or minicom/putty, etc at 9600 bps
	- Type in Wifi configuration

### Hardware BOM

- [NodeMCU v3 board](http://www.banggood.com/Geekcreit-Doit-NodeMcu-Lua-ESP8266-ESP-12E-WIFI-Development-Board-p-985891.html)
- [MAX7219 based LED matrix](https://www.banggood.com/MAX7219-Dot-Matrix-Module-4-in-1-Display-For-Arduino-p-1072083.html)
- Micro usb cable
- Female-female dupont cable 5pcs (usually comes with the display)


## Special thanks

- Vajk for beta testing
- [William Moeur](https://github.com/moeur) for NTP code improvements and credentials config

## Future plans

- Openweathermap API keys to EEPROM
- Force configuration mode (button/jumper, etc)
