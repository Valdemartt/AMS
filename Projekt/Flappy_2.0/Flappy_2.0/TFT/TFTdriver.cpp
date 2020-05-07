/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  Henning Hargaard, February 14, 2019
************************************************************/  
#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"

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

// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// ILI 9341 data sheet, page 238
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

// ILI 9341 data sheet, page 238
void TFTDriver::WriteData(unsigned int data)
{
	DC_PORT |= (1<<DC_BIT);
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

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

TFTDriver::TFTDriver(int width, int height)
{
	_width = width;
	_height = height;
}

TFTDriver::TFTDriver()
{
	_width = 0;
	_height = 0;
}

TFTDriver::~TFTDriver()
{
}

// Initializes (resets) the display
void TFTDriver::DisplayInit()
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
	//CS_PORT &= ~(1<<CS_BIT);

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

// Red 0-31, Green 0-63, Blue 0-31
void TFTDriver::WritePixel(int encodedColor)
{
	WriteData(encodedColor);
}

// Set Column Address (0-239), Start > End
void TFTDriver::SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0b00101010);
	WriteData(Start>>8);
	WriteData(Start);
	WriteData(End>>8);
	WriteData(End);
}

// Set Page Address (0-319), Start > End
void TFTDriver::SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0b00101011);
	WriteData(Start>>8);
	WriteData(Start);
	WriteData(End>>8);
	WriteData(End);
}

// Fills rectangle with specified color
// (StartX,StartY) = Upper left corner. X horizontal (0-319) , Y vertical (0-239).
// Height (1-240) is vertical. Width (1-320) is horizontal.
// R-G-B = 5-6-5 bits.
void TFTDriver::FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue)
{
	SetPageAddress(StartX, (StartX + Width) - 1);
	SetColumnAddress(StartY, (StartY + Height) - 1);
	MemoryWrite();
	for(long int i = 0; i < (Width * Height); ++i)
	{
		WritePixel(0);
	}
	//Dummy command
	DisplayInversionOff();
}

void TFTDriver::DrawFrame(int* data)
{
	int dataSize = sizeof(data);
	if(dataSize > _height * _width)
	{
		dataSize = _height * _width;
	}
	SetPageAddress(0, _width - 1);
	SetColumnAddress(0, _height - 1);
	MemoryWrite();
	for(long int i = 0; i < dataSize; ++i)
	{
		WriteData(data[i]);
	}
	//Dummy command
	DisplayInversionOff();
}

void TFTDriver::DisplayInversionOn()
{
	WriteCommand(0b00100001);
}

void TFTDriver::DisplayInversionOff()
{
	WriteCommand(0b00100000);
}