/*
 * TFTdriver.cpp
 *
 * Created: 26-03-2020 09:40:24
 *  Author: math0
 */  
#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include "Text.h"
#include "../UART/uart.h"
#include <string.h>
#include <stdlib.h>

// Data port definitions:
#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

// Control port definitions:
#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7  //"DC" signal is at the shield called RS
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0



void TFTDriver::WriteCommand(unsigned int command)
{
	//Set command mode
	DC_PORT &= ~(1<<DC_BIT);
	//Setup command data
	DATA_PORT_LOW = command;
	//Set write to 0 (active)
	WR_PORT &= ~(1<<WR_BIT);
	//Wait for cycle 
	_NOP();
	//Set to 1 - triggers on rising edge
	WR_PORT |= (1<<WR_BIT);
	//Wait for cycle
	_NOP();
}

void TFTDriver::WriteData(unsigned int data)
{
	DC_PORT |= (1<<DC_BIT); //Ensure DC high
	//Setup data
	DATA_PORT_HIGH = ((data & 0xFF00)>>8);
	DATA_PORT_LOW = (data & 0xFF);
	//Enable write port
	WR_PORT &= ~(1<<WR_BIT);
	//Cycle
	_NOP();
	//Disable write port
	WR_PORT |= (1<<WR_BIT);
	//Cycle
	_NOP();
}


TFTDriver::TFTDriver(int width, int height, FontGenerator * fontGenerator)
{
	_width = width;
	_height = height;
	_fontGenerator = fontGenerator;
}

TFTDriver::TFTDriver()
{
	_width = 0;
	_height = 0;
}

TFTDriver::~TFTDriver()
{
}

void TFTDriver::Init()
{
	//Set DC pin as output
	DDRD |= (1<<DC_BIT);
	//Set port A and C as output for data pins
	DDRA = 0xff;
	DDRC = 0xff;
	//Set write pin as output
	DDRG |= (1<<WR_BIT);
	//Set CS bit
	DDRG |= (1<<CS_BIT);
	//Set reset pin as output
	DDRG |= (1<<RST_BIT);
		
	DC_PORT |= (1<<DC_BIT);
	WR_PORT |= (1<<WR_BIT);
	CS_PORT &= ~(1<<CS_BIT);
	RST_PORT |= (1<<RST_BIT);
	//Set CS to 0 (enable)

	//Reset and init
	Reset();
	SleepOut();
	DisplayOn();
	_delay_ms(5);
	MemoryAccessControl(0b00001000);
	InterfacePixelFormat(0b00000101);	
	
}

void TFTDriver::DisplayOff()
{
	WriteCommand(0b00101000);
}

void TFTDriver::DisplayOn()
{
	WriteCommand(0b00101001);
}

void TFTDriver::SleepOut()
{
	WriteCommand(0b00010001);
	_delay_ms(10);
}

void TFTDriver::Reset()
{
	RST_PORT &= ~(1<<RST_PORT);
	_delay_ms(500);
	RST_PORT |= (1<<RST_PORT);
	_delay_ms(130);
}

void TFTDriver::MemoryAccessControl(unsigned char parameter)
{
	WriteCommand(0b00110110);
	WriteData(parameter);
}

void TFTDriver::InterfacePixelFormat(unsigned char parameter)
{
	WriteCommand(0b00111010);
	WriteData(parameter);
}

void TFTDriver::MemoryWrite()
{
	WriteCommand(0b00101100);
}

void TFTDriver::WritePixel(int encodedColor)
{
	WriteData(encodedColor);
}

void TFTDriver::SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0b00101010);
	WriteData(Start>>8);
	WriteData(Start);
	WriteData(End>>8);
	WriteData(End);
}

void TFTDriver::SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0b00101011);
	WriteData(Start>>8);
	WriteData(Start);
	WriteData(End>>8);
	WriteData(End);
}

int TFTDriver::GetHeight()
{
	return _height;
}

int TFTDriver::GetWidth()
{
	return _width;
}


void TFTDriver::FillRectangle(int StartX, int StartY, int Width, int Height, unsigned int color)
{
	int endX = StartX + Width;
	int endY = StartY + Height;
	if(StartX > _width || endX < 0) //Out of screen
	{
		return;
	}
	else if(endX > _width && StartX < _width) //On right edge of screen
	{
		endX = _width;
		Width = endX - StartX;
		if(Width < 0)
			Width = 0;
	}
	else if(endX > 0 && StartX < 0) //On left edge of screen
	{
		StartX = 0;
		Width = endX - StartX;
		if(Width < 0)
			Width = 0;
	}
	if(StartY > _height || endY < 0) //Out of screen
	{
		return;
	}
	else if(endY > _height && StartY < _height) //On bottom of screen
	{
		endY = _height;
		Height = endY - StartY;
		if(Height < 0)
			Height = 0;
	}
	else if(endY > 0 && StartY < 0) //On top of screen
	{
		StartY = 0;
		Height = endY - StartY;
		if(Height < 0)
			Height = 0;
	}
	
	SetPageAddress(StartX, endX - 1);
	SetColumnAddress(StartY, endY - 1);
	MemoryWrite();
	long int numPixels = (long int)Width * Height;

	for(long int i = 0; i < numPixels; ++i)
	{
		WritePixel(color);
	}
	
}


void TFTDriver::DrawGame(PipePair * pipePairs, int numPairs, FlappyObject *flappy, int speed)
{
	for(int i = 0; i < numPairs; i++)
	{
		UIObject * lower = pipePairs[i].GetLower();
		UIObject * upper = pipePairs[i].GetUpper();
		
		int startX = upper->GetStartX();
		int width = speed;
		int startY = upper->GetStartY();
		int height = upper->GetHeight();
		unsigned int color = upper->GetColor();
		FillRectangle(startX, startY, width, height, color);
		
		startX = lower->GetStartX();
		width = speed;
		startY = lower->GetStartY();
		height = lower->GetHeight();
		color = lower->GetColor();
		FillRectangle(startX, startY, width, height, color);
	}
	//Draw flappy
	DrawFlappy(flappy);
}

void TFTDriver::DrawTextButton(UIObject * button, bool clicked, const unsigned char * data, long int dataLength, int width, int height, unsigned int backgroundColor, unsigned int textColor, int padding)
{
	FillRectangle(button->GetStartX() - padding, button->GetStartY() - padding, button->GetWidth() + 2*padding, button->GetHeight() + 2*padding, backgroundColor);
	int buttonCenterX = button->GetStartX() + button->GetWidth()/2;
	int buttonCenterY = button->GetStartY() + button->GetHeight()/2;
	DrawText(data, dataLength, width, height, buttonCenterX, buttonCenterY, backgroundColor, textColor);
}

void TFTDriver::EraseObjects(PipePair * pipePairs, int numPairs, FlappyObject * flappy, unsigned int color, int speed)
{
	for(int i = 0; i < numPairs; i++)
	{
		UIObject * lower = pipePairs[i].GetLower();
		UIObject * upper = pipePairs[i].GetUpper();
		
		int startX = upper->GetStartX() + upper->GetWidth() - speed;
		int width = speed;
		int startY = upper->GetStartY();
		int height = upper->GetHeight();
		FillRectangle(startX, startY, width, height, color);
		
		startX = lower->GetStartX() + lower->GetWidth() - speed;
		width = speed;
		startY = lower->GetStartY();
		height = lower->GetHeight();
		FillRectangle(startX, startY, width, height, color);
	}
	int x = flappy->GetStartX();
	int y = flappy->GetStartY();
	int w = flappy->getFlappyLength() + 5;
	int h = flappy->getFlappyHeight();
	FillRectangle(x, y, w, h, color);
}

void TFTDriver::DrawFlappy(FlappyObject * flappy)
{
	int startX = flappy->GetStartX();
	int startY = flappy->GetStartY();
	int height = flappy->getFlappyHeight();
	int width = flappy->getFlappyLength();
	//Draw body
	Color Yellow(255,255,0);
	FillRectangle(startX, startY, width, height, Yellow.getEncodedColor());
	//Draw beak
	Color Red(255, 0, 0);
	FillRectangle(flappy->GetStartX() + flappy->getFlappyLength() - 10,
		flappy->GetStartY() + flappy->getFlappyHeight()/2 + 2, 
		15, 5, 
		Red.getEncodedColor());
	
	//Draw eye
	Color Black(0,0,0);
	FillRectangle(flappy->GetStartX() + flappy->getFlappyLength() - 6,
	flappy->GetStartY() + flappy->getFlappyHeight()/2 - 7,
	3, 7, Black.getEncodedColor());
}

void TFTDriver::DrawBackground(Color *backgroundColor, Color *earthColor, int earthHeight)
{
	int encodedBackgroundColor = backgroundColor->getEncodedColor();
	int encodedearthColor = earthColor->getEncodedColor();
	SetPageAddress(0, _width - 1);
	SetColumnAddress(0, _height - earthHeight - 1);
	MemoryWrite();
	long int numPixels = (long int)_width * _height-earthHeight;
	for(long int i = 0; i < numPixels; ++i)
	{
		WritePixel(encodedBackgroundColor);
	}
	//Dummy command
	//DisplayInversionOff();
		
	SetPageAddress(0, _width - 1);
	SetColumnAddress(_height-earthHeight, _height - 1);
	MemoryWrite();
	numPixels = (long int)_width * earthHeight;
	for(long int i = 0; i < numPixels; ++i)
	{
		WritePixel(encodedearthColor);
	}
}

void TFTDriver::DrawText(const unsigned char * data, long int dataLength, int width, int height, int xCenter, int yCenter, unsigned int backgroundColor, unsigned int textColor)
{
	unsigned int startX = xCenter - width/2;
	unsigned int startY = yCenter - height/2;
	//MemoryAccessControl(0b00011100);
	SetPageAddress(startX, startX + width - 1);
	SetColumnAddress(startY, startY + height - 1);
	MemoryWrite();
	for(long int i = 0; i < dataLength; i++)
	{
		char pixels = data[i];
		for(int b = 0; b < 8; b++)
		{
			char temp = pixels<<b;
			temp &= 0b10000000;
			if(temp != 0)
			{
				WritePixel(textColor);
			}
			else
			{
				WritePixel(backgroundColor);
			}
		}
	}
}

void TFTDriver::WriteText(char* text, int startX, int startY, unsigned int textColor, unsigned int backgroundColor)
{
	int length = strlen(text);
	
	SetColumnAddress(startY,startY+15);
	SetPageAddress(startX,(length*16)+startX);
	MemoryWrite();
	
	for(int i = 0; i < length; ++i )
	{
		unsigned char* c = _fontGenerator->GetCharacter(*(text+i));		
		
		for(int ii = 0; ii< 32; ++ii)
		{
			char pixel = *(c+ii);
			for(int iii = 0; iii < 8 ; iii++)
			{
				char onoff = pixel<<iii;
				onoff &= 0b10000000;
				if(onoff != 0)
				{
					WritePixel(textColor);
				} 
				else if (onoff == 0) 
				{
					WritePixel(backgroundColor);
				}
			}
		}
	}
}

void TFTDriver::UpdateScore(int score, Color * textColor, Color * backgroundColor)
{
	char scoreString [(sizeof(int)*8+1)];
	WriteText(itoa(score, scoreString, 10), _scoreWidth + 10 + 10, _height - _scoreHeight - 2, textColor->getEncodedColor(), backgroundColor->getEncodedColor());
}

void TFTDriver::DrawScore(int score, Color * textColor, Color * backgroundColor)
{
	DrawText(_scoreText, sizeof(_scoreText), _scoreWidth, _scoreHeight, (_scoreWidth/2) + 10, _height - (_scoreHeight/2) - 2, backgroundColor->getEncodedColor(), textColor->getEncodedColor());
	char scoreString [(sizeof(int)*8+1)];
	WriteText(itoa(score, scoreString, 10), _scoreWidth + 10 + 10, _height - _scoreHeight - 2, textColor->getEncodedColor(), backgroundColor->getEncodedColor());
}

void TFTDriver::DisplayInversionOn()
{
	WriteCommand(0b00100001);
}

void TFTDriver::DisplayInversionOff()
{
	WriteCommand(0b00100000);
}