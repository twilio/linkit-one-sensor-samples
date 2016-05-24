/*
  SeeedTouchScreen.cpp - Library for 4-line resistance touch screen.
  Modified by loovee Aug 12, 2012.
  (c) ladyada / adafruit
  Code under MIT License.
*/

#include "pins_arduino.h"
#include "wiring_private.h"
#include <avr/pgmspace.h>
#include "SeeedTouchScreen.h"

// increase or decrease the touchscreen oversampling. This is a little different than you make think:
// 1 is no oversampling, whatever data we get is immediately returned
// 2 is double-sampling and we only return valid data if both points are the same
// 3+ uses insert sort to get the median value.
// We found 2 is precise yet not too slow so we suggest sticking with it!

#define NUMSAMPLES 2        // sample number
#define COMP       2
#define AVERAGE    1
#define RXPLATE    300
#define TSDEBUG    1        // if print the debug information
Point::Point(void) {
    x = y = 0;
}

Point::Point(int x0, int y0, int z0)
{
    x = x0;
    y = y0;
    z = z0;
}

bool Point::operator==(Point p1)
{
    return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool Point::operator!=(Point p1)
{
    return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
    _yp = yp;
    _xm = xm;
    _ym = ym;
    _xp = xp;
}

Point TouchScreen::getPoint(void) {
    


    //return Point(x, y, z);
}

bool TouchScreen::isTouching(void)
{
    Point p = getPoint();
    if(p.z > __PRESURE)return 1;
    else return 0;
}