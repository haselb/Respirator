/*! *****************************************************************************
 * @file     	doxy.h
 * @brief    	Main file for Doxygen
 * @version 	V1.0
 * @date     	2018-Dec-11
 *
 * @note		(C) GNU GPL
 *
 * @profile     Main page file for any project
 * @description If Doxygen is used, this file provides content of Main Page
 *
 * @par
 * CUAS is supplying this software for use with
 * Infineons microcontrollers. This file can be freely distributed within
 * development tools that are supporting such microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * @originator	Matthias Haselberger
 * @author		Matthias Haselberger
 * @bug			none
 * @attention	none
 * @warning		none
 * @todo		-
 ******************************************************************************/

#ifndef _DOXY_H_
#define _DOXY_H_

/*! \mainpage
 *
 * \brief <b>MTSR_1</b>\n
 * Project Respiratory Machine.\n
 * Prerequisites: Bachelor Project Mrs. Kofler Melanie.\n
 * \par Project description:
 * Mainloop with 1 second.
 *
 * \par Compiler and Switches, Dependencies, Tools
 *
 * Tools for edit, compilation, linking and programming of the sources
 * <ul>
 * <li>DAVE Version 4.4.2</li>
 * <li>Segger JLink Debugger and Programmer V641a</li>
 * <li>Doxygen 1.8.8 and higher</li>
 *
 * </ul>
 *
 * \par Versioning
 *
 * <table>
 * <caption id="multi_row"> Version, History </caption>
 * <tr><th>Nr.   <th> Date		  <th> Comment		</td>
 * <tr><td>0.0.0 <td> 2021-Jan-16 <td> Release first draft, initiate Sensor DPS368 from Infineon Git repository
 * <tr><td>0.0.1 <td> 2021-Jan-17 <td> Hosted at git, added LED1 for Heart Beat Indication, improve I2C Error handling
 * <tr><td>0.1.0 <td> 2021-Jan-21 <td> Add Sensor SFM3200, change Struct for Sensors
 * <tr><td>0.1.1 <td> 2021-Jan-24 <td> Test Workflow with XMC4700 Relax Kit Board add exponential smooting
 * <tr><td>0.1.2 <td> 2021-Jan-31 <td> Add LCM, check DPS368 for I2C-Handling by Oscilloscope, add three PIN-Interrupt KEYs
 * <tr><td>0.1.3 <td> 2021-Feb-05 <td> change I2C Receive to &buffer[0]; DpsClass::readBlock returns regBlock.length;
 * <tr><td>0.1.4 <td> 2021-Jan- <td>
 *
 *
 * <tr><td>1.0.0 <td> 2021-Jan- <td> Fist Release for delivery
 * <tr><td>1.0.1 <td> 2021-Jan- <td>
 * </table>
 *
 */
#define MAJOR_VERSION 0U
#define MINOR_VERSION 1U
#define PATCH_VERSION 3U

 /*! \page Hardware Hardware
 * @{
 * <b> Microcontroller XMC4700 on Relaxkit V1</b>
 * <ul>
 * <li>2048kB Flash;
 * <li>352kB RAM;
 * <li>PQFP144;
 * <li>1 USB Interface;
 * <li>1 Debug Interface Segger;
 * <li>1 RJ45 Interface;
 * <li>1 SD-Card Slot;
 * <li>3 LED1 and LED2;
 * <li>3 Tactile Switch BUTTON1 and BUTTON2;
 * </ul>
 * <b> Respiratory</b>
 * <ul>
 * <li>LCD-Dot-Matrix 2x40 Characters;
 * <li>8 LEDs;
 * <li>4 Keys;
 * <li>2 Potentiometers;
 * <li>1 LM76 I2C-Temperature Sensor;
 * <li>1 LM35 Analog Temperature Measurement;
 * <li>1 Buzzer;
 * <li>1 RS232 Interface;
 * <li>Expansion Modul for utilizing external boards;
 * </ul>
 *  @}
 */

/*! \defgroup License License

 * <b>(C) Copyright</b>
 * The Property Rights are taken from GNU GPL
 *
 * The source code could be used and/or modified and labelled by own author.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: The Author
 * has no obligation to support this Software. He is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement of
 * any proprietary rights of a third party.
 *
 * The Author will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 *
 */



#endif /* _DOXY_H_ */

