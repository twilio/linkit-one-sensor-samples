#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL 1

// Parameter 1 = number of cells (max: 512)
// Parameter 2 = Arduino pin number (default pin: 9)
//NS_Rainbow ns_cell = NS_Rainbow(N_CELL);
NS_Rainbow ns_cell = NS_Rainbow(N_CELL,PIN);

void setup() {
  delay(100);
  ns_cell.begin();
  //ns_cell.setBrightness(128);  // range: 0 ~ 255, default: 255  
}

void loop() { 
  unsigned short n = 0;     // n: n-th Cell, 0 ~ (N_CELL-1)
  unsigned int   t = 1000;  // t: int
  
  ns_cell.setColor(n, 255,   0,   0);      // Red
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n, 162,  93,   0);      //
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n,  66, 189,   0);      // 
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n,   0, 255,  30);      // 
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n,   0, 129, 126);      // 
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n,   0,  33, 222);      // 
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n,  63,   0, 192);      // 
  ns_cell.show();
  delay(t);
  ns_cell.setColor(n, 159,   0,  96);      //
  ns_cell.show();
  delay(t);
  
  rainbow(30);      // interval: 30ms  
  delay(t); 
}

void rainbow(uint16_t interval) {
  uint16_t n = ns_cell.numCells();

  for(uint16_t j=0; j<255; j++) {  // one cycle 
    for(uint16_t i=0; i<n; i++) {
      byte r_pos = (((i<<8) -  i) / n + j) % 0xFF;
      byte sect = (r_pos / 0x55) % 0x03, pos = (r_pos % 0x55) * 0x03;
  
      switch(sect) {
      case 0: 
        ns_cell.setColor(i,ns_cell.RGBtoColor(0xFF - pos, pos, 0x00)); break;
      case 1: 
        ns_cell.setColor(i,ns_cell.RGBtoColor(0x00, 0xFF - pos, pos)); break;
      case 2:
        ns_cell.setColor(i,ns_cell.RGBtoColor(pos, 0x00, 0xFF - pos)); break;
      }  
    }
    ns_cell.show();
    delay(interval);
  }
}
