/* 
* PipePair.cpp
*
* Created: 20-05-2020 09:40:54
* Author: valde
*/


#include "PipePair.h"

// default constructor
PipePair::PipePair()
{
	_passed = false;
} //PipePair

// default destructor
PipePair::~PipePair()
{
} //~PipePair

PipePair::PipePair(UIObject upper, UIObject lower)
{
	_upper = upper;
	_lower = lower;
	_passed = false;
}

UIObject * PipePair::GetLower()
{
	return &_lower;
}
UIObject * PipePair::GetUpper()
{
	return &_upper;
}
PipePair& PipePair::operator=( const PipePair &c )
{
	_upper = c._upper;
	_lower = c._lower;
	_passed = false;
}

PipePair::PipePair( const PipePair &c )
{
	_upper = c._upper;
	_lower = c._lower;
	_passed = c._passed;
}

bool PipePair::GetIsPassed()
{
	return _passed;
}

void PipePair::SetIsPassed(bool passed)
{
	_passed = passed;
}
