/*-------------------------------------------------------------------------
Arduino library to control a WS2812B based RGB LED devices  
such as NulSom Rainbow Cell, Stick, Matrix, Coin and LED strips.
Currently handles 800 KHz bitstreams on 16 MHz ATmega MCUs.  

Updated by Chang Hoon Lee for NulSom Rainbow series based on NeoPixel Lib., 
contributions by Do Yun Lee and other members.
-------------------------------------------------------------------------*/

#include "NS_Rainbow.h"

NS_Rainbow::NS_Rainbow(uint16_t n, uint8_t p) : 
	nCells((n>MAX_SIZE)?MAX_SIZE:n), pin(p), 
	nBytes(nCells*3), maxBytes(MAX_SIZE*3), cells(NULL), brightness(0xFF)//,
  //port(portOutputRegister(digitalPinToPort(p))), portMask(digitalPinToBitMask(p))
{
  if((cells = (uint8_t *)malloc(nBytes))) {	
    memset(cells, 0, nBytes);								
  }
}

NS_Rainbow::~NS_Rainbow() {
  if(cells) free(cells);
  pinMode(pin, INPUT);
}

void NS_Rainbow::begin(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void NS_Rainbow::end(void) {
	if(cells) free(cells);
}

void NS_Rainbow::show() {
  if(!cells) return;
	
  volatile uint16_t
    i = nBytes;
  volatile uint8_t
  	next,
  	bit,
   *ptr = cells,
    cB   = *ptr++,
    hi,
    lo;

    hi   = digitalRead(pin) |  portMask;
    lo   = digitalRead(pin) & ~portMask;

	asm volatile(
		"mov  %[next] ,  %[low]"	"\n\t" 
		"ldi  %[bit]  ,  0x08"		"\n\t" 
		"cli\n"       
	"run:"											"\n\t"
		"st   %a[port],  %[high]"	"\n\t"
		"sbrc %[byte] ,  0x07"		"\n\t"
		"mov  %[next] ,  %[high]"	"\n\t"
		"st   %a[port],  %[next]"	"\n\t"
		"mov  %[next] ,  %[low]"	"\n\t"
		"dec  %[bit]"							"\n\t"
		"breq nextByte"						"\n\t"
		"lsl  %[byte]"						"\n\t"
		"jmp .+0"									"\n\t"
		"st   %a[port],  %[low]"	"\n\t"
		"jmp .+0"									"\n\t"
		"rjmp run"								"\n\t"
	"nextByte:"									"\n\t"
		"ld   %[byte] ,  %a[ptr]+""\n\t"
		"st   %a[port],  %[low]"	"\n\t"
		"ldi  %[bit]  ,  0x08"		"\n\t"
		"nop"											"\n\t"
		"sbiw %[cnti], 1"				  "\n\t"
		"brne run"								"\n\t"
		"sei\n"
		:[port]	 "+e" (port),
		 [byte]	 "+r" (cB),
		 [bit]	 "+r" (bit),
		 [next]	 "+r" (next),
		 [cnti]	 "+w" (i)
		:[ptr]	 "e"  (ptr),
		 [high]	 "r"  (hi),
		 [low]	 "r"  (lo)
	);
  _delay_us(50);
}

void NS_Rainbow::clear(uint16_t n_clr) {
	if(n_clr > nCells)		n_clr = nCells;
	uint16_t clrBytes = n_clr * 3;
	memset(cells, 0, clrBytes);
}

void NS_Rainbow::setPin(uint8_t pin) {
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	port     = portOutputRegister(digitalPinToPort(pin));
	portMask = digitalPinToBitMask(pin);
}

void NS_Rainbow::freePin(uint8_t pin) {
	digitalWrite(pin, LOW);
	pinMode(pin, INPUT);
	port = NULL;
	portMask = 0x00;
}

void NS_Rainbow::setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if(n < nCells) {  	 	
    if(brightness < 0xFF) {   	
    	if(brightness > 0x01) {
    		uint16_t cb = brightness + 1, t = 0;
    		
    		t = (g|0x01) * cb;
    		(t>0x80)?(g = (t-0x80) >> 8):(g = 0x00);
    		t = (r|0x01) * cb;
    		(t>0x80)?(r = (t-0x80) >> 8):(r = 0x00);
    		t = (b|0x01) * cb;
    		(t>0x80)?(b = (t-0x80) >> 8):(b = 0x00);
    	}
    	else { 
    		g = 0x00;
    		r = 0x00;
    		b = 0x00;
    	}
    }
    uint8_t *p = &cells[n * 3];

    *p++ = g;
    *p++ = r;
    *p = b;
  }
}

void NS_Rainbow::setColor(uint16_t n, uint32_t c) {
  if(n < nCells) {
		uint8_t
			r = (uint8_t)(c >> 16),
			g = (uint8_t)(c >>  8),
			b = (uint8_t)c;
  	
    if(brightness < 0xFF) {   	
    	if(brightness > 0x01) {
    		uint16_t cb = brightness + 1, t = 0;
    		
    		t = (g|0x01) * cb;
    		(t>0x80)?(g = (t-0x80) >> 8):(g = 0x00);
    		t = (r|0x01) * cb;
    		(t>0x80)?(r = (t-0x80) >> 8):(r = 0x00);
    		t = (b|0x01) * cb;
    		(t>0x80)?(b = (t-0x80) >> 8):(b = 0x00);
    	}
    	else { 
    		g = 0x00;
    		r = 0x00;
    		b = 0x00;
    	}
    }
    uint8_t *p = &cells[n * 3];

    *p++ = g;
    *p++ = r;
    *p = b;
  }
}

uint32_t NS_Rainbow::RGBtoColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t NS_Rainbow::getColor(uint16_t n) const {
	if(n < nCells) {
		uint16_t base = n * 3;
		return (uint32_t)(cells[base + 2])       |
			    ((uint32_t)(cells[base])     << 8) |
			    ((uint32_t)(cells[base + 1]) << 16);
	}
	return 0; 
}

uint8_t *NS_Rainbow::getCellsAddr(void) const {
  return cells;
}

uint16_t NS_Rainbow::numCells(void) const {
  return nCells;
}

void NS_Rainbow::setBrightness(uint8_t b) {
  if(b != brightness) {
    uint8_t *ptr = cells;
    uint16_t ratio, nb = b + 1, cb = brightness + 1;
    
 		if (b < 1) {
			for (uint16_t i = 0; i < nBytes; i++)
				*ptr++ = 0;	
		}
		else if (b > 0xFE) {
			for (uint16_t i = 0; i < nBytes; i++)
				(*ptr > 0) ? (*ptr++ = (((uint32_t)(*ptr + 1) << 16) / cb - 0x80) >> 8) : (*ptr++ = 0);
		}
		else {
			for (uint16_t i = 0; i < nBytes; i++)
				(*ptr > 0) ? (*ptr++ = ((uint32_t)(*ptr + 1) * (nb << 8) / cb - 0x80) >> 8) : (*ptr++ = 0);
		}
		brightness = b;
  }
}

uint8_t NS_Rainbow::getBrightness(void) const {
  return brightness;
}