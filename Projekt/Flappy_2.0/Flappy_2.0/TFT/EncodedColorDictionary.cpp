/* 
* Colors.cpp
*
* Created: 30-04-2020 10:13:38
* Author: valde
*/


#include "EncodedColorDictionary.h"

EncodedColorDictionary::EncodedColorDictionary(std::list<Color> colors)
{
	for (std::list<Color>::const_iterator it = colors.begin(); it != colors.end(); ++it)
	{
		_encodedColors.push_back(std::pair(*it->getName(), EncodeColor(*it)));
	}
}
// default constructor
EncodedColorDictionary::EncodedColorDictionary()
{
	
}
int EncodedColorDictionary::EncodeColor(Color color)
{
	unsigned int blue = (0b00011111 & color.getBlue());
	unsigned int green = (0b00111111 & color.getGreen());
	unsigned int red = (0b00011111 & color.getRed());
	
	unsigned int color = 0;
	color |= blue;
	color |= (green<<6);
	color |= (red<<12);
	return color;
}
int EncodedColorDictionary::GetColor(std::string name)
{
	for (std::list<std::pair<std::string, int>>::const_iterator it = _encodedColors.begin(); it != _encodedColors.end(); ++it)
	{
		if(*it->first == name)
		{
			return *it->second;
		}
	}
	return 0;
}
// default destructor
EncodedColorDictionary::~EncodedColorDictionary()
{
	
} //~Colors
