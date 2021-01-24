/*
 * Statistics.h
 *
 *  Created on: 1 Jan 2019
 *      Author: haselb
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

/**********************************************************************************************************************
*  Definitions, equates and structures
**********************************************************************************************************************/
/* Minimum value  */
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/* Maximum value  */
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define BEYONDLIMITS(max,a,min) ((((a) < (min)) || ((a) > (max))) ? (1) : (0))
/*!
 * @brief 	   Function to calculate single exponential smoothing of a value (datatype doesnt matter).
 * @param[in]  	1.) ave_value; calculated value
 * 				2.) ave_value_old; former ave_value
 * 				3.) smoothing_factor; range 2^n (1,2,4,8,16,32,64,..) to ease division procedure (lsr)
 * @param[out] None
 * @retval     void
 * @pre        None
 * @post       Macro updates global variable ave_value
 * @attention  None
 * @note       None
 */
#define val_average(ave_value,ave_value_old,ave_factor)\
	do { \
		ave_value = ave_value_old + ((ave_value - ave_value_old) / ave_factor);\
		ave_value_old = ave_value;	\
	} while(0)

/**********************************************************************************************************************
* Global variables
**********************************************************************************************************************/


/**********************************************************************************************************************
* Global Prototypes, external Declarations
**********************************************************************************************************************/

extern void calc_double_exp_smoothing(STRUCT_VALUE_t* my);
#endif /* STATISTICS_H_ */
