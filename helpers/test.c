// test application for font drawer

#include <stdio.h>

#define PROGMEM
#define uint8_t	unsigned char

#include "testfont.h"

void drawString(uint8_t col, const uint8_t *fontptr, const char *string)
{
	const uint8_t *ptr;
	uint8_t dl, i, cur, fl, y;
	fl=*fontptr++;
	printf("Font length: %d\n\n",fl);
	// loop
	while(*string)
	{
		printf("char: %d\n",*string);
		ptr=fontptr+fl*(*string);
		dl=*ptr++;
		// printf("Digit cols: %d\n",dl);

		for(i=0;i<dl;i++)
		{
			cur=*ptr++;
			// printf("0x%02X ",cur);
			for(y=0;y<8;y++) printf("%c",cur&1<<y? 'X' : '.' );
			printf("\n");
		}
		printf("\n");
		string++;
	}
}

int main()
{
	const char buf[]={ 4,3,8,9,0 };
	drawString(4,dig6x8,buf);
	return 0; 
}
