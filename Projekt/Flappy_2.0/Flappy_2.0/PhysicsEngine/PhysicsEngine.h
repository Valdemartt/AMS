/* 
* PhysicsEngine.h
*
* Created: 20-05-2020 15:24:33
* Author: math0
*/


#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__

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
	void KeyPressed();
	void Update(float elapsedTime);
	
protected:
private:
	bool keyPressed = false;
	PhysicsEngine( const PhysicsEngine &c );
	PhysicsEngine(int Yposition);
	PhysicsEngine& operator=( const PhysicsEngine &c );
	int FlappyPosition = 0;
	float Velocity = 0.0f;
	float Acceleration = 0.0f;
	float Gravity = 100.0f;

}; //PhysicsEngine

#endif //__PHYSICSENGINE_H__
