/* 
* Colors.h
*
* Created: 30-04-2020 10:13:38
* Author: valde
*/


#ifndef __COLORS_H__
#define __COLORS_H__
#include "string.h"
#include <iostream>
#include "Color.h"
class EncodedColorDictionary
{
//variables
public:
protected:
private:
	std::list<std::pair<std::string, int>> _encodedColors;

//functions
public:
	EncodedColorDictionary(std::list<Color> colors);
	EncodedColorDictionary();
	~EncodedColorDictionary();
	int GetColor(std::string name);
protected:
private:
	Colors( const Colors &c );
	Colors& operator=( const Colors &c );
	int EncodeColor(Color color);
}; //Colors

#endif //__COLORS_H__
