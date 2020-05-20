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
} //PipePair

// default destructor
PipePair::~PipePair()
{
} //~PipePair

PipePair::PipePair(UIObject upper, UIObject lower)
{
	_upper = upper;
	_lower = lower;
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
}

