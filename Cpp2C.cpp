/*
 * Cpp2C.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: haselb
 */

#include "DPS368\Dps368.h"
#include "sfm3200\sfm3000wedo.h"


extern "C" {
#include "Has_misc.h"
}

// Global Variables
// Dps368 Object
Dps368 obj_DPS368 = Dps368();

// SFM3200 Object

SFM3000wedo obj_SFM3200 = SFM3000wedo(S_SFM3200.DevID);



extern "C"
{
	void begin_DPS368(uint8_t I2C_address)			{return obj_DPS368.begin(I2C_address);}
//	int16_t startMeasureBothCont_DPS368(uint8_t temp_mr,uint8_t temp_osr, uint8_t prs_mr, uint8_t prs_osr)
//	{return obj_DPS368.startMeasureBothCont(temp_mr, temp_osr, prs_mr, prs_osr);}

//	int16_t getContResults_DPS368(float *tempBuffer,uint8_t tempCount,float *prsBuffer, uint8_t prsCount)
//  {return obj_DPS368.getContResults(*tempBuffer, tempCount, *prsBuffer, prsCount);}

	int16_t measPressure_DPS368(float *result, uint8_t oversamplingRate) {return obj_DPS368.measurePressureOnce( *result, oversamplingRate);}
//	int16_t startMeasureTemperatureOnce_DPS368(void) {return obj_DPS368.startMeasureTempOnce(void);}
	int16_t measTemperature_DPS368(float *result, uint8_t oversamplingRate) {return obj_DPS368.measureTempOnce( *result, oversamplingRate);}

	void begin_SFM3200() 							{return obj_SFM3200.init();}
	uint16_t measFlow_SFM3200()						{return obj_SFM3200.getvalue();}
}
