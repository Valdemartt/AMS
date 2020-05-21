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


class CollisionDetection
{
	public:
		static bool CheckCollision(FlappyObject * flappy, PipePair * pipes)
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
			
			
			return (collisionLower || collisionUpper);
		};
		static bool  CheckEarthCollision(FlappyObject * flappy, int earth)
		{
			bool groundCollision = flappy->GetStartX()+flappy->getFlappyHeight() > earth;
			return groundCollision;
		}
};

#endif /* COLLISIONDETECTION_H_ */