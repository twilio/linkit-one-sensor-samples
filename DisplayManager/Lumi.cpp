#include "Wire.h"
#include "Lumi.h"
#include "Lumi_default_font.h"     //Default font.

#include <avr/pgmspace.h>

//Constructor:
void Lumi::init(void)
{
    oldAddressingMode = addressingMode; //Default.
    sendCommand(Lumi_Display_Off_Cmd);  //display off
    delay(5);
    sendCommand(Lumi_Display_On_Cmd);   //display on
    delay(5);
    sendCommand(Lumi_Normal_Display_Cmd);  //Set Normal Display (default)
}


//sendCommand():
void Lumi::sendCommand(unsigned char command)
{
  Wire.beginTransmission(Lumi_Address); // begin I2C communication
#if defined(ARDUINO) && ARDUINO >= 100
  Wire.write(Lumi_Command_Mode);             // Set OLED Command mode
  Wire.write(command);
#else
  Wire.send(Lumi_Command_Mode);      // Set OLED Command mode
  Wire.send(command);
#endif
  Wire.endTransmission();                    // End I2C communication
}


//setBrightness():
void Lumi::setBrightness (unsigned char Brightness)
{
   sendCommand(Lumi_Set_Brightness_Cmd);
   sendCommand(Brightness);
}


//setTextXY():
void Lumi::setTextXY (unsigned char Row, unsigned char Column)
{
    sendCommand(0xB0 + Row);                    //set page address
    sendCommand(0x00 + (8 * Column & 0x0F));      //set column lower address
    sendCommand(0x10 + ((8 * Column >> 4) & 0x0F));   //set column higher address
}


//clearDisplay():
void Lumi::clearDisplay ()
{
  unsigned char i,j;
  sendCommand(Lumi_Display_Off_Cmd);    //display off
  for(j=0;j<8;j++)
  {
    setTextXY(j,0);
    {
      for(i=0;i<16;i++)  //clear all columns
      {
        putChar(' ');
      }
    }
  }
  sendCommand(Lumi_Display_On_Cmd);     //display on
  setTextXY(0,0);
}


//sendData():
void Lumi::sendData (unsigned char Data)
{
     Wire.beginTransmission(Lumi_Address);  // begin I2C transmission
#if defined(ARDUINO) && ARDUINO >= 100
     Wire.write(Lumi_Data_Mode);            // data mode
     Wire.write(Data);
#else
     Wire.send(Lumi_Data_Mode);             // data mode
     Wire.send(Data);
#endif
     Wire.endTransmission();                // stop I2C transmission
}


//putChar():
void Lumi::putChar (unsigned char C)
{
    if(C < 32 || C > 127) //Ignore non-printable ASCII characters. This can be modified for multilingual font.
    {
    C=' '; //Space
    }
    unsigned char i=0;
    for(i=0;i<8;i++)
    {
       //read bytes from code memory
       sendData(pgm_read_byte(&BasicFont[C-32][i])); //font array starts at 0, ASCII starts at 32. Hence the translation
    }
}


//putString():
void Lumi::putString (const char *String)
{
    unsigned char i=0;
    while(String[i])
    {
        putChar(String[i]);
        i++;
    }
}


//putNumber():
unsigned char Lumi::putNumber (long long_num)
{
  unsigned char char_buffer[10]="";
  unsigned char i = 0;
  unsigned char f = 0;

  if (long_num < 0)
  {
    f=1;
    putChar('-');
    long_num = -long_num;
  }
  else if (long_num == 0)
  {
    f=1;
    putChar('0');
    return f;
  }

  while (long_num > 0)
  {
    char_buffer[i++] = long_num % 10;
    long_num /= 10;
  }

  f=f+i;
  for(; i > 0; i--)
  {
    putChar('0'+ char_buffer[i - 1]);
  }
  return f;
}


//putFloat():
unsigned char Lumi::putFloat (float floatNumber,unsigned char decimal)
{
  unsigned int temp=0;
  float decy=0.0;
  float rounding = 0.5;
  unsigned char f=0;
  if(floatNumber<0.0)
  {
    putString("-");
    floatNumber = -floatNumber;
    f +=1;
  }
  for (unsigned char i=0; i<decimal; ++i)
  {
    rounding /= 10.0;
  }
    floatNumber += rounding;

  temp = floatNumber;
  f += putNumber(temp);
  if(decimal>0)
  {
    putChar('.');
    f +=1;
 }
  decy = floatNumber-temp;//decimal part,
  for(unsigned char i=0;i<decimal;i++)//4
  {
    decy *=10;// for the next decimal
    temp = decy;//get the decimal
    putNumber(temp);
    decy -= temp;
  }
  f +=decimal;
  return f;
}


//putFloat():
unsigned char Lumi::putFloat (float floatNumber)
{
  unsigned char decimal=2;
  unsigned int temp=0;
  float decy=0.0;
  float rounding = 0.5;
  unsigned char f=0;
  if(floatNumber<0.0)
  {
    putString("-");
    floatNumber = -floatNumber;
    f +=1;
  }
  for (unsigned char i=0; i<decimal; ++i)
  {
    rounding /= 10.0;
  }
    floatNumber += rounding;

  temp = floatNumber;
  f += putNumber(temp);
  if(decimal>0)
  {
    putChar('.');
    f +=1;
 }
  decy = floatNumber-temp;//decimal part,
  for(unsigned char i=0;i<decimal;i++)//4
  {
    decy *=10;// for the next decimal
    temp = decy;//get the decimal
    putNumber(temp);
    decy -= temp;
  }
  f +=decimal;
  return f;
}

//drawString(): combines (x, y) and putString together.
void Lumi::drawString(const char * str1, unsigned char row, unsigned char column) {
  setAddressMode(PAGE_MODE);
  setTextXY(row, column);
  putString(str1);
  restoreAddressMode();
}


//drawBitmap():
void Lumi::drawBitmap (unsigned char *bitmaparray,int bytes)
{
  setAddressMode(HORIZONTAL_MODE);

  for(int i=0;i<bytes;i++)
  {
      sendData(pgm_read_byte(&bitmaparray[i]));
  }

  restoreAddressMode();
}


//setHorizontalScrollProperties():
void Lumi::setHorizontalScrollProperties (bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed)
{
   if(Scroll_Right == direction)
   {
        //Scroll Right
        sendCommand(0x26);
   }
   else
   {
        //Scroll Left
        sendCommand(0x27);

   }
    sendCommand(0x00);
    sendCommand(startPage);
    sendCommand(scrollSpeed);
    sendCommand(endPage);
    sendCommand(0x00);
    sendCommand(0xFF);
}


//activateScroll():
void Lumi::activateScroll ()
{
    sendCommand(Lumi_Activate_Scroll_Cmd);
}


//deactivateScroll():
void Lumi::deactivateScroll ()
{
    sendCommand(Lumi_Dectivate_Scroll_Cmd);
}


//setNormalDisplay():
void Lumi::setNormalDisplay ()
{
    sendCommand(Lumi_Normal_Display_Cmd);
}


//setInverseDisplay():
void Lumi::setInverseDisplay ()
{
    sendCommand(Lumi_Inverse_Display_Cmd);
}


//setAddressMode(): preserve addressing mode for display.
//newAddressingMode (IN): new address mode.
void Lumi::setAddressMode (char newAddressingMode) {
    if (addressingMode != newAddressingMode) {
        oldAddressingMode = addressingMode;
        addressingMode = newAddressingMode;
        sendCommand(0x20);      //set addressing mode
        sendCommand(addressingMode);
    }
}


//restoreAddressMode(): restore addressing mode if different & return it.
char Lumi::restoreAddressMode () {
  if (addressingMode != oldAddressingMode) {
      addressingMode = oldAddressingMode;
      oldAddressingMode = addressingMode;
      sendCommand(0x20);      //set addressing mode
      sendCommand(addressingMode);
  }

  return addressingMode;
}


//drawDirect(): Run before any graphics to ensure we're in the right address mode.
void Lumi::drawDirect (bool state) {
  if (state) {
      setAddressMode(PAGE_MODE);
  } else
      restoreAddressMode();
}


//drawDirectPixel(): draws pixel @ (x, y).  Color is 0 or 1.    Depracated.
/* void Lumi::drawDirectPixel (unsigned char x, unsigned char y, unsigned char p_color) {
    sendCommand(0xB0 + y);                    //set page address
    sendCommand(x % 16);                      //set column lower address
    sendCommand(0x10 + (int)(x / 16));        //set column higher address
    sendData(p_color);
} */


//drawLine():
void Lumi::drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    SWAP_VARS(x0, y0);
    SWAP_VARS(x1, y1);
  }

  if (x0 > x1) {
    SWAP_VARS(x0, x1);
    SWAP_VARS(y0, y1);
  }

  uint8_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


//lineH(): horizontal line.
void Lumi::drawLineH (uint8_t x, uint8_t y, uint8_t width, uint8_t color) {
  drawLine(x, y, x + width, y, color);
}


//lineV(): vertical line.
void Lumi::drawLineV (uint8_t x, uint8_t y, uint8_t height, uint8_t color) {
  drawLine(x, y, x, y + height, color);
}


//drawCircle():
void Lumi::drawCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color) {
  //TODO - find a way to check for no overlapping of pixels so that XOR draw mode will work perfectly
  int8_t f = 1 - radius;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * radius;
  int8_t x = 0;
  int8_t y = radius;

  drawPixel (x0, y0+radius, color);
  drawPixel (x0, y0-radius, color);
  drawPixel (x0+radius, y0, color);
  drawPixel (x0-radius, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel (x0 + x, y0 + y, color);
    drawPixel (x0 - x, y0 + y, color);
    drawPixel (x0 + x, y0 - y, color);
    drawPixel (x0 - x, y0 - y, color);

    drawPixel (x0 + y, y0 + x, color);
    drawPixel (x0 - y, y0 + x, color);
    drawPixel (x0 + y, y0 - x, color);
    drawPixel (x0 - y, y0 - x, color);
  }
}


//fillCircle():
void Lumi::fillCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color) {
  int8_t f = 1 - radius;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * radius;
  int8_t x = 0;
  int8_t y = radius;

  for (uint8_t i=y0-radius; i<=y0+radius; i++) {
    drawPixel(x0, i, color);
  }

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    for (uint8_t i=y0-y; i<=y0+y; i++) {
      drawPixel(x0+x, i, color);
      drawPixel(x0-x, i, color);
    }
    for (uint8_t i=y0-x; i<=y0+x; i++) {
      drawPixel(x0+y, i, color);
      drawPixel(x0-y, i, color);
    }
  }
}


//drawRect():
void Lumi::drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
  uint8_t tempHeight;

  drawLineH(x, y, width, color);
  drawLineH(x, y + height - 1, width, color);

  tempHeight= height - 2;

  // skip drawing vertical lines to avoid overlapping of pixel that will
  // affect XOR plot if no pixel in between horizontal lines
  if (tempHeight < 1) return;

  drawLineV(x,y + 1, tempHeight, color);
  drawLineV(x + width - 1, y + 1, tempHeight, color);
}


//fillRect():
void Lumi::fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
  for (int i = x; i < x + width; i++) {
    drawLineV(i, y, height, color);
  }
}


/********************************************************************************************************
* Screen Buffer Operations.
********************************************************************************************************/

//clearBuffer():
void Lumi::clearBuffer () {
    memset(screenBuffer, 0, sizeof(screenBuffer));
}

//drawPixel(): draw pixel in the buffer.
void Lumi::drawPixel (uint8_t real_x, uint8_t real_y, uint8_t p_color) {
    int page = (int)(real_y / 8);
    int flipit = 1 << (real_y % 8);   //Flip the Y bit within the 8 bit block.
    screenBuffer[(page * 128) + real_x] = (int)(screenBuffer[((page * 128) + real_x)]) | flipit;       //OR the contents
}


//paintBuffer(): paint buffer on the OLED.
void Lumi::paintBuffer () {
  setAddressMode(HORIZONTAL_MODE);

  for(int i = 0; i < Lumi_ScreenBuffer_Size; i++)
      sendData(screenBuffer[i]);

  restoreAddressMode();
}
