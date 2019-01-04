#include "display.h"

void draw_myfont(uint8_t column, const uint8_t *fontdata, uint8_t number) {
	// Draw a digit on the canvas at position specified by column
	uint8_t i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<8;j++) {
			bool val;
			val=(pgm_read_byte(fontdata + number * 4 + i)) & (1<<j);
			setPixel(i+column,j,val);
		}
	}
}

void draw_clock(uint8_t hour,uint8_t minute,uint8_t second)
{
	clr();
	if(hour>=10) draw_myfont(0,font4x8,hour/10);
	else draw_myfont(0,font4x8,10); //blank
	draw_myfont(5,font4x8,hour%10);
	setPixel(10,2,1);
	setPixel(10,5,1);
	draw_myfont(12,font4x8,minute/10);
	draw_myfont(17,font4x8,minute%10);
	draw_myfont(23,font4x7,second/10);
	draw_myfont(28,font4x7,second%10);
	refreshAll();	
}

void drawChar(uint8_t col, const uint8_t *fontdata, const char ch)
{
  int len = pgm_read_byte(fontdata);
  int w = pgm_read_byte(fontdata + 1 + ch * len);
  for (int i = 0; i < w; i++)
    if(col+i>=0 && col+i<8*NUM_MAX) {
      byte v = pgm_read_byte(fontdata + 1 + ch * len + 1 + i);
			for(int y=0;y<8;y++) setPixel(col+i,y,bitRead(v,y) ? 1 : 0);
    }
}

void drawString(uint8_t col, const uint8_t *fontdata, const char *string)
{
  int len = pgm_read_byte(fontdata);
	while(*string)
	{
  	int w = pgm_read_byte(fontdata + 1 + (*string) * len);
		drawChar(col,fontdata,*string);
		col+=w+1;
		string++;
	}
}

void drawStringClr(uint8_t col, const uint8_t *fontdata, const char *string)
{
	clr();
	drawString(col, fontdata, string);
	refreshAll();
}
