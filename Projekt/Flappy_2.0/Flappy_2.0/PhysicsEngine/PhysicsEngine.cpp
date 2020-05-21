/* 
* PhysicsEngine.cpp
*
* Created: 20-05-2020 15:24:33
* Author: math0
*/


#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine()
{
	
}

PhysicsEngine::PhysicsEngine(int Yposition)
{
	FlappyPosition = Yposition;
} 

// default destructor
PhysicsEngine::~PhysicsEngine()
{
} //~PhysicsEngine

void PhysicsEngine::Update(double elapsedTime, FlappyObject * flappy, bool keyPressed)
{
	FlappyPosition = flappy->GetStartY();
	
	if(keyPressed && Velocity >= Gravity / 4)
	{
		Acceleration = 0;
		Velocity = -Gravity / 2;
	}
	else
	{
		Acceleration += Gravity * elapsedTime;
	}
	if(Acceleration>=Gravity)
		Acceleration = Gravity;
	
	Velocity += Acceleration * elapsedTime;
	FlappyPosition += Velocity * elapsedTime;
	
	flappy->SetStartY(FlappyPosition);
	
	//if(keyPressed)
	//{
		//flappy->SetStartY(flappy->GetStartY() - 15);
	//}
	//flappy->SetStartY(flappy->GetStartY() + 6);
}
