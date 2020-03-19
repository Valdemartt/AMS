/*
 * TouchDriver.h
 *
 * Created: 19-03-2020 11:05:04
 *  Author: math0
 */ 


#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_

#include "TouchDriver/Position.h"


class TouchDriver
{
public:
	void InitTouch();
	void Calibrate();
	Position getPosition();
	
};





#endif /* TOUCHDRIVER_H_ */