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

TouchDriver touchDriver;


int main(void)
{
	
    //Main loop, skal h�ndtere hele spillet.
	//freeRTOS b�r nok benyttes.
	
	InitUART(9600,8,'N');
	
	touchDriver.InitTouch();
	
	SendString("Started");
	
    while (1) 
    {
		_delay_ms(1);
		
    }
}

ISR (INT4_vect)
{
	touchDriver.Read();
	
	Position pos = touchDriver.getPosition();
	
	SendInteger(pos.getX());
	SendInteger(pos.getY());
	
}

