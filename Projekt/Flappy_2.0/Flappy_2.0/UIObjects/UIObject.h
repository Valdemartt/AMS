/*
 * UIObject.h
 *
 * Created: 30-04-2020 11:03:43
 *  Author: math0
 */ 


#ifndef UIOBJECT_H_
#define UIOBJECT_H_

class UIObject
{
	public:
		UIObject();
		UIObject(int startX, int startY, int height, int width);

	private:
		int startX;
		int startY;
		int height;
		int width;
		void SetStartX(int startX);
		void SetStartY(int startY);
		void SetHeight(int height);
		void SetWidth(int width);
	
};

#endif /* UIOBJECT_H_ */