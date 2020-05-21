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

void PhysicsEngine::Update(int elapsedTime, FlappyObject * flappy, bool keyPressed)
{
	FlappyPosition = flappy->GetStartY();
	if(FlappyPosition>0)
	{
		Acceleration = 0;
		Velocity = Velocity - Gravity*2;
	}
	else
	{
		Acceleration = Acceleration + Gravity * elapsedTime/20;
	}
	
	if(Acceleration>=Gravity)
		Acceleration = Gravity;
		
	Velocity = Velocity + Acceleration * elapsedTime/20;
	FlappyPosition = FlappyPosition + Velocity;
	
	flappy->SetStartY(FlappyPosition);

	//if(keyPressed)
	//{
		//flappy->SetStartY(flappy->GetStartY() - 15);
	//}
	//flappy->SetStartY(flappy->GetStartY() + 6);
}
