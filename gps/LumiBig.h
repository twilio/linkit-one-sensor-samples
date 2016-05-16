/*
  Lumi96x.h - SSD1327 Gray OLED Driver Library
  2011 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author: Visweswara R

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LUMIBIG_data_H
#define LUMIBIG_data_H

#include <Arduino.h>
#include "Wire.h"

#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define LUMIBIG_VERTICAL_MODE     01
#define LUMIBIG_HORIZONTAL_MODE     02

#define LUMIBIG_Max_X                    95  //96 Pixels
#define LUMIBIG_Max_Y                    95  //96  Pixels
#define LUMIBIG_ScreenBuffer_Size      4608

#define LUMIBIG_Address   0x3c
#define LUMIBIG_Command_Mode  0x80
#define LUMIBIG_Data_Mode   0x40

#define LUMIBIG_Display_Off_Cmd 0xAE
#define LUMIBIG_Display_On_Cmd  0xAF

#define LUMIBIG_Normal_Display_Cmd  0xA4
#define LUMIBIG_Inverse_Display_Cmd 0xA7
#define LUMIBIG_Activate_Scroll_Cmd 0x2F
#define LUMIBIG_Dectivate_Scroll_Cmd  0x2E
#define LUMIBIG_Set_ContrastLevel_Cmd 0x81

#define Scroll_Left     0x00
#define Scroll_Right      0x01

#define Scroll_2Frames      0x7
#define Scroll_3Frames      0x4
#define Scroll_4Frames      0x5
#define Scroll_5Frames      0x0
#define Scroll_25Frames     0x6
#define Scroll_64Frames     0x1
#define Scroll_128Frames    0x2
#define Scroll_256Frames    0x3


class LumiBig {

public:
char addressingMode, oldAddressingMode;
char screenBuffer [LUMIBIG_ScreenBuffer_Size];                    //Buffer for holding graphics data.
//char addressingMode;

void init(void);

void setNormalDisplay();
void setInverseDisplay();

void sendCommand(unsigned char command);
void sendData(unsigned char Data);
void setGrayLevel(unsigned char grayLevel);

void setVerticalMode();
void setHorizontalMode();

void setTextXY(unsigned char row, unsigned char col);
void clearDisplay();
void setBrightness(unsigned char ContrastLevel);
void putChar(unsigned char c);
void drawString(const char * str1, unsigned char row, unsigned char column);

unsigned char putNumber (long n);
unsigned char putFloat (float floatNumber,unsigned char decimal);
unsigned char putFloat (float floatNumber);

void putString(const char *String);

void drawBitmap(unsigned char *bitmaparray,int bytes);

void setHorizontalScrollProperties(bool direction,unsigned char startRow, unsigned char endRow,unsigned char startColumn, unsigned char endColumn, unsigned char scrollSpeed);
void activateScroll();
void deactivateScroll();

//Direct methods.
void drawDirect (bool);
//void drawDirectPixel (unsigned char, unsigned char, unsigned char);       //Deprecated - direct writes (destroys pixels around due to 8 bit mapping).

//Graphics Methods.
void drawPixel (uint8_t real_x, uint8_t real_y, uint8_t p_color);
void drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void drawLineH (uint8_t x, uint8_t y, uint8_t width, uint8_t color);
void drawLineV (uint8_t x, uint8_t y, uint8_t height, uint8_t color);
void drawCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color);
void fillCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color);
void drawRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
void fillRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

//Store & restore addressing methods.
void setAddressMode (char);
char restoreAddressMode ();

//Buffer functions.
void clearBuffer ();
void paintBuffer ();

private:

unsigned char grayH;
unsigned char grayL;


};

//extern Lumi96x Lumi96x;  // Lumi96x object

#endif
