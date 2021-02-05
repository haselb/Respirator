/*
 * init.c
 *
 *  Created on: 15 Jan 2021
 *      Author: hasib
 */

#include <Dave.h>
#include <stdio.h>		// for sprintf
#include "Has_misc.h"
#include "HAL\HAL_i2c.h"
#include "Cpp2C.h"
#include "LCM.h"
#include "doxygen\doxy.h"

uint32_t timer_1_of_8;

void init()
{



	RTC_init(); //Assert Real Time Clock
	timer_1_of_8 = SYSTIMER_CreateTimer(50000, SYSTIMER_MODE_ONE_SHOT, SW_IRQ_1, NULL); //SW-WDG for I2C

	// LCM - Welcome splash screen
    LCD_init();    //initialize LC Module
    delay100us(100);
    sprintf(buffer,"Respirator V %d.%d.%d",MAJOR_VERSION,MINOR_VERSION,PATCH_VERSION);  // defined in doxy.h
    LCD_string(0,0,buffer);

    sprintf(buffer,"   by Kofler, 2021 ");
    LCD_string(1,0,buffer);

  //Call begin to initialize Dps368PressureSensor
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  //Dps368PressureSensor.begin(Wire, 0x76);
  //Use the commented line below instead of the one above to use the default I2C address.
  //if you are using the Pressure 3 click Board, you need 0x76

	begin_DPS368(S_DPS368.DevID);
//	S_DPS368.status = startMeasureBothCont_DPS368(S_DPS368.temp_mr, S_DPS368.temp_osr, S_DPS368.prs_mr, S_DPS368.prs_osr);

//	begin_SFM3200(S_SFM3200.DevID);

}



