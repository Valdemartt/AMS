/* 
* PhysicsEngine.h
*
* Created: 20-05-2020 15:24:33
* Author: math0
*/


#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__
#include "../UIObjects/FlappyObject.h"
class PhysicsEngine
{
//variables
public:
protected:
private:

//functions
public:
	PhysicsEngine();
	~PhysicsEngine();
	void Update(float elapsedTime, FlappyObject * flappy, bool keyPressed);
	
protected:
private:
	PhysicsEngine( const PhysicsEngine &c );
	PhysicsEngine(int Yposition);
	PhysicsEngine& operator=( const PhysicsEngine &c );
	int FlappyPosition = 0;
	float Velocity = 0.0f;
	float Acceleration = 0.0f;
	float Gravity = 6.0f;

}; //PhysicsEngine

#endif //__PHYSICSENGINE_H__
