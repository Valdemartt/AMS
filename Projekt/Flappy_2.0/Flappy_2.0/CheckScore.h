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

class CheckScore
{
public:
	static bool CheckIncrementScore(int xScore, PipePair * pipes)
	{
		UIObject lowerPipe = *pipes->GetLower();
		
		if ((xScore > (lowerPipe.GetStartX() + lowerPipe.GetWidth())) && !pipes->GetIsPassed())
		{
			pipes->SetIsPassed(true);
			return true;
		}
		return false;
	}
protected:
private:
};



#endif /* CHECKSCORE_H_ */