#include "display.h"

void draw_font4x7(uint8_t column, uint8_t number) {
	// Draw a digit on the canvas at position specified by column
	uint8_t i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<8;j++) {
			uint8_t val;
			val=(pgm_read_byte(&font4x7[number][i])) & (1<<j);
			setPixel(i+column,j,val);
		}
	}
}

void draw_font4x8(uint8_t column, uint8_t number) {
	// Draw a digit on the canvas at position specified by column
	uint8_t i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<8;j++) {
			uint8_t val;
			val=(pgm_read_byte(&font4x8[number][i])) & (1<<j);
			setPixel(i+column,j,val);
		}
	}
}

void draw_clock(uint8_t hour,uint8_t minute,uint8_t second)
{
	// uint8_t hour=random(24);
	// uint8_t minute=random(60);
	// uint8_t second=random(60);
	
	clr();
	if(hour>=10) draw_font4x8(0,hour/10);
	else draw_font4x8(0,10); //blank
	draw_font4x8(5,hour%10);
	setPixel(10,2,1);
	setPixel(10,5,1);
	draw_font4x8(12,minute/10);
	draw_font4x8(17,minute%10);
	draw_font4x7(23,second/10);
	draw_font4x7(28,second%10);
	refreshAll();	
}

void drawChar(uint8_t col, const uint8_t *data, const char ch)
{
  int len = pgm_read_byte(data);
  int w = pgm_read_byte(data + 1 + ch * len);
  for (int i = 0; i < w; i++)
    if(col+i>=0 && col+i<8*NUM_MAX) {
      byte v = pgm_read_byte(data + 1 + ch * len + 1 + i);
			for(int y=0;y<8;y++) setPixel(col+i,y,bitRead(v,y) ? 1 : 0);
    }
}

void drawString(uint8_t col, const uint8_t *data, const char *string)
{
	clr();
  int len = pgm_read_byte(data);
	while(*string)
	{
  	int w = pgm_read_byte(data + 1 + (*string) * len);
		drawChar(col,data,*string);
		col+=w+1;
		string++;
	}
	refreshAll();
}
