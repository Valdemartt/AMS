/*
 * FlappyObject.h
 *
 * Created: 07-05-2020 10:16:15
 *  Author: math0
 */ 


#ifndef FLAPPYOBJECT_H_
#define FLAPPYOBJECT_H_

#define FLAPPY_HEIGHT 25
#define FLAPPY_LENGTH 32
class FlappyObject
{
	
private:
	int _startX;
	int _startY;
public:	
	FlappyObject(int startX, int startY)
	{
		_startY = startY;
		_startX = startX;
	}
	FlappyObject() 
	{
		_startX = 0;
		_startY = 0;
	}
	int getFlappyHeight()
	{
		return FLAPPY_HEIGHT;
	}
	int getFlappyLength()
	{
		return FLAPPY_LENGTH;
	}
	int GetStartX()
	{
		return _startX;
	}
	int GetStartY() 
	{
		return _startY;
	}
	void SetStartY(int y)
	{
		_startY = y;
	}
	FlappyObject& operator=( const FlappyObject &c ) 
	{
		_startX = c._startX;
		_startY = c._startY;
	}
};

#endif /* FLAPPYOBJECT_H_ */