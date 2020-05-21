/*
 * CollisionDetection.h
 *
 * Created: 20-05-2020 13:03:46
 *  Author: math0
 */ 


#ifndef COLLISIONDETECTION_H_
#define COLLISIONDETECTION_H_

#include "UIObjects/FlappyObject.h"
#include "UIObjects/PipePair.h"
#include "UIObjects/UIObject.h"
#include "UART/uart.h"

class CollisionDetection
{
	public:
		static bool CheckCollision(FlappyObject * flappy, PipePair * pipes, int earth)
		{
			UIObject lowerPipe = *pipes->GetLower();
			UIObject upperPipe = *pipes->GetUpper();
			
			bool collisionLower = 
			flappy->GetStartX() < lowerPipe.GetStartX() + lowerPipe.GetWidth() && 
			flappy->GetStartX() + flappy->getFlappyLength() > lowerPipe.GetStartX() &&
			flappy->GetStartY() < lowerPipe.GetStartY() + lowerPipe.GetHeight() &&
			flappy->GetStartY() + flappy->getFlappyHeight() > lowerPipe.GetStartY();
			
			bool collisionUpper = 
			flappy->GetStartX() < upperPipe.GetStartX() + upperPipe.GetWidth() &&
			flappy->GetStartX() + flappy->getFlappyLength() > upperPipe.GetStartX() &&
			flappy->GetStartY() < upperPipe.GetStartY() + upperPipe.GetHeight() &&
			flappy->GetStartY() + flappy->getFlappyHeight() > upperPipe.GetStartY();
			
			bool groundCollision = ((flappy->GetStartY() + flappy->getFlappyHeight()) > earth);
			
			return collisionLower || collisionUpper || groundCollision;
		};
};

#endif /* COLLISIONDETECTION_H_ */