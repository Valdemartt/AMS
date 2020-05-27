/* 
* InterruptSetup.h
*
* Created: 20-05-2020 15:18:36
* Author: valde
*/

#ifndef __INTERRUPTSETUP_H__
#define __INTERRUPTSETUP_H__
#include <avr/io.h>

class InterruptSetup
{

//functions
public:
	InterruptSetup();
	~InterruptSetup();
	static void Init() 
	{
		TIMSK3 = 2; //Enable interrupt on compare A for timer 3
		TCCR3A &= 0b11111100; //Set CTC mode
		TCCR3B &= 0b11101111; //Set CTC mode
		TCCR3B |= 0b00001000; //Set CTC mode
		OCR3A = 62500/30; //Compare on when timer reaches 6250 - every 100 ms;
		TCCR3B |= 0b00000100; //Set 256 clock prescaler and start timer
	};
private:
	InterruptSetup( const InterruptSetup &c );
	InterruptSetup& operator=( const InterruptSetup &c );

}; //InterruptSetup

#endif //__INTERRUPTSETUP_H__
