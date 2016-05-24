
#include "DisplayManager.h"
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <LTask.h>

#include "Wire.h"
#include "Icons.h"

//3 Graphics Drivers for separate displays.
//#include "../display_drivers/lumi/Lumi.h"
//#include "../display_drivers/lumi_big/LumiBig.h"
//#include "../display_drivers/lumi_jumbo/LumiJumbo.h"


//*******************************************************
// Rewrite required to reduce code redundancy.
//*******************************************************

/*
--------------------------------------------------------
STATIC CLASS MEMBER INITIALIZATION
--------------------------------------------------------
*/

bool DisplayManager::_is_initialized = false;
char DisplayManager::_display_lines[10][40];

//Use default setting.
displayDevice_t DisplayManager::_display_device = CONFIG_SYSTEM_DEFAULT_DISPLAY;

//Displays.
Lumi DisplayManager::_lumi;
LumiBig DisplayManager::_lumiBig;


/*
--------------------------------------------------------
PUBLIC FUNCTIONS
--------------------------------------------------------
*/


//setDisplayDevice(): set display type.
void DisplayManager::setDisplayDevice(displayDevice_t display_device = CONFIG_SYSTEM_DEFAULT_DISPLAY) {
	_display_device = display_device;
}


//init()
void DisplayManager::init(){
	switch(_display_device) {
		case disp_OLED_96x96: {
			Wire.begin();
			_lumiBig.init();
			_lumiBig.clearDisplay();
			_lumiBig.clearBuffer();					//Clear painting buffer.
			break;
		}

		case disp_OLED_128x64: {
			Wire.begin();
			_lumi.init();
			_lumi.clearDisplay();
			_lumi.clearBuffer();					//Clear painting buffer.
			break;
		}

		case disp_TFT: {

		}
	}

	_is_initialized = true;
}


//clearDisplay()
void DisplayManager::clearDisplay() {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.clearDisplay();
			break;
		}

		case disp_OLED_128x64: {
			_lumi.clearDisplay();
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::setTextXY(unsigned char row, unsigned char col) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.setTextXY(row, col);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.setTextXY(row, col);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::putString(const char * str1, unsigned char row, unsigned char column) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawString(str1, row, column);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawString(str1, row, column);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::drawIcon(int icon_id) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.setInverseDisplay();

			int img_size = 96*96/8;

			if( icon_id == ICON_LOGO_SIGNAL ){
				_lumiBig.drawBitmap(icon_logo_signal, img_size);

			} else if( icon_id == ICON_WIFI_SET ){
				_lumiBig.drawBitmap(icon_wifi_set, img_size);

			} else if( icon_id == ICON_WIFI_WAITING ){
				_lumiBig.drawBitmap(icon_wifi_waiting, img_size);

			} else if( icon_id == ICON_CELLULAR_SET ){
				_lumiBig.drawBitmap(icon_cellular_set, img_size);

			} else if( icon_id == ICON_CELLULAR_WAITING ){
				_lumiBig.drawBitmap(icon_cellular_set, img_size);

			} else if( icon_id == ICON_ROTATE ){
				_lumiBig.drawBitmap(icon_rotate, img_size);

			} else if( icon_id == ICON_SERVER_WAITING ){
				_lumiBig.drawBitmap(icon_server_waiting, img_size);

			} else if( icon_id == ICON_SERVER_SET ){
				_lumiBig.drawBitmap(icon_server_set, img_size);
			}
		}

		case disp_OLED_128x64: {
			_lumi.setInverseDisplay();

			//Icon support required.
		}

		case disp_TFT: {

		}

		/* Pause operation for 1 second to let the icon sit on screen */

		delay(1000);
	}
}


void DisplayManager::drawPixel (uint8_t real_x, uint8_t real_y, uint8_t p_color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawPixel(real_x, real_y, p_color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawPixel(real_x, real_y, p_color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawLine (x0, y0, x1, y1, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawLine (x0, y0, x1, y1, color);
			break;
		}

		case disp_TFT: {
		}
	}
}


void DisplayManager::drawLineH (uint8_t x, uint8_t y, uint8_t width, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawLineH (x, y, width, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawLineH (x, y, width, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::drawLineV (uint8_t x, uint8_t y, uint8_t height, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawLineV (x, y, height, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawLineV (x, y, height, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::drawCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawCircle (x0, y0, radius, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawCircle (x0, y0, radius, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::fillCircle (uint8_t x0, uint8_t y0, uint8_t radius, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.fillCircle (x0, y0, radius, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.fillCircle (x0, y0, radius, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::drawRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.drawRect(x, y, width, height, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.drawRect(x, y, width, height, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::fillRect (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.fillRect(x, y, width, height, color);
			break;
		}

		case disp_OLED_128x64: {
			_lumi.fillRect(x, y, width, height, color);
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::paintBuffer () {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.paintBuffer();
			break;
		}

		case disp_OLED_128x64: {
			_lumi.paintBuffer();
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::clearBuffer () {
	switch(_display_device) {
		case disp_OLED_96x96: {
			_lumiBig.clearBuffer();
			break;
		}

		case disp_OLED_128x64: {
			_lumi.clearBuffer();
			break;
		}

		case disp_TFT: {

		}
	}
}


void DisplayManager::update(){
    /* Do nothing */
}


void DisplayManager::writeText(const char text[]){
	if (_is_initialized) {
		int curr_x = 0;
		int curr_y = 0;

		String out_string = String(text);

		String write_buffer = "";
		int screen_character_width = 10;

		//Simulate scrolled lines.
		for (int tl=8; tl>=0; tl--) {
			if (tl == 0)
				strcpy(_display_lines[tl], text);
			else
				strcpy(_display_lines[tl], _display_lines[tl - 1]);
		}

		switch(_display_device) {
			case disp_OLED_96x96: {
				//_lumiBig.clearDisplay();
				_lumiBig.paintBuffer();													//Paint buffer instead of clearing screen: allow for text + gfx.

				for (int tl=0; tl<=8; tl++) {
					_lumiBig.drawString(_display_lines[tl], tl * 2, 0);
				}
				break;
			}

			case disp_OLED_128x64: {
				//_lumi.clearDisplay();
				_lumi.paintBuffer();													//Paint buffer instead of clearing screen: allow for text + gfx.

				for (int tl=0; tl<=8; tl++) {
					_lumi.drawString(_display_lines[tl], tl, 0);
				}
				break;
			}

			case disp_TFT: {

			}
		}
	}
}
