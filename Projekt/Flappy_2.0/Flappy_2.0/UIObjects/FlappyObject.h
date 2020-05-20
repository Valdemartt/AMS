/*
 * FlappyObject.h
 *
 * Created: 07-05-2020 10:16:15
 *  Author: math0
 */ 


#ifndef FLAPPYOBJECT_H_
#define FLAPPYOBJECT_H_

#define FLAPPY_HEIGHT 25
#define FLAPPY_LENGTH 64

class FlappyObject
{
	
private:
	int _startX;
	int _startY;
	int flappy[FLAPPY_LENGTH];
public:
	//unsigned int flappy[FLAPPY_HEIGHT][FLAPPY_LENGTH] = {
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0x00, 0x00, 0xff, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xff, 0xff, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0x00, 0x00, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0x00, 0x00, 0x83, 0xff, 0x83, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0x83, 0xff, 0x83, 0xff, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24},
		//{0x00, 0x00, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x00, 0x00, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0xc8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x00, 0x00},
		//{0x00, 0x00, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc8, 0xff, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x00, 0x00},
		//{0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x83, 0xff, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0x21, 0xd2, 0x21, 0xd2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x00, 0x00, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x21, 0xd2, 0x00, 0x00, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0xc2, 0xfd, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24},
		//{0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24, 0xbe, 0x24}};
	
	FlappyObject(int startX, int startY)
	{
		_startY = startY;
		_startX = startX;
		Color yellow(255, 255, 0);
		int encoded = yellow.getEncodedColor();
		for(int i = 0; i < FLAPPY_LENGTH; i++)
		{
			flappy[i] = encoded;
		}
	}
	FlappyObject() 
	{
		_startX = 0;
		_startY = 0;
	}
	int* getFlappy(int index)
	{
		return flappy;
	}
	int getFlappyHeight()
	{
		return FLAPPY_HEIGHT;
	}
	int getFlappyLength()
	{
		return FLAPPY_LENGTH/2;
	}
	int GetStartX()
	{
		return _startX;
	}
	int GetStartY() 
	{
		return _startY;
	}
};

#endif /* FLAPPYOBJECT_H_ */