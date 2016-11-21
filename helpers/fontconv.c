// translator for http://xantorohara.github.io/led-matrix-editor/
// written by Adam Kovesdi (c)2016

#include <stdio.h>
#include <stdint.h>

const uint64_t IMAGES[] = {
  0x000000040e150404,
  0x0000000f03050910,
  0x00000004021f0204,
  0x000000100905030f,
  0x0000000404150e04,
  0x000000011214181e,
  0x00000004081f0804,
  0x0000001e18141201,
};

void print64bit(uint64_t number)
{
	uint8_t *array;
	uint8_t by;
	array=(uint8_t*)&number;
	for(by=0;by<8;by++)
	{
		printf("0x%02x, ",*(array+by));
	}
	printf("\n");
	array+=8;
}

#define SETBIT(theport,thebit) ((theport) |= (1<<thebit))
#define GETBIT(theport,thebit) ((theport) & (1<<thebit))
#define CLEARBIT(theport,thebit) ((theport) &= (~(1<<thebit)))

uint64_t translate(uint64_t number)
{
	uint64_t result;
	uint8_t *source,*dest;
	source=(uint8_t*)&number;
	dest=(uint8_t*)&result;

	int byte, bit;

	for(byte=0;byte<8;byte++)
	{
		for(bit=0;bit<8;bit++)
		{
			if(GETBIT(*(source+byte),bit))
			{
				SETBIT(*(dest+bit),byte);
			}
			else
			{
				CLEARBIT(*(dest+bit),byte);
			}
		}
	}
	return result;
}

int main()
{
	uint8_t by,pic;
	printf("const uint8_t icons[] PROGMEM = { 9,\n");
	for(pic=0;pic<sizeof(IMAGES)/8;pic++) {
		printf("0x08,  ");
		print64bit(translate(IMAGES[pic]));
	}
	printf("};\n");
	return 0;
}



