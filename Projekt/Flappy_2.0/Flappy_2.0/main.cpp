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

TouchDriver touchDriver(300 , 1200, 350, 450, 4095, 320, 240, 3);
FontGenerator fontGenerator;
TFTDriver tftDriver(320, 240, &fontGenerator);
int fps = 30;
PhysicsEngine engine(9.82, 10, 90/fps);

int pipeDistance = 100;
int pipeWidth = 30;
int pipeGap = 100;
GameController game(&tftDriver, &engine, 42, pipeWidth, pipeGap, pipeDistance);

bool drawNewFrame;
bool gamePaused;
bool screenTouched;
bool updating;

int main(void)
{	 
	//Allocate memory for objects
	int numPipes = tftDriver.GetWidth()/(pipeWidth + pipeDistance) + 1;
	PipePair pipes[numPipes];
	int numButtons = game.GetNumButtons();
	UIObject buttons[numButtons];
	
	game.SetPipes(pipes);
	game.SetButtons(buttons);
	
	sei();
	gamePaused = false;
    //Main loop, skal håndtere hele spillet.
	//freeRTOS bør nok benyttes.
	InitUART(9600,8,'N');
	touchDriver.Init();
	tftDriver.Init();
	game.Menu();
	InterruptSetup::Init();
	screenTouched = false;
	drawNewFrame = false;
    while(true)
    {
		//screenTouched = touchDriver.ScreenTouched();
		if(screenTouched && !game.IsPlaying())
		{
			if(touchDriver.ReadPosition());
			{
				Position * pos = touchDriver.GetPosition();
				game.DetectClick(pos);
			}
		}
		if(game.IsPlaying())
		{
			if(drawNewFrame)
			{
				game.NextFrame(screenTouched);
				screenTouched = false;
				drawNewFrame = false;
			}
		}
    }
}

ISR(TIMER3_COMPA_vect)
{
	drawNewFrame = true;
}

ISR(INT4_vect)
{
	screenTouched = true;
	cbi(EIMSK, 4);
	touchDriver.SetTimer1_EnableInterrupt();
}

ISR(TIMER1_COMPA_vect)
{
	sbi(EIFR, 4); //Set flag to 0
	sbi(EIMSK, 4); //Enable interrupt
	TIMSK1 = 0; //Disable timer interrupt
	TCCR1B = 0; //Set timer clock to 0
}
