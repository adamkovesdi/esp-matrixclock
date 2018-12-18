#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Arduino.h>
#include "fonts.h"
#include "max7219.h"

// void draw_font4x7(uint8_t column, uint8_t number);
// void draw_font4x8(uint8_t column, uint8_t number);

void draw_clock(uint8_t hour,uint8_t minute,uint8_t second);
void drawChar(uint8_t col, const uint8_t *fontdata, const char ch);
void drawString(uint8_t col, const uint8_t *fontdata, const char *string);
void drawStringClr(uint8_t col, const uint8_t *fontdata, const char *string);

#endif
