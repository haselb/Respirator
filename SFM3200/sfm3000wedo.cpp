/*
  SFM3000wedo.cpp - Library for reading values from flowmeter Sensirion SFM3000wedo
  https://www.sensirion.com/en/flow-sensors/mass-flow-meters-for-high-precise-measurement-of-gases/low-pressure-drop-mass-flow-meter/
  Created by WeDo, Zuerich 20170616
  
  Released into the public domain.
*/

#include "SFM3000wedo.h"
//#include <Wire.h>

extern "C" {
	#include <Dave.h>
	#include "Has_misc.h"
	#include "HAL\HAL_i2c.h"
}



 
SFM3000wedo::SFM3000wedo(uint8_t i2cAddress)
//SFM3000wedo::SFM3000wedo(int i2cAddress)
{
	//: mI2cAddress(i2cAddress)
	mI2cAddress = i2cAddress;
}



void SFM3000wedo::init()
{
//	int a = 0;
//	int b = 0;
//	int c = 0;
	
	uint8_t reg;
	uint8_t *val;
//	Wire.begin();
//	Serial.begin(9600);
//	delay(1000);
	delay100us(1000); // 100ms after POR Sensor is ready
//	Wire.beginTransmission(byte(mI2cAddress)); // transmit to device with I2C mI2cAddress
//	Wire.beginTransmission(byte(mI2cAddress)); // transmit to device with I2C mI2cAddress
//	Wire.write(byte(0x10));      //
//	Wire.write(byte(0x00));      //
//	Wire.endTransmission();
	reg=0xA;

    Soft_WDG_1(ON);	// if no acknowledge occurs, program would wait infintiy in while loop
    I2C_MASTER_Transmit(&I2C_MASTER_0,true,mI2cAddress,&reg,1,false);
    while((tx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
    tx_completion_0 = 0;
    Soft_WDG_1(OFF);  // if after xxms of no response, IRQ set flag_eject_at_I2C_NACK=1 to leave while loop
	if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
	{
		flag_I2C_NACK=0;
		flag_eject_at_I2C_NACK=0;
//		return false;
	}

	val=0x0;

    I2C_MASTER_Transmit(&I2C_MASTER_0,false,mI2cAddress,val,1,true);
	while((tx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
	tx_completion_0 = 0;
	Soft_WDG_1(OFF);  // if after xxms of no response, IRQ set flag_eject_at_I2C_NACK=1 to leave while loop
	if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
	{
		flag_I2C_NACK=0;
		flag_eject_at_I2C_NACK=0;
		//return false;
	}
	else
	{
		delay100us(5);
		//return true;
	}


	
//	Wire.requestFrom(mI2cAddress, 3); //
//	a = Wire.read(); // first received byte stored here
//	b = Wire.read(); // second received byte stored here
//	c = Wire.read(); // third received byte stored here
//	Wire.endTransmission();
//	Serial.print(a);
//	Serial.print(b);
//	Serial.println(c);
    Soft_WDG_1(ON);
    I2C_MASTER_Receive(&I2C_MASTER_0,true,mI2cAddress,val,3,true,true);
    while((rx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
    rx_completion_0 = 0;
    Soft_WDG_1(OFF);

    if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
    {
    	 flag_I2C_NACK=0;
    	 flag_eject_at_I2C_NACK=0;
    	// return -1;
    }
    //delay100us(1);
    //return len;
	
	delay100us(5);
//	Wire.requestFrom(mI2cAddress, 3); //
//	a = Wire.read(); // first received byte stored here
//	b = Wire.read(); // second received byte stored here
//	c = Wire.read(); // third received byte stored here
//	Wire.endTransmission();
//	Serial.print(a);
//	Serial.print(b);
//	Serial.println(c);
	

    Soft_WDG_1(ON);
    I2C_MASTER_Receive(&I2C_MASTER_0,true,mI2cAddress,val,3,true,true);
    while((rx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
    rx_completion_0 = 0;
    Soft_WDG_1(OFF);

    if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
    {
    	 flag_I2C_NACK=0;
    	 flag_eject_at_I2C_NACK=0;
    	// return -1;
    }
	delay100us(5);
	
}
 
float SFM3000wedo::getvalue()
{
	uint8_t reg;
	uint8_t *val;
//    Wire.requestFrom(mI2cAddress, 3); // read 3 bytes from device with address 0x40
	uint16_t a = 0;// = Wire.read(); // first received byte stored here. The variable "uint16_t" can hold 2 bytes, this will be relevant later
	uint8_t b = 0; //=Wire.read(); // second received byte stored here
	uint8_t crc = 0; //=Wire.read(); // crc value stored here

	reg=0xA;

    Soft_WDG_1(ON);	// if no acknowledge occurs, program would wait infintiy in while loop
    I2C_MASTER_Transmit(&I2C_MASTER_0,true,mI2cAddress,&reg,1,false);
    while((tx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
    tx_completion_0 = 0;
    Soft_WDG_1(OFF);  // if after xxms of no response, IRQ set flag_eject_at_I2C_NACK=1 to leave while loop
	if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
	{
		flag_I2C_NACK=0;
		flag_eject_at_I2C_NACK=0;
//		return false;
	}

	val=0x0;

    I2C_MASTER_Transmit(&I2C_MASTER_0,false,mI2cAddress,val,1,true);
	while((tx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
	tx_completion_0 = 0;
	Soft_WDG_1(OFF);  // if after xxms of no response, IRQ set flag_eject_at_I2C_NACK=1 to leave while loop
	if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
	{
		flag_I2C_NACK=0;
		flag_eject_at_I2C_NACK=0;
		//return false;
	}
	else
	{
		delay100us(5);
		//return true;
	}


    Soft_WDG_1(ON);
    I2C_MASTER_Receive(&I2C_MASTER_0,true,mI2cAddress,val,3,true,true);
    while((rx_completion_0 == 0) && (flag_I2C_NACK == 0) && (flag_eject_at_I2C_NACK == 0));
    rx_completion_0 = 0;
    Soft_WDG_1(OFF);

    if(flag_I2C_NACK || flag_eject_at_I2C_NACK)
    {
    	 flag_I2C_NACK=0;
    	 flag_eject_at_I2C_NACK=0;
    	// return -1;
    }
	delay100us(5);

	a=val[0];
	b=val[1];
	crc=val[2];

	uint8_t mycrc = 0xFF; // initialize crc variable
	mycrc = crc8(a, mycrc); // let first byte through CRC calculation
	mycrc = crc8(b, mycrc); // and the second byte too
	if (mycrc != crc) { // check if the calculated and the received CRC byte matches
		//Serial.println("Error: wrong CRC");
	}
	a = (a << 8) | b; // combine the two received bytes to a 16bit integer value
	// a >>= 2; // remove the two least significant bits
	//float Flow = (float)a;
	int Flow=a;
	return Flow;
}

uint8_t SFM3000wedo::crc8(const uint8_t data, uint8_t crc)
{
	   crc ^= data;
	   for ( uint8_t i = 8; i; --i ) {
		   crc = ( crc & 0x80 )
		   ? (crc << 1) ^ 0x31
		   : (crc << 1);
		}
	return crc;
}



// Linear interpolation
// float Fader::lerp (float m1, float M1, float m2, float M2, float v1)
// {
  // float d  = M1 - m1;
  // float c  = (M2 - m2) / d;
  // float o = ( -(M2 * m1) + (m2 * m1) + m2 * d) / d;
  // return v1 * c + o;
// }
