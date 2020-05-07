/*
 * UIObjectFactory.cpp
 *
 * Created: 30-04-2020 11:16:51
 *  Author: math0
 */ 

#include "UIObjectFactory.h"
#include "UIObject.h"

UIObjectFactory::UIObjectFactory()
{
	
}

UIObject UIObjectFactory::CreateObject(int startX, int startY, int height, int width)
{
	object = UIObject(startX,startY,height,width);
	return object;
}