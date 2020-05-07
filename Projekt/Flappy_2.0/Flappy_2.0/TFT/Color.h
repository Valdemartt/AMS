/* 
* Color.h
*
* Created: 30-04-2020 10:19:32
* Author: valde
*/


#ifndef __COLOR_H__
#define __COLOR_H__


class Color
{
//variables
public:
protected:
private:
char _red;
char _green;
char _blue;
std::string _name;
//functions
public:
	Color(char red, char green, char blue, std::string name) 
	{
		_red = red;
		_green = green;
		_blue = blue;
		_name = name;
	}
	Color()
	{
		_red = 0;
		_green = 0;
		_blue = 0;
		_name = "";
	}
	~Color();
	char getRed() { return _red; }
	char getGreen() { return _green; }
	char getBlue() { return _blue }
	std::string getName() { return _name; }
protected:
private:
	Color( const Color &c );
	Color& operator=( const Color &c );

}; //Color

#endif //__COLOR_H__
