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
#include "TFT/Color.h"
#include "Game/GameController.h"
#include "Game/InterruptSetup.h"
#include "TFT/FontGenerator.h"

#include <util/delay.h>

TouchDriver touchDriver(400, 400, 4095, 320, 240);
bool drawNewFrame;
bool gamePaused;
bool screenTouched;
int main(void)
{	 
	gamePaused = false;
    //Main loop, skal håndtere hele spillet.
	//freeRTOS bør nok benyttes.
	InitUART(9600,8,'N');
	touchDriver.InitTouch();
	FontGenerator fontGenerator;
	TFTDriver tftDriver(320, 240, &fontGenerator);
	//tftDriver.DisplayInit();
	PhysicsEngine engine(9.82/2);
	GameController game(&tftDriver, &touchDriver, &engine, 42, 30, 100);
	InterruptSetup::InitFrameTimer();
	game.StartGame();
	screenTouched = false;
	drawNewFrame = true;
    while(true)
    {
		if(game.IsPlaying())
		{
			if(drawNewFrame)
			{
				game.NextFrame(screenTouched);
				screenTouched = false;
				drawNewFrame = false;
			}
		}
		else 
		{
			if(screenTouched)
			{
				game.StartGame();
			}
		}	
    }
}

ISR(INT4_vect)
{
	screenTouched = true;
	//Disable interrupt - will be enable again on timer0 overflow.
	cbi(EIMSK, IRQ_PIN);
	touchDriver.Read();
	//SendChar(' ');
	//SendInteger(touchDriver.getY());
	touchDriver.SetTimer1_EnableInterrupt();
}

ISR(TIMER3_COMPA_vect)
{
	drawNewFrame = true;
}

ISR(TIMER1_COMPA_vect)
{
	TIMSK1 = 0; //Disable timer interrupt
	
	//Disable timer
	TCCR1A = 0;
	TCCR1B = 0;
	
	sbi(EIFR, 4); //Clear INT4 flag if set in mean time to avoid additional interrupts
	sbi(EIMSK, IRQ_PIN); //re-enable interrupt
}