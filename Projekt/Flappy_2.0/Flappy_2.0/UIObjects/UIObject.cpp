/*
 * UIObject.cpp
 *
 * Created: 30-04-2020 10:55:21
 *  Author: math0
 */ 


#include "UIObject.h"

//Starting with 30 pixels.
#define PIPE_SPAWN_LENGTH 30;

UIObject::UIObject(int x, int y, int h, int w)
{
	SetStartX(x);
	SetStartY(y);
	SetHeight(h);
	SetWidth(w);
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