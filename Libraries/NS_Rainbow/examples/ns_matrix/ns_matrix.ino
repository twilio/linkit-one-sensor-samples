#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL 64

// Parameter 1 = number of cells (max: 512)
// Parameter 2 = Arduino pin number (default pin: 9)
//NS_Rainbow ns_matrix = NS_Rainbow(N_CELL);
NS_Rainbow ns_matrix = NS_Rainbow(N_CELL,PIN);

void setup() {
  delay(100);
  ns_matrix.begin();
  ns_matrix.clear();
  ns_matrix.show();
  ns_matrix.setBrightness(128);  // range: 0 ~ 255  
}

void loop() {
  byte           cycle = 1; // cycles of all colors on wheel
  unsigned int   t = 100;   // t: delay time

  for(byte i=0; i<ns_matrix.numCells(); i++) {
    ns_matrix.setColor(i, 162,  93,   0);
    ns_matrix.show();
    delay(t);
    ns_matrix.setColor(i,   0,   0,   0);      // Black (clear)
  }
  
  for(int i=0; i<2; i++) {
    rainbow(10);      // interval: 10ms
  } 
  
  ns_matrix.clear();
  ns_matrix.show();
  delay(t); 
}

void rainbow(uint16_t interval) {
  uint16_t n = ns_matrix.numCells();

  for(uint16_t j=0; j<255; j++) {  // one cycle 
    for(uint16_t i=0; i<n; i++) {
      byte r_pos = (((i<<8) -  i) / n + j) % 0xFF;
      byte sect = (r_pos / 0x55) % 0x03, pos = (r_pos % 0x55) * 0x03;
  
      switch(sect) {
      case 0: 
        ns_matrix.setColor(i,ns_matrix.RGBtoColor(0xFF - pos, pos, 0x00)); break;
      case 1: 
        ns_matrix.setColor(i,ns_matrix.RGBtoColor(0x00, 0xFF - pos, pos)); break;
      case 2:
        ns_matrix.setColor(i,ns_matrix.RGBtoColor(pos, 0x00, 0xFF - pos)); break;
      }  
    }
    ns_matrix.show();
    delay(interval);
  }
}
