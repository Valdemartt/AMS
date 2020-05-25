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

PhysicsEngine::PhysicsEngine(double gravity)
{
	_gravity = gravity;
	Velocity = 0;
	Acceleration = 0;
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
		//if(keyPressed && Velocity >= _gravity / 10)
		//{
			//Acceleration = 0;
			//Velocity = Velocity - _gravity;
		//}
		//else
		//{
			//Acceleration = Acceleration + _gravity * elapsedTime/20;
		//}
		//
		//if(Acceleration>=_gravity)
		//Acceleration = _gravity;
		//
		//Velocity = Velocity + Acceleration * elapsedTime/20;
		//posY = posY + Velocity;
		//
		//flappy->SetStartY(posY);
		
		if(keyPressed) //If screen pressed - increase acceleration
		{
			Acceleration = 0;
			Velocity = 0;
			Acceleration += _gravity/5;
			posY -= 7;
		}
		//Gravity
		Acceleration -= _gravity/20;
		
		if(Acceleration > _gravity * 2)
			Acceleration = _gravity * 2;
			
		if(Acceleration < - _gravity)
			Acceleration = - _gravity;
		
		//Increase velocity
		Velocity += Acceleration;
		//Invert 
		posY -= (int)Velocity;
		
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
}