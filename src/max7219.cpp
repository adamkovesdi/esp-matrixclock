#include "max7219.h"

uint8_t scr[NUM_MAX*8];
void sendCmd(int addr, byte cmd, byte data)
{
  digitalWrite(CS_PIN, LOW);
  for (int i = NUM_MAX-1; i>=0; i--) {
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, i==addr ? cmd : 0);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, i==addr ? data : 0);
  }
  digitalWrite(CS_PIN, HIGH);
}

void sendCmdAll(byte cmd, byte data)
{
  digitalWrite(CS_PIN, LOW);
  for (int i = NUM_MAX-1; i>=0; i--) {
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, cmd);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
  }
  digitalWrite(CS_PIN, HIGH);
}
/*
void refresh(int addr) {
  for (int i = 0; i < 8; i++)
    sendCmd(addr, i + CMD_DIGIT0, scr[addr * 8 + i]);
}
*/

void refreshAll() {
  for (int c = 0; c < 8; c++) {
    digitalWrite(CS_PIN, LOW);
    for(int i=NUM_MAX-1; i>=0; i--) {
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, scr[i * 8 + c]);
    }
    digitalWrite(CS_PIN, HIGH);
 }
}

void clr()
{
  for (int i = 0; i < NUM_MAX*8; i++) scr[i] = 0;
}

void initMAX7219()
{
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  sendCmdAll(CMD_DISPLAYTEST, 0);
  sendCmdAll(CMD_SCANLIMIT, 7);
  sendCmdAll(CMD_DECODEMODE, 0);
  sendCmdAll(CMD_INTENSITY, 1);
  sendCmdAll(CMD_SHUTDOWN, 0);
  clr();
  refreshAll();
  sendCmdAll(CMD_SHUTDOWN,1);
  sendCmdAll(CMD_INTENSITY,6);
}

#define SETBIT(theport,thebit) ((theport) |= (1<<thebit))
#define CLEARBIT(theport,thebit) ((theport) &= (~(1<<thebit)))

void setPixel(unsigned int x, unsigned int y, boolean value)
{
	// hardware dependent pixel buserator by adamkov
	unsigned int bte,bit;

#ifdef OLDTYPE_MATRIX
	// use this for the old type green circuit board matrix (2017 version) (input connectors at seconds side)
	bte=(3-(byte)(x/8))*8+y;
	bit=7-((byte)(x%8));
#else
	// use this for the new type blue circuit board matrix (bought in 2019) (input connectors at hour side)
	bte=((byte)(x/8))*8+y;
	bit=7-((byte)(x%8));
#endif

	if(value)SETBIT(scr[bte],bit);
	else CLEARBIT(scr[bte],bit);
}

