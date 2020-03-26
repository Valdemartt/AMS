/*
 * TouchDriver.cpp
 *
 * Created: 26-03-2020 08:39:14
 *  Author: math0
 */ 

#include <avr/interrupt.h>
#include "TouchDriver.h"

#define CAL_X 0x00378F66UL
#define CAL_Y 0x03C34155UL
#define CAL_S 0x000EF13FUL

TouchDriver::TouchDriver()
{
	
}

void TouchDriver::InitTouch()
{
	//P Directions
	CLK_DDR |= 1<<(CLK_PIN);
	CS_DDR |= 1<<(CS_PIN);
	DIN_DDR |= 1<<(DIN_PIN);
	DOUT_DDR &= ~1<<(DOUT_PIN);
	IRQ_DDR |= 1<<(IRQ_PIN);
	
	//INT setup for INT4
	EIMSK |= 1<<(4);
	EICRB |= 3;
	
	sei();
	
	
	position = Position(0,0);
	
}

void TouchDriver::Read()
{
	unsigned long temp_x=0, temp_y=0;
	//int datacounter = 0;
	
	cbi(CS_PORT,CS_PIN);
	
	//disables interrupt
	IRQ_DDR &= ~1<<(IRQ_PIN);
	
	if(ScreenTouched())
	{
		WriteData(0x90);
		ClockPulse();
		temp_x = ReadData();
		
		if(ScreenTouched())
		{
			WriteData(0xD0);
			ClockPulse();
			temp_y = ReadData();
			
			/*if((temp_x>ADC_RES_MIN) && (temp_x<ADC_RES_MAX) && (temp_y>ADC_RES_MIN) && (temp_y<ADC_RES_MAX))
			{
				
			}*/
			
			
			
			position.setX(temp_x);
			position.setY(temp_y);
		}
		
	}
	
	sbi(CS_PORT,CS_PIN);
	
	//Enables interrupt
	IRQ_DDR |= 1<<(IRQ_PIN);
}

Position TouchDriver::getPosition()
{
	return position;
}

bool TouchDriver::ScreenTouched()
{
	return !rbi(IRQ_PORT,IRQ_PIN);
}

void TouchDriver::WriteData(unsigned char data)
{
	unsigned char temp = data;
	
	ClearClock();
	for(int i=0;i<8;i++)
	{
		if(temp & 0b10000000)
		{
			sbi(DIN_PORT,DIN_PIN);
		}
		else
		{
			cbi(DIN_PORT,DIN_PIN);	
		}
		temp = temp <<(1);
		ClockPulse();
	}
}

int16_t TouchDriver::ReadData()
{
	int16_t data = 0;
	
	for (int i=0; i<12;i++)
	{
		data = data<<(1);
		ClockPulse();
		if(rbi(DOUT_PORT,DOUT_PIN))
		{
			data++;
		}
	}
	
	return data;
}

void TouchDriver::ClockPulse()
{
	sbi(CLK_PORT,CLK_PIN);
	cbi(CLK_PORT,CLK_PIN);
}

void TouchDriver::ClearClock()
{
	cbi(CLK_PORT,CLK_PIN);
}


