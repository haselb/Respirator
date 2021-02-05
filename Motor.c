/*
 * Motor.c
 *
 *  Created on: 4 Feb 2021
 *      Author: haselb
 */

#include <Dave.h>

uint8_t data[2]={0};

void update_motor(void)
{
	  UART_Transmit(&UART_0, data, sizeof(data));
}
