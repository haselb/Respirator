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
	 void begin_SFM3200();
	 uint16_t measFlow_SFM3200();
//}


#endif /* CPP2C_H_ */
