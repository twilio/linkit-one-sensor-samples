#include <NS_Rainbow.h>
#include <EEPROM.h>

#define PIN 9
#define N_CELL (30*5)  // 30pcs/m * 5m/roll

byte flag_a = 1, flag_b = 0;
unsigned int cnt = 0, seed = 0;  // seed: used to initialize random number generator
const unsigned int maxCycle = 1200;  // go to next state when cnt >= maxCycle

// Parameter 1 = number of cells (max: 512)
// Parameter 2 = Arduino pin number (default pin: 9)
//NS_Rainbow ns_strip = NS_Rainbow(N_CELL);
NS_Rainbow ns_strip = NS_Rainbow(N_CELL,PIN);

void setup() {
  for (int i = 0; i < 8; i++) {
    seed += analogRead(i);
  }
  seed += EEPROM.read(0);  // get part of the seed from EEPROM
  randomSeed(seed);
  EEPROM.write(0, random(256));
  delay(100);
  ns_strip.begin();
  ns_strip.clear();
  ns_strip.show();
  //ns_strip.setBrightness(128);  // range: 0 ~ 255  
}

void loop() {
  unsigned char sect, color;
  
  if(flag_a) {  
    sect = cnt / (maxCycle / 4);
    switch(sect) {
      case 0: 
        twinkleTwinkle(0, 1, 0);  // only white
        break;
      case 1: 
        twinkleTwinkle(0, 2, 0);  // white and red
        break;
      case 2: 
        twinkleTwinkle(1, 2, 0);  // red, and green
        break;
      default: 
        // red, green, blue, cyan, magenta, yellow
        twinkleTwinkle(1, 6, cnt > maxCycle - 100);
    }
    ns_strip.show();
  }
  
  if(flag_b) {  
    ns_strip.setColor(random(N_CELL), random(256), random(256), random(256));
    ns_strip.setColor(random(N_CELL), 0, 0, 0);
    ns_strip.setColor(random(N_CELL), 0, 0, 0);
    ns_strip.show();
    delay(10); 
    ns_strip.clear();
  }

  if(++cnt > maxCycle) {
    cnt = 0;
    flag_a = random(2);
    flag_b = random(2);
  }
}


void fade(unsigned char *val, unsigned char fadeTime) {
  if (*val) {
    unsigned char subAmt = *val >> fadeTime;
    if (subAmt < 1)
      subAmt = 1;
    *val -= subAmt;
  }
}

void twinkleColorAdjust(unsigned char *color) {
  if (*color == 255) {
    *color = 254;
  }
  else if (*color % 2) {
    *color = *color * 2 + 1;
  }
  else if (*color > 0) {
    fade(color, 4);
    if (*color % 2) {
      (*color)--;
    }
  }
}

void twinkleTwinkle(unsigned char minVal, unsigned char numColors, unsigned char noNewBursts) {
  for (unsigned int i = 0; i < N_CELL; i++) {
    uint16_t base = i * 3;
    twinkleColorAdjust((ns_strip.getCellsAddr()+base));
    twinkleColorAdjust((ns_strip.getCellsAddr()+base+2));
    twinkleColorAdjust((ns_strip.getCellsAddr()+base+1));
  }
  
  if (noNewBursts) return;
  
  for (unsigned int i = 0; i < 4; i++) {
    int j = random(N_CELL);
    uint32_t color = ns_strip.getColor(j);
    
    if (color) break;
    
    switch (random(numColors) + minVal) {
      case 0:
        ns_strip.setColor(j, 255, 255, 255);  // white
        break;
      case 1:
        ns_strip.setColor(j, 255,   0,   0);  // red
        break;
      case 2:
        ns_strip.setColor(j,   0, 255,   0);  // green
        break;
      case 3:
        ns_strip.setColor(j,   0,   0, 255);  // blue
        break;
      case 4:
        ns_strip.setColor(j, 255, 255,   0);  // yellow
        break;
      case 5:
        ns_strip.setColor(j,   0, 255, 255);  // cyan
        break;
      case 6:
        ns_strip.setColor(j, 255,   0, 255);  // magenta
        break;
      default:
        ns_strip.setColor(j, 255, 255, 255);  // white
    }
  }
}
