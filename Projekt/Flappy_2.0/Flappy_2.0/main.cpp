/*
 * Flappy_2.0.cpp
 *
 * Created: 19-03-2020 10:59:50
 * Author : math0
 */ 


#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UARTDriver/uart.c"
#include "TouchDriver/Position.h"
#include "UIObjects/UIObjectFactory.h"
#include "TFT/Color.h"
#include "Game/GameController.h"

#include <util/delay.h>

TouchDriver touchDriver(400, 400, 4095, 320, 240);
Position pos;

int main(void)
{	 
    //Main loop, skal håndtere hele spillet.
	//freeRTOS bør nok benyttes.
	InitUART(9600,8,'N');
	touchDriver.InitTouch();
	Color Blue(0, 0, 255);
	TFTDriver tftDriver(320, 240);
	tftDriver.DisplayInit();
	tftDriver.DrawBackground(&Blue);
	GameController game(&tftDriver, &touchDriver, 42, 30, 50);

	game.StartGame();
    while(true)
    {
		
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