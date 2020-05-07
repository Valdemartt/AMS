/*
 * UIObject.cpp
 *
 * Created: 30-04-2020 10:55:21
 *  Author: math0
 */ 


#include "UIObject.h"
#include "FlappyObject.h"

UIObject::UIObject(int x, int y, int h, int w)
{
	SetStartX(x);
	SetStartY(y);
	SetHeight(h);
	SetWidth(w);
}

UIObject::UIObject(int x, int y, int h, int w, bool flappy)
{
	SetStartX(x);
	SetStartY(y);
	SetHeight(h);
	SetWidth(w);
	if(flappy)
	{
		FlappyObject bird;
		int* flappyArray = bird.getFlappy();
		SetFlappy(flappyArray);
	}
}

void UIObject::SetStartX(int x)
{
	this->startX = startX;
}

void UIObject::SetStartY(int y)
{
	this->startY = y;
}

void UIObject::SetHeight(int h)
{
	this->height = h;
}

void UIObject::SetWidth(int w)
{
	this->width = w;
}

void UIObject::SetFlappy(int* flappy)
{
	this->flappy=flappy;
}