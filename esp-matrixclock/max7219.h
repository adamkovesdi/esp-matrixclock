#ifndef _MAX7219_H
#define _MAX7219_H

#include <Arduino.h>

#define NUM_MAX			4
#define DIN_PIN			15  // D8
#define CS_PIN		  13  // D7
#define CLK_PIN			12  // D6

// MAX7219 functions by Pawel A. Hernik
// MAX7219 commands:
#define CMD_NOOP   0
#define CMD_DIGIT0 1
#define CMD_DIGIT1 2
#define CMD_DIGIT2 3
#define CMD_DIGIT3 4
#define CMD_DIGIT4 5
#define CMD_DIGIT5 6
#define CMD_DIGIT6 7
#define CMD_DIGIT7 8
#define CMD_DECODEMODE  9
#define CMD_INTENSITY   10
#define CMD_SCANLIMIT   11
#define CMD_SHUTDOWN    12
#define CMD_DISPLAYTEST 15

#define SETBIT(theport,thebit) ((theport) |= (1<<thebit))
#define CLEARBIT(theport,thebit) ((theport) &= (~(1<<thebit)))

void sendCmd(int addr, byte cmd, byte data);
void sendCmdAll(byte cmd, byte data);
// void refresh(int addr);
void refreshAll() ;

void clr();
void initMAX7219();

void setPixel(unsigned int x, unsigned int y, boolean value);

#endif
