#ifndef DisplayManager_haaa
#define DisplayManager_haaa

  #define ICON_LOGO_SIGNAL 0
  #define ICON_LOGO_TWILIO 1
  #define ICON_WIFI_WAITING 2
  #define ICON_WIFI_SET 3
  #define ICON_CELLULAR_WAITING 4
  #define ICON_CELLULAR_SET 5
  #define ICON_ROTATE 6
  #define ICON_SERVER_WAITING 7
  #define ICON_SERVER_SET 8

  #define BRIGHTNESS_LOW 0
  #define BRIGHTNESS_MEDIUM 8
  #define BRIGHTNESS_HIGH 15

  #include <Wire.h>

  #include "system.h"

  //2 displays supported with Jumbo TF W-I-P.
  #include "Lumi.h"                         //128x64 OLED.
  #include "LumiBig.h"                      //96x96 OLED.

  //Display type.
  typedef enum {
    disp_UNKNOWN = -1,
    disp_OLED_96x96 = 1,
    disp_OLED_128x64 = 2,
    disp_TFT = 3,
    disp_TEXT_LCD = 4
  } displayDevice_t;

  class DisplayManager {

    private:
      /* Make constructor private to prohibit instantiation */

      DisplayManager();

    protected:
      static bool         _is_initialized;
      static char         _display_lines[10][40];
      static displayDevice_t    _display_device;

      //Graphics displays supported.
      static Lumi         _lumi;
      static LumiBig        _lumiBig;
      //static LumiJumbo      _lumiJumbo;

    public:
      static void init();
      static void setDisplayDevice(displayDevice_t display_device);
      static void clearDisplay();
      static void setTextXY(unsigned char row, unsigned char col);
      static void putString(const char * str1, unsigned char row, unsigned char column);

      //Graphics Methods.
        static void drawPixel (uint8_t real_x, uint8_t real_y, uint8_t p_color);
        static void drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
        static void drawLineH (uint8_t x, uint8_t y, uint8_t width, uint8_t color);
        static void drawLineV (uint8_t x, uint8_t y, uint8_t height, uint8_t color);
        static void drawCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color);
        static void fillCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color);
        static void drawRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
        static void fillRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

        static void paintBuffer();
        static void clearBuffer();

        static void ptest();

      static void update();
      static void drawIcon(int icon_id);
      static void writeText(const char text[]);
  };

#endif
