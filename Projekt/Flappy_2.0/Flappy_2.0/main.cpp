/*
 * Flappy_2.0.cpp
 *
 * Created: 19-03-2020 10:59:50
 * Author : math0
 */ 


#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TouchDriver/TouchDriver.h"
#include "UARTDriver/uart.c"
#include "TouchDriver/Position.h"
#include <util/delay.h>

TouchDriver touchDriver(400,400,4095, 320, 240);
Position pos;

int main(void)
{	
    //Main loop, skal håndtere hele spillet.
	//freeRTOS bør nok benyttes.
	InitUART(9600,8,'N');
	////_delay_ms(1000);
	touchDriver.InitTouch();
	SendString("RST");
    while(true)
    {
		_delay_ms(1000);
    }
}

ISR(INT4_vect)
{
	//Disable interrupt - will be enable again on timer0 overflow.
	cbi(EIMSK, IRQ_PIN);
	touchDriver.Read();
	SendInteger(touchDriver.getX());
	SendChar(' ');
	SendInteger(touchDriver.getY());
	touchDriver.SetTimer1_EnableInterrupt();
}

ISR(TIMER1_COMPA_vect)
{
	TIMSK1 = 0; //Disable timer interrupt
	
	//Disable timer
	TCCR1A = 0; 
	TCCR1B = 0;
	
	sbi(EIFR, 4); //Clear INT4 flag if set in mean time to avoid additional interrupts
	sbi(EIMSK, IRQ_PIN); //re-enable interrupt
	SendString("Timer interrupt");
}