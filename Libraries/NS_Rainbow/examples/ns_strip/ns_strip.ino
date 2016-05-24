#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL (30*5)  // 30pcs/m * 5m/roll

// Parameter 1 = number of cells (max: 512)
// Parameter 2 = Arduino pin number (default pin: 9)
//NS_Rainbow ns_strip = NS_Rainbow(N_CELL);
NS_Rainbow ns_strip = NS_Rainbow(N_CELL,PIN);

void setup() {
  delay(100);
  ns_strip.begin();
  ns_strip.clear();
  ns_strip.setBrightness(128);  // range: 0 ~ 255  
}

void loop() {
  unsigned int   t = 100;   // t: delay time

  for(byte i=0; i<ns_strip.numCells(); i++) {
    ns_strip.setColor(i, 85,  85,   85);
    ns_strip.show();
    delay(t);
    ns_strip.setColor(i,   0,   0,   0);      // Black (clear)
  }
  
  rainbow(30);      // interval: 30ms
  
  ns_strip.clear();
  ns_strip.show();
  delay(t); 
}

void rainbow(uint16_t interval) {
  uint16_t n = ns_strip.numCells();

  for(uint16_t j=0; j<255; j++) {  // one cycle 
    for(uint16_t i=0; i<n; i++) {
      byte r_pos = (((i<<8) -  i) / n + j) % 0xFF;
      byte sect = (r_pos / 0x55) % 0x03, pos = (r_pos % 0x55) * 0x03;
  
      switch(sect) {
      case 0: 
        ns_strip.setColor(i,ns_strip.RGBtoColor(0xFF - pos, pos, 0x00)); break;
      case 1: 
        ns_strip.setColor(i,ns_strip.RGBtoColor(0x00, 0xFF - pos, pos)); break;
      case 2:
        ns_strip.setColor(i,ns_strip.RGBtoColor(pos, 0x00, 0xFF - pos)); break;
      }  
    }
    ns_strip.show();
    delay(interval);
  }
}
