/*
 * TouchDriver.cpp
 *
 * Created: 26-03-2020 08:39:14
 *  Author: math0
 */ 

#include <avr/interrupt.h>
#include "TouchDriver.h"
#include <avr/cpufunc.h>
#include "../UART/uart.h"
#include <avr/io.h>


TouchDriver::TouchDriver(int xLeftOffset, int xRightOffset, int yTopOffset, int yBottomOffset, int conversionResolution, int xPixels, int yPixels, int precision)
{
	_xRightOffset = xRightOffset;
	_xLeftOffset = xLeftOffset;
	_yTopOffset = yTopOffset;
	_yBottomOffset = yBottomOffset;
	_timer0_duration = 0;
	_xPixels = xPixels;
	_yPixels = yPixels;
	_conversionResolution = conversionResolution;
	_xResPerPixel = (_conversionResolution - _xLeftOffset - _xRightOffset) / _xPixels;
	_yResPerPixel = (_conversionResolution - _yTopOffset - _yBottomOffset) / _yPixels;
	_precision = precision;
}
TouchDriver::TouchDriver()
{
}
void TouchDriver::Init()
{
	//P Directions
	sbi(CLK_DDR, CLK_PIN);
	sbi(DIN_DDR, DIN_PIN);
	sbi(CS_DDR, CS_PIN);
	cbi(DOUT_DDR, DOUT_PIN);
	cbi(IRQ_DDR, IRQ_PIN);
	
	//INT setup for INT4
	sbi(EIMSK, 4);
	sbi(EICRB, 2);
	//sei();
	
	position = Position(0,0);
	
	sbi(CS_PORT,CS_PIN);
	_NOP();
	_NOP();
	cbi(CS_PORT,CS_PIN);
	_NOP();
	_NOP();
	WriteData(0x90);
	ClockPulse();
	unsigned long temp_x = ReadData();
	sbi(CS_PORT,CS_PIN);
}

bool TouchDriver::ReadPosition()
{
	unsigned int temp_x=0, temp_y=0;
	bool positionRead = false;
	int xRead = 0, yRead = 0;
	cbi(CS_PORT,CS_PIN);
	for(int i = 0; i < _precision; i++)
	{
		if(ScreenTouched())
		{
			WriteData(0x90);
			temp_x += ReadData();
			xRead++;
			if(ScreenTouched())
			{
				WriteData(0xD0);
				temp_y += ReadData();
				yRead++;
				positionRead = true;
			}
		}
		_NOP();
		ClockPulse();
	}
	if(positionRead)
	{
		position.setX(_xPixels - (((temp_x/xRead) - _xLeftOffset) / _xResPerPixel));
		position.setY(_yPixels - (((temp_y/yRead) - _yTopOffset) / _yResPerPixel));
	}
	sbi(CS_PORT,CS_PIN);
	return positionRead;
}

int TouchDriver::getX()
{
	return position.getX();
}
int TouchDriver::getY()
{
	return position.getY();
}


bool TouchDriver::ScreenTouched()
{
	bool dataAvailable;
	dataAvailable = !rbi(IRQ_PORT,IRQ_PIN);
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
}

int16_t TouchDriver::ReadData()
{
	int16_t data = 0;
	_NOP();
	_NOP();
	_NOP();
	ClockPulse(); //Busy clock pulse
	for (int i=0; i<12;i++)
	{
		data = data<<(1);
		if(rbi(DOUT_PORT,DOUT_PIN))
		{
			data++;
		}
		ClockPulse();
	}
	for (int i=0; i<3;i++)
	{
		ClockPulse();
	}
	return data;
}

void TouchDriver::ClockPulse()
{
	//needs to be at least 500 to achieve 1.5 micro sec pr. 3 clockpulses
	_NOP();
	_NOP();
	sbi(CLK_PORT,CLK_PIN);
	_NOP();
	_NOP();
	cbi(CLK_PORT,CLK_PIN);
}

void TouchDriver::SetTimer1_EnableInterrupt()
{
	TIMSK1 = 2; //Enable interrupt on compare A for timer 1
	TCCR1A &= 0b11111100; //Set CTC mode
	TCCR1B &= 0b11101111; //Set CTC mode
	TCCR1B |= 0b00001000; //Set CTC mode
	OCR1A = 10000; //Compare on when timer reaches 10000
	TCCR1B |= 0b00000011; //Set 64 clock prescaler and start timer
}
void TouchDriver::ClearClock()
{
	cbi(CLK_PORT,CLK_PIN);
}


