/*
 Copyright (C) 2014 G. Spanos <spaniakos@gmail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
#include "TempSensor_config.h"
#include "TempSensor.h"

/****************************************************************************/

TempSensor::TempSensor(uint8_t pin,float Thres){
		pinTemp = pin;
		temperature = 0;
		sensorValue = 0;
		Old_temperature = 0;
		Rensor = 0;
		TempeThres = Thres;
}

TempSensor::TempSensor(uint8_t pin){
		pinTemp = pin;
		temperature = 0;
		sensorValue = 0;
		Old_temperature = 0;
		Rensor = 0;
		TempeThres = 0.10;
}
	
void TempSensor::begin(){
	pinMode(pinTemp, OUTPUT);
}

void TempSensor::Read_Temperature(){
	sensorValue = analogRead(pinTemp);
	#if defined(SERIAL_DEBUG_TEMP)
		printf_P(PSTR("sensorValue: %i\n"), sensorValue);
	#endif
}
	
float TempSensor::Sensor_to_Temp(){
	Read_Temperature();
	CalcRensor();
	temperature = 1/(log(Rensor/10000)/B+1/298.15)-273.15;
	#if defined(SERIAL_DEBUG_TEMP)
			printf_P(PSTR("temperature: %f\n"), temperature);
	#endif
}
	
void TempSensor::Save_Old(){
	#if defined(SERIAL_DEBUG_TEMP)
			printf_P(PSTR("old temp saved: %f <- %f\n"), temperature,Old_temperature);
	#endif
	Old_temperature = temperature;
}
	
int TempSensor::cmp_values(){
	#if defined(SERIAL_DEBUG_LUX)
			printf_P(PSTR("\nTests 1: %f \t 2: %f \t Thres: %f \n"), (temperature - Old_temperature),(Old_temperature - temperature),TempeThres);
	#endif
	if ((temperature - Old_temperature >= TempeThres) || (Old_temperature - temperature >= TempeThres)){
		Save_Old();
		return 1;
	}else return 0;
}

float TempSensor::Value(){
	return temperature;
}

float TempSensor::Old_Value(){
	return Old_temperature;
}

void TempSensor::CalcRensor(){
	Rensor = (float)(1023-sensorValue)*10000/sensorValue;
	#if defined(SERIAL_DEBUG_TEMP)
		printf_P(PSTR("Rensor: %f\n"), Rensor);
	#endif
}

float TempSensor::get_Rensor(){
	return Rensor;
}

float TempSensor::get_Threshold(){
	return TempeThres;
}

void TempSensor::calibrate(){
	Sensor_to_Temp();
	cmp_values();
	Sensor_to_Temp();
	cmp_values();
	Sensor_to_Temp();
	cmp_values();
}


