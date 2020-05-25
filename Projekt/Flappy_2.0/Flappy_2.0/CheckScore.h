/*
 * CheckScore.h
 *
 * Created: 21-05-2020 09:22:08
 *  Author: math0
 */ 


#ifndef CHECKSCORE_H_
#define CHECKSCORE_H_

#include "UIObjects/FlappyObject.h"
#include "UIObjects/PipePair.h"
#include "UIObjects/UIObject.h"
#include "UART/uart.h"

class CheckScore
{
public:
	static bool CheckIncrementScore(FlappyObject * flappy, PipePair * pipes)
	{
		UIObject lowerPipe = *pipes->GetLower();
		if (flappy->GetStartX() > (lowerPipe.GetStartX() + lowerPipe.GetWidth()) && (pipes->GetIsPassed() == false))
		{
			pipes->SetIsPassed(true);
			return true;
		}
		return false;
	}
};



#endif /* CHECKSCORE_H_ */