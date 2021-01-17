/*
 * HAL_i2c.c
 *
 *  Created on: Dec 26, 2017
 *      Author: haselb
 */


#include "HAL_i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
//#include "MISC.h"
#include <time.h>
#include "Has_misc.h"
//#include "Cpp2C.h"


volatile uint8_t tx_completion_0 = 0;
volatile uint8_t rx_completion_0 = 0;
volatile bool flag_I2C_NACK=0;
volatile bool flag_eject_at_I2C_NACK=0;
uint32_t timer_1_of_8;




//IRQ-Handler for SYSTIMER, initiated by function Soft_WDG (checkout SYSTIMER_XMC45.PDF)
void SW_IRQ_1 (void *args)
{
		flag_eject_at_I2C_NACK=1;

		I2C_MASTER_AbortTransmit(&I2C_MASTER_0);
		I2C_MASTER_AbortReceive(&I2C_MASTER_0);
//		I2C_MASTER_SendStop(&I2C_MASTER_0);
		I2C_MASTER_Init(&I2C_MASTER_0);
}


//on_or_off: if 0:off; 1: on
void Soft_WDG_1 (bool on_or_off)
{
	if(on_or_off)
	{
		SYSTIMER_StartTimer(timer_1_of_8);
	}
	else
	{
		SYSTIMER_StopTimer(timer_1_of_8);
	}
}


//IRQ-Handler of I2C-MASTER-Interface  initiated by DAVE
void tx_callback_0(void)
{
       tx_completion_0 = 1;
}

//IRQ-Handler of I2C-Interface MASTER initiated by DAVE
void rx_callback_0(void)
{
       rx_completion_0 = 1;
}

//IRQ-Handler MASTER for detecting missing/not responding slave  initiated by DAVE
void I2C_NACK_IRQ_Handler_0(void)
{
	flag_I2C_NACK=1;
	I2C_MASTER_AbortTransmit(&I2C_MASTER_0) ;// before init, abort transmit has to be executed
	I2C_MASTER_AbortReceive(&I2C_MASTER_0);
//	I2C_MASTER_SendStop(&I2C_MASTER_0);
//	I2C_MASTER_Init(&I2C_MASTER_0); // init I2C bus again to respond
}

//IRQ-Handler MASTER for detecting arbitration lost, initiated by DAVE
void I2C_ARB_Lost_IRQ_Handler_0 (void)
{
	flag_I2C_NACK=1;
}

//IRQ-Handler MASTER for detecting errors, initiated by DAVE
void I2C_ERR_IRQ_Handler_0 (void)
{
	flag_I2C_NACK=1;
}






