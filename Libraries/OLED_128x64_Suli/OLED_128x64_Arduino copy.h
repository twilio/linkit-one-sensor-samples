#ifndef __OLED_128x64_ARDUINO_H__
#define __OLED_128x64_ARDUINO_H__

#include <Wire.h>
#include <Arduino.h>

#include "Suli.h"

#include "OLED_128x64_Suli.h"


class SeeedOLED {

public:

    void init()
    {
        oled_128x64_init(&Wire);
    }

    void setNormalDisplay()
    {
        oled_128x64_normal_display();
    }
    
    void setInverseDisplay()
    {
        oled_128x64_inversel_display();
    }

    void setPageMode()
    {
        oled_128x64_pagemode();
    }
    
    void setHorizontalMode()
    {
        oled_128x64_hmode();
    }

    void setTextXY(unsigned char Row, unsigned char Column)
    {
        oled_128x64_XY(Column, Row);
    }
    
    void clearDisplay()
    {
        oled_128x64_clear();
    }
    
    void setBrightness(unsigned char Brightness)
    {
        oled_128x64_brightness(Brightness);
    }
    
    void putChar(unsigned char c)
    {
        oled_128x64_char(c);
    }

    void putString(const char *String)
    {
        oled_128x64_string(String);
    }

    unsigned char putNumber(long n)
    {
        oled_128x64_num(n);
    }
    
    unsigned char putFloat(float floatNumber,unsigned char decimal)
    {
        oled_128x64_float_decimal(floatNumber, decimal);
    }
    
    unsigned char putFloat(float floatNumber)
    {
        oled_128x64_float(floatNumber);
    }

    void setHorizontalScrollProperties(bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed)
    {
        oled_128x64_hsp(direction, startPage, endPage, scrollSpeed);
    }
    
    void activateScroll()
    {
        oled_128x64_active_scroll();
    }
    
    void deactivateScroll()
    {
        oled_128x64_deactive_scroll();
    }

};


#endif