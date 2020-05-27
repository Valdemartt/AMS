/* 
* PhysicsEngine.cpp
*
* Created: 20-05-2020 15:24:33
* Author: math0
*/


#include "PhysicsEngine.h"
#include "../UART/uart.h"

PhysicsEngine::PhysicsEngine()
{
	_gravity = 9.82;
	Velocity = 0;
	Acceleration = 0;
}

PhysicsEngine::PhysicsEngine(double gravity, double fps, int speed)
{
	_gravity = gravity;
	Velocity = 0;
	Acceleration = 0;
	_fps = fps;
	_speed = speed;
	_startSpeed = speed;
} 

// default destructor
PhysicsEngine::~PhysicsEngine()
{
} //~PhysicsEngine

void PhysicsEngine::Update(int elapsedTime, FlappyObject * flappy, bool keyPressed)
{
	int posY = flappy->GetStartY();
	if(posY > 0)
	{
		if(keyPressed) //If screen pressed - increase acceleration
		{
			if(Acceleration < 0)
				Acceleration = 0;
			if(Velocity < 0)
				Velocity = 0;
			Acceleration += _gravity/4;
		}
		//Gravity
		Acceleration -= _gravity/(_fps*2);
		
		if(Acceleration > (_gravity/2))
			Acceleration = (_gravity/2);
			
		if(Acceleration < - _gravity)
			Acceleration = - _gravity;
		
		//Increase velocity
		Velocity += Acceleration;
		//Invert 
		posY -= (int)Velocity/_fps;
		
		flappy->SetStartY(posY);
	}
	else
	{
		flappy->SetStartY(1);	
		Acceleration = 0;
		Velocity = 0;
	}
}

void PhysicsEngine::Reset()
{
	Acceleration = 0;
	Velocity = 0;
	_speed = _startSpeed;
}