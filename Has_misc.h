/*
 * Has_misc.h
 *
 *  Created on: Oct 13, 2015
 *      Author: haselb
 */

#ifndef HAS_MISC_H_
#define HAS_MISC_H_

#include <Dave.h>


#define ON 1
#define OFF 0

extern const char* WeekDay[];

extern volatile uint8_t mainloop_ticks;
extern XMC_RTC_TIME_t timeval;

extern void RTC_init(void);
extern void delay100us(uint32_t dwUs);
extern void update_Pressure(void);
extern void update_Flow(void);



/**
* @ingroup FLAG ARRAY
*
* @brief Flags for whole system Respiratory
*/
typedef struct FLAG_ARRAY
{
	uint16_t KEY_UP					:1; //!< flag for keypressed
	uint16_t KEY_DOWN				:1; //!< flag for keypressed
	uint16_t KEY_STOP				:1;	//!< flag for keypressed
	uint16_t toggle_W				:1; //!< toggle doubledot in time display
	uint16_t res12					:1; //!<
	uint16_t res11					:1; //!<
	uint16_t res10					:1; //!<
	uint16_t res9					:1; //!<
	uint16_t res8					:1; //!<
	uint16_t res7					:1; //!<
	uint16_t res6					:1; //!<
	uint16_t res5					:1; //!<
	uint16_t res4					:1; //!<
	uint16_t res3					:1; //!<
	uint16_t res2					:1; //!<
	uint16_t res1					:1; //!<
}FLAG_ARRAY_t;

extern volatile FLAG_ARRAY_t f;



/**
* @ingroup STRUCT_VALUE_t
*
* @brief commonly used struct for different values of a sensor
*/
typedef struct
{
	float raw_value;	//!< value_raw is the current acquired raw value of sensor
	float ave_value;	//!< is the smoothed value of exponential average
	float ave_value_old;//!< last smoothed value
	float ave_factor;	//!< smoothing coefficient within range 0 < alpha < 1 (memory decay rate); 1 is neutral
	float max_value;	//!< boundary, prevent from panic values or outliers
	float min_value;	//!< boundary,prevent from panic values or outliers
	float tre_value;	//!< trend smoothed value of exponential average
	float tre_value_old;//!< last trend value
	float tre_factor;	//!< trend coefficient within range  0 < beta < 1 ; 1 is neutral
	uint8_t tre_char; //!< trend indicator up-no-dwn
}STRUCT_VALUE_t;

// Pressure Sensor DPS368
 struct pressure
{
	STRUCT_VALUE_t pressure;//!< pressure
	uint8_t oversampling;	//!< oversampling factor
	uint8_t DevID;			//!< if I2C sensor
	uint8_t location;		//!< where is sensor located
	uint8_t status;			//!< status of sensor
};
extern struct pressure S_DPS368;

// Flow Sensor SFM3200
 struct flow
{
	STRUCT_VALUE_t flow; 	//!< pressure
	int16_t offset;			//!< offset factor
	float scale;			//!< Scale factor for Air and N2 is 140.0, O2 is 142.8
	uint8_t DevID;			//!< if I2C sensor
	uint8_t location;		//!< where is sensor located
	uint8_t status;			//!< status of sensor
};
extern struct flow S_SFM3200;




#endif /* HAS_MISC_H_ */
