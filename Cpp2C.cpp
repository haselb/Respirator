/*
 * Cpp2C.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: haselb
 */

#include "DPS368\Dps368.h"


extern "C" {
#include "Has_misc.h"
}

// Global Variables
// Dps368 Opject
Dps368 obj_DPS368 = Dps368();


extern "C"
{
STRUCT_SENSOR_t S_DPS368;

	void begin_DPS368(uint8_t I2C_address)			{return obj_DPS368.begin(I2C_address);}
	int16_t measPressure_DPS368(float *i,uint8_t j) {return obj_DPS368.measurePressureOnce( *i, j);}
//	uint8_t start_BMP180_Temp() {return obj_BMP180.startTemperature();}
//	char get_BMP180_Temperature(double *p) 				{return obj_BMP180.getTemperature(*p);}
//	char start_BMP180_Pressure(char i) 					{return obj_BMP180.startPressure(i);}
//	char get_BMP180_Pressure(double *p,double t) 		{return obj_BMP180.getPressure(*p,t);}
//	double calc_BMP180_absPressure(double P, double A)	{return obj_BMP180.sealevel(P,A);}

}
