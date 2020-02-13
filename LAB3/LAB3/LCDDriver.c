/*-------------------------------------------------------------------
  File name: "lcd162.c"

  Driver for "LCD Keypad Shield" alphanumeric display.
  Display controller = HD44780U (LCD-II).
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connection : PORTx (4 bit mode) :
  [LCD]        [Portx]
  RS   ------  PH 5
  RW   ------  GND
  E    ------  PH 6
  DB4  ------  PG 5
  DB5  ------  PE 3
  DB6  ------  PH 3
  DB7  ------  PH 4

---------------------------------------------------------------------*/
#include <avr/io.h>
#define F_CPU 16000000
#define Clock_Duration_ns 1/F_CPU * 1000000000
#include <util/delay.h>
// Enabling us to use macro _NOP() to insert the NOP instruction
#include <avr/cpufunc.h>
#include "LCDDriver.h"
#include <math.h>

// library function itoa() is needed
#include <stdlib.h>

//*********************** PRIVATE (static) operations *********************
static void waitBusy(long us)
{
  //long ns = us * 1000;
  //int numCycles = ceil(ns/Clock_Duration_ns);
  //int adjustedNumCycles = ceil((numCycles - 1) / 3);
  //for(int i = 0; i < adjustedNumCycles; ++i)
  //{
	  //_NOP();
  //}
  _delay_ms(2);
}  

static void pulse_E()
{
  PORTH = (PORTH | 0b01000000); 
  _NOP();
  _NOP();
  _NOP();
  _NOP();
  PORTH = (PORTH & 0b10111111);
  _NOP();
  _NOP();
}

// Sets the display data pins according to the 4 lower bits of data
static void set4DataPins(unsigned char data)
{
  PORTH = (PORTH & 0b11100111) | ((data<<1) & 0b00011000);
  PORTE = (PORTE & 0b11110111) | ((data<<2) & 0b00001000);
  PORTG = (PORTG & 0b11011111) | ((data<<5) & 0b00100000);
}

static void sendInstruction(unsigned char data)
{      
  waitBusy(50);
  // Set RS and E to 0
  PORTH = (PORTH & 0b10011111);

  set4DataPins(data>>4);
  pulse_E();
  set4DataPins(data);
  pulse_E();
}

static void sendData(unsigned char data)
{      
  waitBusy(50);
  //Set RS 
  PORTH = (PORTH | 0b00100000);
  //Set E to 0
  PORTH = (PORTH & 0b10111111);
  set4DataPins(data>>4);
  pulse_E();

  set4DataPins(data);
  pulse_E();
  _delay_us(50);
}


static void Timer_2_Init()
{
	TCCR2A = 0b10000011;
	TCCR2B = 0b00000111;
	OCR2A = 255/4;
	DDRB |= (1<<4);
}


static void ADC_Init()
{
	ADMUX = 0b01000000;
	ADCSRA = 0b11100111;
	ADCSRB = 0;
}
//*********************** PUBLIC functions *****************************

// Initializes the display, blanks it and sets "current display position"
// at the upper line, leftmost character (cursor invisible)
// Reference: Page 46 in the HD44780 data sheet
void LCDInit()
{
  // Initializing the used port
  DDRH |= 0b01111000;  // Outputs
  DDRE |= 0b00001000;
  DDRG |= 0b00100000;
  
  // Wait 50 ms (min. 15 ms demanded according to the data sheet)
  _delay_ms(50);
  // Function set (still 8 bit interface)
  PORTG |= 0b00100000;
  PORTE |= 0b00001000;
  pulse_E();
  
  // Wait 10 ms (min. 4,1 ms demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  pulse_E();

  // Wait 10 ms (min. 100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (still 8 bit interface)
  pulse_E();

  // Wait 10 ms (min. 100 us demanded according to the data sheet)
  _delay_ms(10);
  // Function set (now selecting 4 bit interface !)
  PORTG &= 0b11011111;
  pulse_E();

  // Function Set : 4 bit interface, 2 line display, 5x8 dots
  sendInstruction( 0b00101000 );
  // Display, cursor and blinking OFF
  sendInstruction( 0b00001000 );
  // Clear display and set DDRAM adr = 0	
  sendInstruction( 0b00000001 );
  // By display writes : Increment cursor / no shift
  sendInstruction( 0b00000110 );
  // Display ON, cursor and blinking ON
  sendInstruction( 0b00001111 );

  Timer_2_Init();
  ADC_Init();
}

// Blanks the display and sets "current display position" to
// the upper line, leftmost character
void LCDClear()
{
  sendInstruction(0b00000001);
}

// Sets DDRAM address to character position x and line number y
void LCDGotoXY( int x, int y )
{
  if(y == 1)
  {
	  x += 40;
  }
  sendInstruction(0b10000000 | x);
}

// Display "ch" at "current display position"
void LCDDispChar(char ch)
{
  sendData(ch);
}

// Displays the string "str" starting at "current display position"
void LCDDispString(char* str)
{
  for(int i = 0; i < strlen(str); ++i)
  {
	  sendData(str[i]);
  }
}

// Displays the value of integer "i" at "current display position"
void LCDDispInteger(int i)
{
  char buffer[20];
  itoa(i, buffer, 10);
  LCDDispString(buffer);
}

// Loads one of the 8 user definable characters (UDC) with a dot-pattern,
// pre-defined in an 8 byte array in FLASH memory
void LCDLoadUDC(unsigned char UDCNo, const unsigned char *UDCTab)
{
	sendInstruction(0b01000000 | (UDCNo<<3));
	for(int i = 0; i < 8; ++i)
	{
		sendData(*UDCTab++);
	}
	LCDGotoXY(0,0);
}

// Selects, if the cursor has to be visible, and if the character at
// the cursor position has to blink.
// "cursor" not 0 => visible cursor.
// "blink" not 0 => the character at the cursor position blinks.
void LCDOnOffControl(unsigned char cursor, unsigned char blink)
{
	int b = 0b00001100;
	if(cursor != 0 && cursor != '0'){
		b |= 1<<1;
	}
	if(blink != 0 && blink != '0'){
		b |= 1;
	}
  sendInstruction(b);
}

// Moves the cursor to the left
void LCDCursorLeft()
{
  sendInstruction(0b00010000);
}

// Moves the cursor to the right
void LCDCursorRight()
{
    sendInstruction(0b00010100);
}

// Moves the display text one position to the left
void LCDShiftLeft()
{
  sendInstruction(0b00011000);
}

// Moves the display text one position to the right
void LCDShiftRight()
{
  sendInstruction(0b00011100);
}

// Sets the backlight intensity to "percent" (0-100)
void setBacklight(unsigned char percent)
{
  if(percent <= 100)
  {
	  OCR2A = (percent*255)/100;
  }
}

// Reads the status for the 5 on board keys
// Returns 0, if no key pressed
unsigned char readKeys()
{
  if(ADCW < 50)
	return 1;
  if(ADCW < 195)
	return 2;
  if(ADCW < 380)
	return 3;
  if(ADCW < 555)
	return 4;
  if(ADCW < 790)
	return 5;
	
  return 0;
}