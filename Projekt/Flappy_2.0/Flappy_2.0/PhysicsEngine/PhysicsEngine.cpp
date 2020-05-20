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

void PhysicsEngine::Update(float elapsedTime, FlappyObject * flappy, bool keyPressed)
{
	//if(keyPressed && Velocity >= Gravity / 5.0f)
	//{
		//Acceleration = 0.0f;
		//Velocity = -Gravity / 3.0f;
	//}
	//else
	//{
		//Acceleration += Gravity * elapsedTime;
	//}
	//if(Acceleration>=Gravity)
	//{
		//Acceleration = Gravity;
	//}
	//Velocity += Acceleration * elapsedTime;
	//FlappyPosition += Velocity * elapsedTime;	
	//flappy->SetStartY(FlappyPosition);
	//keyPressed=false;
	if(keyPressed)
	{
		flappy->SetStartY(flappy->GetStartY() - 15);
	}
	flappy->SetStartY(flappy->GetStartY() + 3);
}
