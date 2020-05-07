/*
 * FlappyObject.h
 *
 * Created: 07-05-2020 10:16:15
 *  Author: math0
 */ 


#ifndef FLAPPYOBJECT_H_
#define FLAPPYOBJECT_H_

#define FLAPPY_SIZE 30

class FlappyObject
{
public:
	static int flappy[FLAPPY_SIZE][FLAPPY_SIZE];
	int* getFlappy()
	{
		int* flappyAdd = &flappy[FLAPPY_SIZE][FLAPPY_SIZE];
		return flappyAdd;
	}
	int getFlappySize()
	{
		return FLAPPY_SIZE;
	}
};



#endif /* FLAPPYOBJECT_H_ */