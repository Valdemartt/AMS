/*
 * UIObject.h
 *
 * Created: 30-04-2020 11:03:43
 *  Author: math0
 */ 


#ifndef UIOBJECT_H_
#define UIOBJECT_H_

#define PIPE_SPAWN_LENGTH 50

class UIObject
{
	public:
		UIObject();
		UIObject(int startX, int startY, int height, int width);
		UIObject(int startX, int startY, int height, int width, bool flappy);

	private:
		int* flappy;
		int startX;
		int startY;
		int height;
		int width;
		void SetStartX(int startX);
		void SetStartY(int startY);
		void SetHeight(int height);
		void SetWidth(int width);
		void SetFlappy(int* flappy);
};

#endif /* UIOBJECT_H_ */