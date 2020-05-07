/*
 * UIObjectFactory.cpp
 *
 * Created: 30-04-2020 11:16:51
 *  Author: math0
 */ 

#include "UIObjectFactory.h"

UIObjectFactory::UIObjectFactory()
{
	
}

UIObject UIObjectFactory::CreateObject(int startX, int startY, int height, int width)
{
	Color Black(0,0,0);
	UIObject object(startX,startY,height,width, &Black);
	return object;
}
UIObject UIObjectFactory::CreateRectangle(int startX, int startY, int height, int width, Color* color)
{
	UIObject object(startX, startY, height, width, color);
	return object;
}