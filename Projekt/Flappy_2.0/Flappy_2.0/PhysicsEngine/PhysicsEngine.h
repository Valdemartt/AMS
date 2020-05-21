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
	void Update(int elapsedTime, FlappyObject * flappy, bool keyPressed);
	
protected:
private:
	PhysicsEngine( const PhysicsEngine &c );
	PhysicsEngine(int Yposition);
	PhysicsEngine& operator=( const PhysicsEngine &c );
	int FlappyPosition = 0;
	int Velocity = 0;
	int Acceleration = 0;
	int Gravity = 10;

}; //PhysicsEngine

#endif //__PHYSICSENGINE_H__
