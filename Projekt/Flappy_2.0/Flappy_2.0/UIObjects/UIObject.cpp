/*
 * UIObject.cpp
 *
 * Created: 30-04-2020 10:55:21
 *  Author: math0
 */ 


#include "UIObject.h"
#include "FlappyObject.h"

UIObject::UIObject(int x, int y, int h, int w, Color *color)
{
	SetStartX(x);
	SetStartY(y);
	SetHeight(h);
	SetWidth(w);
	SetColor(color);
}
UIObject::UIObject()
{
	SetStartX(0);
	SetStartY(0);
	SetHeight(0);
	SetWidth(0);
	Color Black(0,0,0);
	SetColor(&Black);
}

void UIObject::SetStartX(int x)
{
	this->startX = x;
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

void UIObject::SetColor(Color *color)
{
	this->color = color->getEncodedColor();
}

int UIObject::GetHeight()
{
	return this->height;
}

int UIObject::GetStartX()
{
	return this->startX;
}

int UIObject::GetStartY()
{
	return this->startY;
}

int UIObject::GetWidth()
{
	return this->width;
}

unsigned int UIObject::GetColor()
{
	return this->color;
}


