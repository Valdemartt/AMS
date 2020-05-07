/*
 * UIObjectFactory.h
 *
 * Created: 30-04-2020 11:10:19
 *  Author: math0
 */ 


#include "UIObject.h"

#ifndef UIOBJECTFACTORY_H_
#define UIOBJECTFACTORY_H_

class UIObjectFactory
{
	public:
		UIObjectFactory();
		UIObject CreateObject(int startX, int startY, int height, int width);
		UIObject CreateRectangle(int startX, int startY, int height, int width, Color* color);
	private:
		UIObject object;
};



#endif /* UIOBJECTFACTORY_H_ */