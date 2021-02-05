/*
 * main.c
 *
 *  Created on: 2021 Jan 15 10:22:28
 *  Author: hasib
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "init.h"
#include "Has_misc.h"
#include "Cpp2C.h"
#include "LCM.h"
#include "motor.h"
//#include "isot_i2c.h"



/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int main(void)
{
  DAVE_STATUS_t status;

   status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }
  init(); // init all devices and other stuff
  //find_I2C_device();

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	update_Temperature();
	update_Pressure();
//	update_Flow();
	update_motor();
//	update_LCD();


	  while(mainloop_ticks<1);  // main loop endurance is 1 second
	  mainloop_ticks=0;
	  DIGITAL_IO_ToggleOutput(&DIGITAL_O_LED_HB); //toggles : 0 -> 1

  }
}
