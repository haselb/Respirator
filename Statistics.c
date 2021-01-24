/*
 * Statistics.c
 *
 *  Created on: 1 Jan 2019
 *      Author: haselb
 */

#include <Dave.h>
#include "Has_misc.h"



// (c) GNU-Free Software Foundation by Harald Kipp
//unsigned long ByteSwap(unsigned long val)
//{
//asm volatile (
//        "eor     r3, %1, %1, ror #16\n\t"
//        "bic     r3, r3, #0x00FF0000\n\t"
//        "mov     %0, %1, ror #8\n\t"
//        "eor     %0, %0, r3, lsr #8"
//        : "=r" (val)
//        : "0"(val)
//        : "r3"
//);
//return val;
//}



/*!
 * @brief 	   Function for calculating double exponential smoothing (second order exponential smoothing)
 * @param[in/out] STRUCT_VALUE_t : object of values, access by object -> member
 * @retval     trend-sign for assigning proper arrow symbol
 * @pre        trend-sign depends on character set of LCM
 * @post		the updated average value represents next forecasted estimated value
 * @attention  be aware of raw_value's least significant bit acquisition jitter if coefficients  \n
 * alpha and beta are determined.
 * @note       algorithmus a.k.a. Holt-Winters double exponential smoothing method. The higher alpha \n
 * the faster method forgets; at 1, filter degenerates. The Smallest Mean Square Error (MSE) (Levenberg-Marquardt LM-Algo) \n
 * could be utilized to calculate both coefficients alpha and beta. Second order IIR Filter.
 */
void calc_double_exp_smoothing(STRUCT_VALUE_t* my)
{
	float fore_cast=0.0;

	my->ave_value = my->ave_factor * my->raw_value + (1 - my->ave_factor) * (my->ave_value_old + my->tre_value_old); 	// level smoothing
	my->tre_value = my->tre_factor * (my->ave_value - my->ave_value_old) + (1 - my->tre_factor) * (my->tre_value_old); 	// estimated trend smoothing
	fore_cast = my->ave_value + my->tre_value; 								// forecast of next value

	my->ave_value = fore_cast;			// the displayed value is a forecasted one
	my->ave_value_old = my->ave_value;	//update old limit value
	my->tre_value_old = my->tre_value;	//update old trend value


}

