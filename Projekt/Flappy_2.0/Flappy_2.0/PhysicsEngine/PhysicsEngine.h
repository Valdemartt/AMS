/* 
* PhysicsEngine.h
*
* Created: 20-05-2020 15:24:33
* Author: math0
*/


#ifndef __PHYSICSENGINE_H__
#define __PHYSICSENGINE_H__
#include "../UIObjects/FlappyObject.h"
#include <stdio.h>
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
	PhysicsEngine(double gravity, double fps, int speed);
	void Update(int elapsedTime, FlappyObject * flappy, bool keyPressed);
	void Reset();
	double GetFps() { return _fps; };
	void SetFps(double fps) { _fps = fps; };
	int GetSpeed() { return _speed; };
	void SetSpeed(int speed) { _speed = speed; };
protected:
private:
	PhysicsEngine( const PhysicsEngine &c );
	PhysicsEngine& operator=( const PhysicsEngine &c );
	double Velocity = 0;
	double Acceleration = 0; 
	double _gravity = 0;
	double _fps = 0;
	int _speed = 0;
	int _startSpeed = 0;

}; //PhysicsEngine

#endif //__PHYSICSENGINE_H__
