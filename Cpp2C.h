/*
 * Cpp2C.h
 *
 *  Created on: Jan 19, 2018
 *      Author: haselb
 */

#ifndef CPP2C_H_
#define CPP2C_H_



// extern STRUCT_SENSOR_t S_DPS368;

//extern "C"
//{
	 void begin_DPS368(uint8_t I2C_Address);
	 int16_t measPressure_DPS368(float *i,uint8_t j);
//}

//	uint16_t begin_APDS9960() {return obj_APDS9960.init();}
//	uint16_t enableLightSensor_APDS9960(bool i) 	{return obj_APDS9960.enableLightSensor(i);}
//	uint16_t getMode_APDS9960()						{return obj_APDS9960.getMode();}
//	char get_BMP180_Temperature(double *p);
//	char start_BMP180_Pressure(char i);
//	char get_BMP180_Pressure(double *p,double t);
//	double calc_BMP180_absPressure(double P, double A);


#endif /* CPP2C_H_ */
