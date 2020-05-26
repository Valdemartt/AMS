/*
 * UIObject.h
 *
 * Created: 30-04-2020 11:03:43
 *  Author: math0
 */ 


#ifndef UIOBJECT_H_
#define UIOBJECT_H_

#include "../TFT/Color.h"

#define PIPE_SPAWN_LENGTH 50
class GameController;
typedef void (GameController::* gameControllerCallback)();

class UIObject
{
	public:
		UIObject();
		UIObject(int startX, int startY, int height, int width, Color *color);
		int GetStartX();
		int GetStartY();
		int GetHeight();
		int GetWidth();
		void SetStartX(int startX);
		void SetStartY(int startY);
		void SetHeight(int height);
		void SetWidth(int width);
		void SetColor(Color * color);
		void SetCallback(gameControllerCallback callback) { _callback = callback; };
		void Callback(GameController * game) { (game->*_callback)(); };
		unsigned int GetColor();
		UIObject& operator=( const UIObject &c );
	private:
		int startX;
		int startY;
		int height;
		int width;
		unsigned int color;
		gameControllerCallback _callback;
};

#endif /* UIOBJECT_H_ */