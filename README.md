# Dot matrix clock with weather and NTP

This is my dot matrix clock made with ESP8266 WiFi capable MCU. Accurate time signal is acquired from NTP and weather information is available through Openweathermap.org API.

![esp-matrixclock](pictures/clock.jpg)

## Features
- 24 hour time display
- NTP sync
- Optional weather data from Openweathermap.org API
- Outside temperature display
- Wind speed display
- Wind direction display
- DST support (automatic change)
- Over the Air (OTA) firmware upgrade capability
- Serially configurable wifi credentials 

## Prerequisites
- ESP8266 board (recommended: NodeMCU/compatible see BOM)
- MAX7219 based LED matrix display (order from China)
- *Openweathermap account (optional)*
- [PlatformIO](https://platformio.org)

## Time display screen
![esp-matrixclock](pictures/clock-time.png)

## Weather display screen
Current weather is displayed 3 times per minute for 4 seconds.

![esp-matrixclock](pictures/clock-weather.png)

## Build & Installation HOWTO

### Hardware BOM

- [NodeMCU v3 board](http://www.banggood.com/Geekcreit-Doit-NodeMcu-Lua-ESP8266-ESP-12E-WIFI-Development-Board-p-985891.html)
- [MAX7219 based LED matrix](https://www.banggood.com/MAX7219-Dot-Matrix-Module-4-in-1-Display-For-Arduino-p-1072083.html)
- Micro usb to USB cable
- Female-female dupont cable 5pcs (usually comes with the display)

### Wiring between NodeMCU and matrix board

```
NodeMCU 3.3V -> Matrix Vcc
NodeMCU GND  -> Matrix GND
NodeMCU D8   -> Matrix DIN
NodeMCU D7   -> Matrix CS
NodeMCU D6   -> Matrix CLK
```

### Software installation

- Download and install [PlatformIO](https://platformio.org)
- Optionally read https://docs.platformio.org/en/latest/quickstart.html

PlatformIO automatically downloads all required libraries, boards, and configures your environment.

Optional steps for weather info functionality

- Openweathermap: [http://openweathermap.org/](http://openweathermap.org/) 
	- Register an account
	- Get your API key at: [https://home.openweathermap.org/api_keys](https://home.openweathermap.org/api_keys) 
	- Find your location/city id on here: [https://openweathermap.org/find?q=](https://openweathermap.org/find?q=) 

- Changes in file *main.cpp* needed for weather functionality
	- Add your api key from openweathermap: uncomment define WEATHERKEY
	- Add your city id from same
	- Save file

### Uploading Firmware to ESP8266 module

PlatformIO serial
```
platformio run --target upload
```

PlatformIO OTA
```
platformio run -t upload --upload-port <IP address of ESP>
```

### Wifi Configuration

- If the clock fails to connect to an AP it will ask for credentials
- Run serial monitor (Arduino IDE) or minicom/putty, etc at 9600 bps
- Type in your own Wifi credentials

## Future plans

- Openweathermap API keys to EEPROM
- Force configuration mode (button/jumper, etc)

## Special thanks

- Vajk for beta testing & original HOWTO
- [William Moeur](https://github.com/moeur) for NTP code

