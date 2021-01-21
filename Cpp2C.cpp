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
	int16_t measPressure_DPS368(float *i,uint8_t j) {return obj_DPS368.measurePressureOnce( *i, j);}
	void begin_SFM3200() 							{return obj_SFM3200.init();}
	uint16_t measFlow_SFM3200()						{return obj_SFM3200.getvalue();}
}
