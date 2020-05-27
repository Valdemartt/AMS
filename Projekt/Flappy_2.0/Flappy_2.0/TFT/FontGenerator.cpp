/* 
* FontGenerator.cpp
*
* Created: 21-05-2020 13:53:12
* Author: valde
*/


#include "FontGenerator.h"

// default constructor
FontGenerator::FontGenerator()
{
} //FontGenerator

// default destructor
FontGenerator::~FontGenerator()
{
} //~FontGenerator

unsigned char* FontGenerator::GetCharacter(char c)
{
	if(c > 47 && c < 59)
	{
		unsigned char* data = numbers[c-48];
		return data;
	}
}