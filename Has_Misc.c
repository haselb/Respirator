/*
 * Has_Misc.c
 *
 *  Created on: Oct 13, 2015
 *      Author: haselb
 */

#include <Dave.h>
#include <stdio.h>
#include "Has_Misc.h"
#include "Cpp2C.h"
#include "statistics.h"
#include "LCM.h"


volatile uint32_t timetick_count=0;	// global variable for time tick count
volatile uint8_t mainloop_ticks=0;
XMC_RTC_TIME_t timeval;
const char* WeekDay[]={"So","Mo","Di","Mi","Do","Fr","Sa"};

volatile FLAG_ARRAY_t f;


/*!
 * struct for Pressure measurement
 */
struct pressure S_DPS368 =
{
		.pressure.ave_value		= 0.0f,	/* default value				*/
		.pressure.max_value		= 0.0f,	/* max value for temp? 			*/
		.pressure.min_value		= 0.0f,		/* min value    				*/
		.pressure.ave_value_old = 0.0f,		/* take same value as ave_value	*/
		.pressure.ave_factor	= 0.08f,		/* weight for average filter	*/
		.pressure.tre_value		= 0.0f,
		.pressure.tre_value_old	= 0.0f,
		.pressure.tre_factor	= 0.05f,
		.temp_mr				= 2U, /* 2^temp_mr measurement results per second (value from 0 to 7)*/
		.temp_osr				= 2U, /* 2^temp_osr temperature oversampling rate per result (value from 0 to 7) */
		.prs_mr					= 2U, /* 2^prs_mr measurement results per second (value from 0 to 7)*/
		.prs_osr				= 2U, /* 2^prs_osr pressure oversampling rate per result (value from 0 to 7) */
		.location				= 1U,		/* where is the sensor located	*/
		.DevID					= 0xEEU,	/* I2C-Dev.Addr. in 8 bit notation */
		.status					= 0x00U		/* different states, 0x00 is OK	*/
};

/*!
 * struct for Flow measurement
 */
struct flow S_SFM3200 =
{
		.flow.ave_value		= 00.0f,	/* default value				*/
		.flow.max_value 		= 00.0f,	/* max value for temp? 			*/
		.flow.min_value 		= 0.0f,		/* min value    				*/
		.flow.ave_value_old 	= 0.0f,		/* take same value as ave_value	*/
		.flow.ave_factor		= 8U,		/* weight for average filter	*/
		.offset			=32000U,	/* Offset for the sensor		*/
		.scale			=140.0f,		/* Scale factor for Air and N2 is 140.0, O2 is 142.8*/
		.location		= 1U,		/* where is the sensor located	*/
		.DevID			= 0x80U,	/* I2C-Dev.Addr. in 8 bit notation */
		.status			= 0x00U		/* different states, 0x00 is OK	*/
};



/*!
 * @brief 	   Callback Function initiated by PIN IRQ, called at key pressed.
 * @param[in]  None.
 * @param[out] None.
 * @retval     None.
 * @pre        DAVE RTC-App is utilized.
 * @post       Approproiate flag is set.
 * @attention  -
 * @note       -
 */
void PinIRQHandler_UP(void)
{
  f.KEY_UP=1;
}


/*!
 * @brief 	   Callback Function initiated by PIN IRQ, called at key pressed.
 * @param[in]  None.
 * @param[out] None.
 * @retval     None.
 * @pre        DAVE RTC-App is utilized.
 * @post       Approproiate flag is set.
 * @attention  -
 * @note       -
 */
void PinIRQHandler_DOWN(void)
{
  f.KEY_DOWN=1;
}


/*!
 * @brief 	   Callback Function initiated by PIN IRQ, called at key pressed.
 * @param[in]  None.
 * @param[out] None.
 * @retval     None.
 * @pre        DAVE RTC-App is utilized.
 * @post       Approproiate flag is set.
 * @attention  -
 * @note       -
 */
void PinIRQHandler_STOP(void)
{
  f.KEY_STOP=1;
}



/*!
 * @brief 	   Callback Function initiated by Timer IRQ, called all 1ms.
 * @param[in]  None.
 * @param[out] None.
 * @retval     None.
 * @pre        DAVE RTC-App is utilized.
 * @post        variable timetick_count is incremented.
 * @attention  -
 * @note       -
 */
 void TimerIRQHandler(void)
 {

 	/* Acknowledge the period match interrupt*/
	 TIMER_ClearEvent(&TIMER_0);

 	/* Increment time tick count */
 	timetick_count++;

 }

 /*!
  * @brief 	   Function to wait for n 100µs.
  * @param[in]  uint32_t dwUs
  * @param[out] None
  * @retval     void
  * @pre        initiate TIMER_0-IRQ before.
  * @post       None
  * @attention  None
  * @note       This routine serves the TIMER_0.
  */
 void delay100us(uint32_t dwUs)
 {
	 timetick_count=0;
	 TIMER_Start(&TIMER_0);
	 while(timetick_count < dwUs);
	  {
	    while(TIMER_GetInterruptStatus(&TIMER_0));
	    TIMER_Stop(&TIMER_0);
	  }

 }

/*!
* @brief 	   IRQ_Handler initiated by DAVE IRQ-Service and is invoked after RTC0 event.
* @param[in]  None
* @param[out] None
* @retval     void
* @pre        requires IRQ, initiated by DAVE
* @post       Function increments global variables @ref mainloop_ticks
* @attention  None
* @note       This routine is the callback function of DAVE. It is invoked by the ISR generated from DAVE.
*/
void RTC_Time_Handler(void) //RTC_IRQ_Handler
{

	mainloop_ticks++;
}

/*!
 * @brief 	   Function sanitizes @ref timeval struct and is invoked in init cycle.
 * @param[in]  None
 * @param[out] None
 * @retval     void
 * @pre        invoked in init cycle
 * @post       Function updates global variable @ref timeval
 * @attention  None
 * @note       This routine initializes @ref timeval values in RTC_0 App.
 */
void RTC_init(void)
{
	timeval.seconds=0;
	timeval.minutes=0;
	timeval.hours=12;
	timeval.days=15;
	timeval.month=1;
	timeval.year=2021;
	RTC_Stop();
	RTC_SetTime(&timeval);
	RTC_Start();
}


/*!
 * @brief 	   Function updates temperature value
 * @param[in]  None
 * @param[out] None
 * @retval     void
 * @pre        invoked in main loop
 * @post       Function updates raw value of sensor and calculates average value
 * @attention  None
 * @note       None
 */
void update_Temperature(void)
{


	S_DPS368.status = measTemperature_DPS368(&S_DPS368.temperature.raw_value, S_DPS368.temp_osr);

	if(S_DPS368.status != 0)
	{
		sprintf(buffer,"DPS368 reports 0x%02X", S_DPS368.status);
		LCD_string(4,0,buffer);
	}
}


/*!
 * @brief 	   Function updates pressure value
 * @param[in]  None
 * @param[out] None
 * @retval     void
 * @pre        invoked in main loop
 * @post       Function updates raw value of sensor and calculates average value
 * @attention  None
 * @note       None
 */
void update_Pressure(void)
{

	 S_DPS368.status = measPressure_DPS368(&S_DPS368.pressure.raw_value, S_DPS368.prs_osr);

	   	// calculate and update average values and trend sign if available
	 //calc_double_exp_smoothing(&S_DPS368.pressure);

}


/*!
 * @brief 	   Function updates flow value
 * @param[in]  None
 * @param[out] None
 * @retval     void
 * @pre        invoked in main loop
 * @post       Function updates raw value of sensor and calculates average value
 * @attention  None
 * @note       None
 */
void update_Flow(void)
{
	S_SFM3200.flow.raw_value = (measFlow_SFM3200() - S_SFM3200.offset)/ S_SFM3200.scale;

	calc_double_exp_smoothing(&S_SFM3200.flow);

}
