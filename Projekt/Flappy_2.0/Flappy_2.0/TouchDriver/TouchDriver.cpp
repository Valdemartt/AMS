/*
 * TouchDriver.cpp
 *
 * Created: 26-03-2020 08:39:14
 *  Author: math0
 */ 

#include <avr/interrupt.h>
#include "TouchDriver.h"
#include <avr/cpufunc.h>

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
	EICRB |= 2;
	sei();
	
	position = Position(0,0);
	
	sbi(CS_PORT,CS_PIN);
	sbi(CLK_PORT,CLK_PIN);
	//sbi(DIN_PORT,DIN_PIN);
	//sbi(IRQ_PORT,IRQ_PIN);
	
	cbi(CS_PORT,CS_PIN);
	_NOP();
	_NOP();
	WriteData(0x90);
	ClockPulse();
	unsigned long temp_x = ReadData();
	sbi(CS_PORT,CS_PIN);
}

void TouchDriver::Read()
{
	unsigned int temp_x=0, temp_y=0;
	//int datacounter = 0;
	
	cbi(CS_PORT,CS_PIN);
	
	//enables interrupt
	IRQ_DDR &= ~1<<(IRQ_PIN);
	
	if(!rbi(IRQ_PORT,IRQ_PIN))
	{
		WriteData(0x90);
		temp_x = ReadData();
		
		if(!rbi(IRQ_PORT,IRQ_PIN))
		{
			WriteData(0xD0);
			temp_y = ReadData();
			
			/*if((temp_x>ADC_RES_MIN) && (temp_x<ADC_RES_MAX) && (temp_y>ADC_RES_MIN) && (temp_y<ADC_RES_MAX))
			{
				
			}*/
			
			position.setX(temp_x);
			position.setY(temp_y);
		}
		
	}
	
	//disables interrupt
	IRQ_DDR |= 1<<(IRQ_PIN);
		
	sbi(CS_PORT,CS_PIN);
	_NOP();
	ClockPulse();

}

Position TouchDriver::getPosition()
{
	return position;
}

bool TouchDriver::ScreenTouched()
{
	bool dataAvailable;
	IRQ_DDR &= ~1<<(IRQ_PIN);
	dataAvailable = !rbi(IRQ_PORT,IRQ_PIN);
	IRQ_DDR |= 1<<(IRQ_PIN);
	return dataAvailable;
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
		_NOP();
		ClockPulse();
	}
	cbi(DIN_PORT,DIN_PIN);
	_NOP();
	_NOP();
	_NOP();
	ClockPulse();
	
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
	for (int i=0; i<3;i++)
	{
		ClockPulse();
	}

	return data;
}

void TouchDriver::ClockPulse()
{
	//needs to be atleast 500 to achieve 1.5 micro sec pr. 3 clockpulses
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	sbi(CLK_PORT,CLK_PIN);
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	_NOP();
	cbi(CLK_PORT,CLK_PIN);
}

void TouchDriver::ClearClock()
{
	cbi(CLK_PORT,CLK_PIN);
}


