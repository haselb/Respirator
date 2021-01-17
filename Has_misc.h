/*
 * Has_misc.h
 *
 *  Created on: Oct 13, 2015
 *      Author: haselb
 */

#ifndef HAS_MISC_H_
#define HAS_MISC_H_

#include <Dave.h>

typedef struct
{
	float raw_value;		/* direct from HAL	*/
	float ave_value;		/* nominal value 	*/
	float ave_value_old;	/* for averaging 	*/
	float max_value;		/* boundary			*/
	float min_value;		/* boundary			*/
	uint8_t ave_factor;		/* filter coeff, 2^n*/
	uint8_t oversampling;	/*oversampling factor */
	uint8_t	location;		/* where is sensor located */
	int16_t status;     /* 0..OK, 1-6..reading errors, 7..sensor is cutted off and value is sanitized */
	uint8_t DevID;		/* if I2C sensor 		*/
}STRUCT_SENSOR_t;

extern STRUCT_SENSOR_t Pressure;

#define ON 1
#define OFF 0

extern volatile uint8_t mainloop_ticks;
extern XMC_RTC_TIME_t timeval;

extern void RTC_init(void);
extern void delay100us(uint32_t dwUs);
extern void update_Pressure(void);


#endif /* HAS_MISC_H_ */
