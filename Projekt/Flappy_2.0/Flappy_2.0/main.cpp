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
PhysicsEngine engine(9.82/10, 5);
GameController game(&tftDriver, &touchDriver, &engine, 42, 30, 100);
bool drawNewFrame;
bool gamePaused;
bool screenTouched;
bool updating;
int main(void)
{	 
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
		screenTouched = touchDriver.ScreenTouched();
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
