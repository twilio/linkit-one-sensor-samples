/*
  GraphicsLib - SSD130x OLED Driver Library
  Based on SeeedOLED library (2011 Copyright (c) Seeed Technology Inc.  Author: Visweswara R)

  Twilio Marketing Department.
*/

#ifndef Lumi_data_H
#define Lumi_data_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#include "Wire.h"
#endif

#define SWAP_VARS(a, b) do { typeof(a) t; t = a; a = b; b = t; } while(0)

#define Lumi_Max_X                   127 //128 Pixels
#define Lumi_Max_Y                    63  //64  Pixels
#define Lumi_ScreenBuffer_Size      1024

#define PAGE_MODE                   0x02
#define HORIZONTAL_MODE             0x00

#define Lumi_Address                0x3c
#define Lumi_Command_Mode           0x80
#define Lumi_Data_Mode              0x40
#define Lumi_Display_Off_Cmd        0xAE
#define Lumi_Display_On_Cmd         0xAF
#define Lumi_Normal_Display_Cmd     0xA6
#define Lumi_Inverse_Display_Cmd    0xA7
#define Lumi_Activate_Scroll_Cmd    0x2F
#define Lumi_Dectivate_Scroll_Cmd   0x2E
#define Lumi_Set_Brightness_Cmd     0x81

#define Scroll_Left                 0x00
#define Scroll_Right                0x01

#define Scroll_2Frames              0x7
#define Scroll_3Frames              0x4
#define Scroll_4Frames              0x5
#define Scroll_5Frames              0x0
#define Scroll_25Frames             0x6
#define Scroll_64Frames             0x1
#define Scroll_128Frames            0x2
#define Scroll_256Frames            0x3

class Lumi {
private:
    unsigned char grayH;
    unsigned char grayL;
public:
    char addressingMode, oldAddressingMode;
    char screenBuffer [Lumi_ScreenBuffer_Size];                    //128 * 8 pages / 8 bits

    void init (void);

    void setNormalDisplay ();
    void setInverseDisplay ();

    void sendCommand (unsigned char command);
    void sendData (unsigned char Data);
    //setGrayLevel()

    //setVerticalMode()
    void setHorizontalMode ();

    //--setPageMode()
    void setPageMode ();

    void setTextXY (unsigned char Row, unsigned char Column);
    void clearDisplay ();
    void setBrightness (unsigned char Brightness);
    void putChar (unsigned char c);
    void putString (const char *String);
    unsigned char putNumber (long n);
    void drawString(const char * str1, unsigned char row, unsigned char column);

    //--putFloat()
    unsigned char putFloat (float floatNumber,unsigned char decimal);
    unsigned char putFloat (float floatNumber);
    void drawBitmap (unsigned char *bitmaparray, int bytes);

    void setHorizontalScrollProperties (bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed);
    void activateScroll ();
    void deactivateScroll ();

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

};

#endif
