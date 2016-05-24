#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL 8

// Parameter 1 = number of cells (max: 512)
// Parameter 2 = Arduino pin number (default pin: 9)
//NS_Rainbow ns_stick = NS_Rainbow(N_CELL);
NS_Rainbow ns_stick = NS_Rainbow(N_CELL,PIN);

void setup() {
  delay(100);
  ns_stick.begin();
  //ns_stick.setBrightness(128);  // range: 0 ~ 255, default: 255  
}

void loop() {
  unsigned int   t = 500;   // t: delay time

  ns_stick.setColor(0, 255,   0,   0);      // Red
  ns_stick.show();
  delay(t);
  ns_stick.setColor(0,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(1, 162,  93,   0);      //   
  ns_stick.show();
  delay(t);
  ns_stick.setColor(1,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(2,  66, 189,   0);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(2,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(3,   0, 255,  30);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(3,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(4,   0, 129, 126);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(4,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(5,   0,  33, 222);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(5,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(6,  63,   0, 192);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(6,   0,   0,   0);      // Black (clear)
  ns_stick.setColor(7, 159,   0,  96);      // 
  ns_stick.show();
  delay(t);
  ns_stick.setColor(7,   0,   0,   0);      // Black (clear)
  ns_stick.show();
  delay(t);
  
  for(int i=0; i<2; i++) {
    rainbow(30);      // interval: 30ms
  } 
  
  ns_stick.clear();
  ns_stick.show();
  delay(t); 
}

void rainbow(uint16_t interval) {
  uint16_t n = ns_stick.numCells();

  for(uint16_t j=0; j<255; j++) {  // one cycle 
    for(uint16_t i=0; i<n; i++) {
      byte r_pos = (((i<<8) -  i) / n + j) % 0xFF;
      byte sect = (r_pos / 0x55) % 0x03, pos = (r_pos % 0x55) * 0x03;
  
      switch(sect) {
      case 0: 
        ns_stick.setColor(i,ns_stick.RGBtoColor(0xFF - pos, pos, 0x00)); break;
      case 1: 
        ns_stick.setColor(i,ns_stick.RGBtoColor(0x00, 0xFF - pos, pos)); break;
      case 2:
        ns_stick.setColor(i,ns_stick.RGBtoColor(pos, 0x00, 0xFF - pos)); break;
      }  
    }
    ns_stick.show();
    delay(interval);
  }
}
