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
		static bool CheckCollision(FlappyObject * flappy, PipePair * pipes)
		{
			int flappyStartX, flappyEndX, flappyStartY, flappyEndY;
			flappyStartX = flappy->GetStartX();
			flappyEndX = flappyStartX + flappy->getFlappyLength();
			flappyStartY = flappy->GetStartY();
			flappyEndY = flappyStartY + flappy->getFlappyHeight();

			int lowerPipeStartX = pipes->GetLower()->GetStartX();
			int lowerPipeEndX = lowerPipeStartX + pipes->GetLower()->GetWidth();
			int lowerPipeStartY = pipes->GetLower()->GetStartY();
			int lowerPipeEndY = lowerPipeStartY + pipes->GetLower()->GetHeight();
			
			bool collisionLower = 
			flappyStartX < lowerPipeEndX &&
			flappyEndX > lowerPipeStartX &&
			flappyStartY < lowerPipeEndY &&
			flappyEndY > lowerPipeStartY;
			 
			bool collisionUpper = false;
			
			int upperPipeStartX = pipes->GetUpper()->GetStartX();
			int upperPipeEndX = upperPipeStartX + pipes->GetUpper()->GetWidth();
			int upperPipeStartY = pipes->GetUpper()->GetStartY();
			int upperPipeEndY = upperPipeStartY + pipes->GetUpper()->GetHeight();
			
			if(!collisionLower)
			{
				collisionUpper = 
				flappyStartX < upperPipeEndX &&
				flappyEndX > upperPipeStartX &&
				flappyStartY < upperPipeEndY &&
				flappyEndY > upperPipeStartY;
			}
			
			return (collisionLower || collisionUpper);
		};
		static bool CheckEarthCollision(FlappyObject * flappy, int earth)
		{
			bool groundCollision = flappy->GetStartY() + flappy->getFlappyHeight() > earth;
				
			return groundCollision;
		}
		
		static bool CheckButtonClicked(UIObject * button, Position * clickPosition)
		{
			return (clickPosition->getX() > button->GetStartX() && 
				clickPosition->getX() < button->GetStartX() + button->GetWidth() &&
				clickPosition->getY() > button->GetStartY() &&
				clickPosition->getY() < button->GetStartY() + button->GetHeight());
		}
};

#endif /* COLLISIONDETECTION_H_ */