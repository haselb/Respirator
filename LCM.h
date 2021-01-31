/*
 * LCD.h
 *
 *  Created on: 26.12.2017
 *      Author: haselb
 */

#ifndef LCM_H_
#define LCM_H_

#include <DAVE.h>


// Header for local LCD-Module


#define LCD_MAX_WIDTH 20	    // 20 colums-display
#define LCD_MAX_LINES 4			// 4 lines display

#define LCD_EN_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_EN)
#define LCD_EN_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_EN)

#define LCD_RS_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_RS)
#define LCD_RS_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_RS)

#define LCD_RW_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_RW)
#define LCD_RW_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_RW)

// data Ports are handled by BUS_IO
//#define LCD_D4_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_D4)
//#define LCD_D4_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_D4)
//
//#define LCD_D5_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_D5)
//#define LCD_D5_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_D5)
//
//#define LCD_D6_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_D6)
//#define LCD_D6_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_D6)
//
//#define LCD_D7_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_D7)
//#define LCD_D7_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_D7)

//#define LCD_Reset_Clr DIGITAL_IO_SetOutputLow(&DIGITAL_O_LCD_RESET)
//#define LCD_Reset_Set DIGITAL_IO_SetOutputHigh(&DIGITAL_O_LCD_RESET)

//enumerate bit condition of sent character
//bitposition in a Byte
//| upper nibble  | lower nibble  |
//| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |

//enum{
//   bit0      = 0x01U,
//   bit1      = 0x02U,
//   bit2      = 0x04U,
//   bit3      = 0x08U,
//   bit4      = 0x10U,
//   bit5      = 0x20U,
//   bit6      = 0x40U,
//   bit7      = 0x80U
//};

#define CLEAR_DISPLAY 	0x01
#define RETURN_HOME		0x02
#define DISPLAY_ON		0x0C

// equate character set in ROM Font table A to name
#define C_UP 	0xDE
#define C_UM	0x17
#define C_N		0xDF
#define C_LM	0x19
#define C_DN	0xE0
#define C_DEG	128U

extern char buffer[LCD_MAX_WIDTH+1];
extern volatile uint32_t display_queue;

//prototypes for local LCD display with nibble-drive mode (4bit)
extern void LCD_init(void);
extern void LCD_clearlines (void);
extern void LCD_string(uint8_t LCDLine, uint8_t LCDColumn, char *LCDText);
extern void LCD_write_nibble(void);
extern void write(uint8_t i);
extern void command(uint8_t i);
extern void update_LCD(void);


#endif /* LCM_H_ */
