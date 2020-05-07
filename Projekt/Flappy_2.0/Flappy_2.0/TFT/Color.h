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
char* _name;
unsigned int _encodedColor;
//functions
public:
	Color(char red, char green, char blue, char* name) 
	{
		_red = red;
		_green = green;
		_blue = blue;
		_name = name;
		
		unsigned int blue_enc = (0b00011111 & blue);
		unsigned int green_enc = (0b00111111 & green);
		unsigned int red_enc = (0b00011111 & red);
		
		unsigned int color = 0;
		color |= blue_enc;
		color |= (green_enc<<6);
		color |= (red_enc<<12);
		_encodedColor = color;
	}
	Color(char red, char green, char blue)
	{
		_red = red;
		_green = green;
		_blue = blue;
		
		unsigned int blue_enc = (0b00011111 & blue);
		unsigned int green_enc = (0b00111111 & green);
		unsigned int red_enc = (0b00011111 & red);
		
		unsigned int color = 0;
		color |= blue_enc;
		color |= (green_enc<<6);
		color |= (red_enc<<12);
		_encodedColor = color;
	}
	Color()
	{
		_red = 0;
		_green = 0;
		_blue = 0;
		_name = "";
		_encodedColor = 0;
	}
	~Color()
	{
		
	}
	char getRed() { return _red; }
	char getGreen() { return _green; }
	char getBlue() { return _blue; }
	char* getName() { return _name; }
	unsigned int getEncodedColor() { return _encodedColor; }	
protected:
private:
	Color( const Color &c );
	Color& operator=( const Color &c );

}; //Color

#endif //__COLOR_H__
