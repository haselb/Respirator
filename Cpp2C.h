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
	int16_t startMeasureBothCont_DPS368(uint8_t temp_mr,uint8_t temp_osr, uint8_t prs_mr, uint8_t prs_osr);
	int16_t getContResults_DPS368(float *tempBuffer,uint8_t tempCount,float *prsBuffer, uint8_t prsCount);
	 int16_t measPressure_DPS368(float *result, uint8_t oversamplingRate);
//	 int16_t startMeasureTemperatureOnce_DPS368(void);
	 int16_t measTemperature_DPS368(float *result, uint8_t oversamplingRate);
	 void begin_SFM3200();
	 uint16_t measFlow_SFM3200();
//}


#endif /* CPP2C_H_ */
