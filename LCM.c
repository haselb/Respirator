/*
 * LCM.c
 *
 *  Created on: 26.12.2017
 *      Author: haselb
 *      This Code drives a NewHaven DOT-Matrix LCD in 4-bit mode
 *      Control Lines used: RW RS EN (DIGITAL_O_LCD_xx)
 *      Data Lines used: D4 D5 D6 D7 (BUS_O_LCD_x)
 *
 *        Column
 *        	0  1  2  3  ............................19
 *        ---------------------------------------------
 * Line 0 | :  :  :  :  :                           : |
 * Line 1 | :  :  :  :  :                           : |
 * Line 2 | :  :  :  :  :                           : |
 * Line 3 | :  :  :  :  :                           : |
 *        ---------------------------------------------
 */

#include <DAVE.h>		//Declarations from DAVE4 Code Generation (includes SFR declaration)
#include "LCM.h"		// LCD-Module Prototypes
//#include "HAL_ADC.h"
#include "Has_Misc.h"		// for IRQ handling
#include <stdio.h>		// for sprintf
#include "HAL\HAL_i2c.h"
#include "init.h"


char buffer[LCD_MAX_WIDTH+1]; // last byte houses command EOL '\0'
volatile uint32_t display_queue=0;

/*
 * @brief Function to write a 4-bit Nibble.
 *
 * @param[in]  none
 *
 * @return  none
 */
void LCD_write_nibble(void) {

 //toggle Enable pin: High to Low transition
 LCD_EN_Set;
 delay100us(10);  //1ms
 LCD_EN_Clr;
}


/*
 * @brief Function to write a command to LCM.
 *
 * @param[in]  char
 *
 * @return  none
 */
void command(uint8_t i)
{
	uint8_t temp=0;

	temp=i>>4; //upper Nibble
	BUS_IO_Write(&BUS_O_LCD_D,temp);
	LCD_RS_Clr;
	LCD_RW_Clr;
	LCD_write_nibble();
	temp = i & 0x0F; //lower nibble
	BUS_IO_Write(&BUS_O_LCD_D,temp);
	LCD_write_nibble();
}

/*
 * @brief Function to write data to LCM.
 *
 * @param[in]  one character
 *
 * @return  none
 */
void write(uint8_t i)
{
	uint8_t temp=0;

	temp=i>>4; //upper Nibble shift to lower position
	BUS_IO_Write(&BUS_O_LCD_D,temp); // write lower nibble to Bus-Ports
	LCD_RS_Set;
	LCD_RW_Clr;
	LCD_write_nibble();
	temp = i & 0x0F; //mask out lower nibble
	BUS_IO_Write(&BUS_O_LCD_D,temp); // write lower nibble to Bus-Ports
	LCD_write_nibble();
}


/*
 * @brief Function to initialize LCM.
 *
 * @param[in]  none
 *
 * @return  none
 */
void LCD_init(void)
{
	// serve HW-Reset
	DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_RESET);
 	// wait for passing LCD-Power on Reset POR
	delay100us(200);   //wait after Power on device

	// init process in 4-bit mode as described in documentation
	BUS_IO_Write(&BUS_O_LCD_D,0x03); // write lower nibble to Bus-Ports
	delay100us(500);				 // wait at least 50ms
	LCD_write_nibble();				 // toggle Enable Port, high to low transition
	delay100us(500);
	LCD_write_nibble();
	delay100us(50);
	LCD_write_nibble();
	delay100us(50);
	BUS_IO_Write(&BUS_O_LCD_D,0x02); // write lower nibble to Bus-Ports
	LCD_write_nibble();
	delay100us(50);

	command(0x2A); //function set (extended command set)
	command(0x71); //function selection A
	write(0x00); // disable internal VDD regulator (2.8V I/O). data(0x5C) = enable regulator (5V I/O)
	command(0x28); //function set (fundamental command set)
	command(0x08); //display off, cursor off, blink off
	command(0x2A); //function set (extended command set)
	command(0x79); //OLED command set enabled
	command(0xD5); //set display clock divide ratio/oscillator frequency
	command(0x70); //set display clock divide ratio/oscillator frequency
	command(0x78); //OLED command set disabled
	command(0x09); //extended function set (4-lines)
	command(0x06); //COM SEG direction
	command(0x72); //function selection B
	write(0x00); //ROM CGRAM selection
	command(0x2A); //function set (extended command set)
	command(0x79); //OLED command set enabled
	command(0xDA); //set SEG pins hardware configuration
	command(0x10); //set SEG pins hardware configuration
	command(0xDC); //function selection C
	command(0x00); //function selection C
	command(0x81); //set contrast control
	command(0x7F); //set contrast control
	command(0xD9); //set phase length
	command(0xF1); //set phase length
	command(0xDB); //set VCOMH deselect level
	command(0x40); //set VCOMH deselect level
	command(0x78); //OLED command set disabled
	command(0x28); //function set (fundamental command set)
	command(0x01); //clear display
	command(0x80); //set DDRAM address to 0x00
	command(0x0C); //display ON

//	// now LCD ready for access
//	command(0x2A);		//function set (extension register) RE=1
//	delay100us(50);
//	command(0x06);		// common bi-direction function (BDC=1, BDS=0)
//	delay100us(50);
//	command(0x28);		//function set (fundamental command set) RE=0
//	delay100us(50);
//	//	command(0x79);
//	command(0x10);		//set SEG pins hardware configuration
//	delay100us(50);
////	command(0x07);      //common Segment direction left to right
////	delay100us(50);
////	command(0x09); //extended function set (4-lines)
////	delay100us(50);
////	command(0x78);
//	command(CLEAR_DISPLAY);
//	delay100us(50);
//	command(DISPLAY_ON);		//display ON
	delay100us(50);

}

// contrast proportional to value
// ADC darkvalue: 255d, ADC brightvalue: 70d
void set_contrast(uint8_t value)
{
	value /=2;	// 8bit ADC aligned to 7 bit LCM contrast range
	//if(value < 37) value -= 37U;
	if(value > 127U) value = 127U; // sanitize input
	command(0x2A);		//function set (extension register) RE=1
	delay100us(50);
	command(0x79);		//OLED command set enabled
	delay100us(50);
	command(0x81);		//set contrast control
	delay100us(50);
	command(127U-value);
	delay100us(50);
	command(0x78);	//OLED command set disabled
	delay100us(50);
	command(0x28); //function set (fundamental command set)
}

/*
* @brief Function to write string to LCM.
*
* @param[in]  1. Range of LCDLine: 0,1,2,3
*             2. Range of LCDColumn: 0,1,2...19
*             3. text string in ASCII notation
* @return  none
*/
void LCD_string(uint8_t LCDLine, uint8_t LCDColumn, char *LCDText)
{
	uint8_t offset=0x80;
 //calculate offset from RETURN_HOME position 0x80
	if((LCDLine >= 0) || (LCDLine < LCD_MAX_LINES) ||
			(LCDColumn >= 0) || (LCDColumn < LCD_MAX_WIDTH))
	{
		offset=offset+(LCDLine*0x20)+LCDColumn;
	}
	else
	{
		offset=0x80; //keep RETURN_HOME position
	}

	command(offset); // step to position
	// write text byte by byte to LCD till EOL character "\0"
	while (*LCDText)
		write(*LCDText++);
}


/*
* @brief Function to clear entire LCM.
*
* @param[in]  none
*
* @return  none
*/
void LCD_clearlines(void)
{
	// Write command CLS(0x01) to LCD-Display
	//------------------------------------------------
	// FUNCTION SET: Clear display
	command(CLEAR_DISPLAY);
//	delay100us(10); //wait
	// Write command home
	command(RETURN_HOME); //set curser to position 0,
//	delay100us(10);//wait

}


/*
* @brief Function to update LCM in mainloop.
*
* @param[in]  none
*
* @return  none
*/
void update_LCD(void)
{
//	uint16_t resets=0;
//	uint16_t writes=0;
//	uint16_t op_days=0;



//	f.toggle_W = f.toggle_W ^ 0x01;

	// serve first LCD Line: Trend, Temp, Char_temp,  Hum, Air_pres, Trend

//	sprintf(buffer,"%c%+5.1f%c %4.1f%%  %4.0f%c",
//			ROOM_M.T_Out_trend_char,
//			ROOM_M.T_Out_ave,
//			C_DEG,
//			ROOM_M.H_Out_ave,
//			S_ROOM_BA.BARO.ave_value,
//			S_ROOM_BA.trend_char);
	LCD_string(0,0,buffer);


	//serve second LCD Line:

//	sprintf(buffer,"%c%4.1f%c %2.0f%% %4.0f %4.0f",
//			S_ROOM_TH.trend_char,
//			S_ROOM_TH.temp.ave_value,
//			C_DEG,
//			S_ROOM_TH.humi.ave_value,
//			S_ROOM_AQ.eCO2.ave_value,
//			S_ROOM_AQ.TVOC.ave_value);
	LCD_string(1,0,buffer);

//serve third LCD Line:

	RTC_GetTime(&timeval);

//	if(f.toggle_W)
//	{
//		sprintf(buffer,"%2s %4d.%02d.%02d %02d %02d ",
//				WeekDay[timeval.daysofweek],
//				timeval.year,
//				timeval.month,
//				timeval.days,
//				timeval.hours,
//				timeval.minutes);
//	}
//	else
//	{
		sprintf(buffer,"%2s %4d.%02d.%02d %02d:%02d ",
				WeekDay[timeval.daysofweek],
				timeval.year,
				timeval.month,
				timeval.days,
				timeval.hours,
				timeval.minutes);
//	}
	LCD_string(2,0,buffer);


//serve fourth LCD Line: serve status and messages by queuing up


//			sprintf(buffer,"%03d, %03d, 0x%04X ", I2C_Comm_Counter,Environmental_Light,I2C_SLAVE_Status);
//			sprintf(buffer,"%+05.1f%c %+5.1f%c %+05.2f",ROOM_M.T_Boiler_ave,C_DEG,
//					ROOM_M.T_Setpoint,C_DEG,
//					ROOM_M.K_val);

//			LCD_string(3,0,buffer);

}



