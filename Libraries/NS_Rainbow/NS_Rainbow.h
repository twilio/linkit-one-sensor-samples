/*--------------------------------------------------------------------
  This file is part of the NulSom Rainbow library.

  NulSom Rainbow is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NulSom Rainbow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  --------------------------------------------------------------------*/

#ifndef NS_RAINBOW_H
#define NS_RAINBOW_H

#include <Arduino.h>
//#include <util/delay.h>



#define SIG_PIN  	9
#define MAX_SIZE 	512		// 612

class NS_Rainbow {

 public:

  NS_Rainbow(uint16_t n, uint8_t p = SIG_PIN);
  ~NS_Rainbow();

  void
    begin(void),
		end(void),
		show(void),
		clear(uint16_t n_clr = MAX_SIZE),
		setPin(uint8_t p),
		freePin(uint8_t pin),
		setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
		setColor(uint16_t n, uint32_t c),
    setBrightness(uint8_t b = 0xFF);

	uint8_t
    getBrightness(void) const,
		*getCellsAddr() const;
   
  uint16_t
    numCells(void) const;

  static uint32_t
    RGBtoColor(uint8_t r, uint8_t g, uint8_t b);

  uint32_t
    getColor(uint16_t n) const;

 private:

#ifdef __AVR__
  const volatile uint8_t
    *port;

  uint8_t
    portMask;
#endif

  uint8_t
    pin,
    brightness,
   *cells;

  const uint16_t
    nCells,
    nBytes,
    maxBytes;
};

#endif // NS_RAINBOW_H
