/*
 Copyright (C) 2014 G. Spanos <spaniakos@gmail.com

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 * 
 */

#ifndef __TempSensor_CONFIG_H__
#define __TempSensor_CONFIG_H__

	/*** USER DEFINES:  ***/  
	//#define SERIAL_DEBUG_TEMP
	/**********************/
	#define B 3975 // B value of the thermistor
	
	#if defined (__ARDUINO_X86__)
		#define printf_P printf
		#define PSTR(x) (x)
	#endif
	#include <stdint.h>
	#include <stdio.h>
	#include <string.h>
	#include <SPI.h>
	#include <math.h>

#endif //TempSensor_CONFIG
