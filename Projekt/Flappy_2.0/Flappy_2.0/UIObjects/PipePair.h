/* 
* PipePair.h
*
* Created: 20-05-2020 09:40:54
* Author: valde
*/


#ifndef __PIPEPAIR_H__
#define __PIPEPAIR_H__

#include "UIObject.h"
class PipePair
{
//variables
public:
protected:
private:
UIObject _upper;
UIObject _lower;

//functions
public:
	PipePair();
	PipePair(UIObject upper, UIObject lower);
	~PipePair();
	UIObject * GetUpper();
	UIObject * GetLower();
	PipePair& operator=( const PipePair &c );
protected:
private:
	PipePair( const PipePair &c );
}; //PipePair

#endif //__PIPEPAIR_H__
