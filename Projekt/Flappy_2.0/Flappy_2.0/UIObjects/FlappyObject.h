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
public:
	static int flappy[FLAPPY_HEIGHT][FLAPPY_LENGTH];
	int* getFlappy()
	{
		int* flappyAdd = &flappy[FLAPPY_HEIGHT][FLAPPY_LENGTH];
		return flappyAdd;
	}
	int getFlappyHeight()
	{
		return FLAPPY_HEIGHT;
	}
	int getFlappyLength()
	{
		return FLAPPY_LENGTH;
	}
};



#endif /* FLAPPYOBJECT_H_ */