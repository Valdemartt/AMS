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
	//if(c == 4 || c == 32)
	//{
		//unsigned char* data = code_space;
		//return data;
	//}
	
	if(c > 47 && c < 59)
	{
		unsigned char* data = numbers[c-48];
		return data;
	}
	
	//unsigned char* data = Characters[c-97];
}