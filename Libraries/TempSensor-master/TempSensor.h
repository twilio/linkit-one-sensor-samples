/*
 Copyright (C) 2014 G. Spanos <spaniakos@gmail.com

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * @file TempSensor.h
 *
 * Class declaration for TempSensor and helper enums
 */

#ifndef __TempSensor_H__
#define __TempSensor_H__

#include "TempSensor_config.h"

class TempSensor{
	private:
		uint8_t pinTemp;/**< holds the Pin number of the board */
	    float temperature;/**< holds the temperature value  after the convertion from te reading */
		unsigned int sensorValue;/**< holds the reading value from the sensor */
		float Old_temperature;/**< holds the old temperature value, mainly used from cmp_values */
		float Rensor;/**< holds the rensor value */
		float TempeThres;/**< hold the Threshold, mainly used from cmp_values */
	public:
	/**
	 * class constructor.
	 * 
	 * @param pin uint8_t Number of the pin to be used for reading
	 * @param Thres float value of the threshold that will be used
	 */
	TempSensor(uint8_t pin,float Thres);
	
	/**
	 * class constructor.
	 * 
	 * Threasold initializes to 0,10.
	 * @param pin uint8_t Number of the pin to be used for reading
	 */
	TempSensor(uint8_t pin);//thres inits to 0.10
	
	/**
	 * Initialized the base grove class with the balues given in the constructor.
	 * 
	 */
	void begin(void);
	
	/** reads value from sensor.
	 * the value is saved to sensorValue
	 */
	void Read_Temperature(void);
	
	/** Reads the Value from the pin using 
	 *  @code Read_Temperature(); @endcode
	 *  Calculates the Rensor using
	 *  @code CalcRensor(); @endcode
	 *  end Saves the temperature value. 
	 */
	float Sensor_to_Temp(void);
	
	/** set Old_temperature equal to current temperature.
	 * 
	 */
	void Save_Old(void);
	
	/** compare temperature and OLD_temperature values.
	 *  @return int 0 if equal , 1 if not
	 */
	int cmp_values(void);
	
	/** Gets the Temperature valule.
	 *  @return temperature value.
	 */
	 float Value(void);
	 
	 /** get the Old_temperature value.
	  *  @return OLD_temperature value.
	  */
	 float Old_Value(void);
	 
	 /** Calculate the Rensor.
	  *  The value is saved inside the class.
	  */
	 void CalcRensor();
	 
	 /** GETS the Rensor value.
	  *  @return Rensor value.
	  */
	 float get_Rensor();
	 
	  /** Gets the Threshold.
	  *  @return TempeThres as integer
	  */
	 float get_Threshold();
	 
	 /** calibrate the sensor and readings.
	  *  Does initial readings in order to calibrate the sensor.
	  */
	 void calibrate();
};
#endif //TempSennsor

/**
 * @example Temperature.ino
 * <b>For Arduino</b><br />
 * <b> updated: spaniakos 2015</b><br />
 *
 * In this example a simple reading of the sensor value is printed into Serial.<br />
 * the valueis first converted to Celcius using class functions.
 */

/**
  * @mainpage grove TempSensor (TTC03 Thermistor) library for arduino.
  *
  * @section Goals Design Goals
  *
  * This library is designed to:
  * @li extend the basic grove library
  * @li be able to compare Values in order to optimize the prosses
  *
  *section News News
  *
  * If issues are discovered with the documentation please report them <a href="https://github.com/spaniakos/spaniakos.github.io/issues"> here</a>
  * 
  * @section Useful Useful References
*
* Please refer to:
*
* @li <a href="http://spaniakos.github.io/TempSensor/classTempSensor.html"><b>TempSensor</b> Class Documentation</a>
* @li <a href="https://github.com/spaniakos/TempSensor/archive/master.zip"><b>Download</b></a>
* @li <a href="https://github.com/spaniakos/TempSensor/"><b>Source Code</b></a>
* @li <a href="http://spaniakos.github.io/">All spaniakos Documentation Main Page</a>
*
* @section Board_Support Board Support
*
* Most standard Arduino based boards are supported:
* - Arduino
* - Intel Galileo support
* 
* @section Thermistor_support Thermistor Support
* 
* It supports:
* - The grove Temperature sensor
* - Every Tempererature sensor equiped with the TTC03 Thermistor
*/
