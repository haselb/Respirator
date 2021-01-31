
/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2019, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2014-06-16:
 *     - Initial version<br>
 * 2015-08-28:
 *     - Added CLOCK_XMC1_Init conditionally
 * 2018-08-08:
 *     - Add creation of projectData.bak file
 * 2019-01-30:
 *     - Fix creation of projectData.bak file
 * 2019-04-29:
 *     - Make DAVE_Init() weak, the user can reimplement the function
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "DAVE.h"

/***********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/*******************************************************************************
 * @brief This function initializes the APPs Init Functions.
 *
 * @param[in]  None
 *
 * @return  DAVE_STATUS_t <BR>
 ******************************************************************************/
__WEAK DAVE_STATUS_t DAVE_Init(void)
{
  DAVE_STATUS_t init_status;
  
  init_status = DAVE_STATUS_SUCCESS;
     /** @Initialization of APPs Init Functions */
     init_status = (DAVE_STATUS_t)CLOCK_XMC4_Init(&CLOCK_XMC4_0);

  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of I2C_MASTER APP instance I2C_MASTER_0 */
	 init_status = (DAVE_STATUS_t)I2C_MASTER_Init(&I2C_MASTER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of RTC APP instance RTC_0 */
	 init_status = (DAVE_STATUS_t)RTC_Init(&RTC_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of TIMER APP instance TIMER_0 */
	 init_status = (DAVE_STATUS_t)TIMER_Init(&TIMER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance INTERRUPT_0 */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&INTERRUPT_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of SYSTIMER APP instance SYSTIMER_0 */
	 init_status = (DAVE_STATUS_t)SYSTIMER_Init(&SYSTIMER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_O_LED_HB */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_O_LED_HB); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_O_LCD_RS */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_O_LCD_RS); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_O_LCD_RW */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_O_LCD_RW); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_O_LCD_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_O_LCD_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DIGITAL_O_LCD_RESET */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DIGITAL_O_LCD_RESET); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PIN_INTERRUPT APP instance PIN_INTERRUPT_STOP */
	 init_status = (DAVE_STATUS_t)PIN_INTERRUPT_Init(&PIN_INTERRUPT_STOP); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PIN_INTERRUPT APP instance PIN_INTERRUPT_DOWN */
	 init_status = (DAVE_STATUS_t)PIN_INTERRUPT_Init(&PIN_INTERRUPT_DOWN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PIN_INTERRUPT APP instance PIN_INTERRUPT_UP */
	 init_status = (DAVE_STATUS_t)PIN_INTERRUPT_Init(&PIN_INTERRUPT_UP); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of BUS_IO APP instance BUS_O_LCD_D */
	 init_status = (DAVE_STATUS_t)BUS_IO_Init(&BUS_O_LCD_D); 
   }  
  return init_status;
} /**  End of function DAVE_Init */

