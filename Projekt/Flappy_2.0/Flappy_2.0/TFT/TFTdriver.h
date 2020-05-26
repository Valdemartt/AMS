/************************************************************
  File name: "TFTdriver.c"

/*
 * TFTdriver.h
 *
 * Created: 26-03-2020 09:40:24
 *  Author: math0
 */ 
#ifndef __TFTDriver_H__
#define __TFTDriver_H__
#include "Color.h"
#include "../UIObjects/PipePair.h"
#include "../UIObjects/FlappyObject.h"
#include "FontGenerator.h"
class TFTDriver
{
//Variables
private:
	int _height;
	int _width;
	FontGenerator * _fontGenerator;
public: 
	TFTDriver(int height, int width, FontGenerator * fontGenerator);
	TFTDriver();
	~TFTDriver();
	void Init();
	void Reset();
	void DisplayOff();
	void DisplayOn();
	void FillRectangle(int StartX, int StartY, unsigned int Width,
	unsigned int Height, unsigned int color);
	void DrawGame(PipePair *pillars, int numPillars, FlappyObject *flappy, int speed);
	void DrawBackground(Color *backgroundColor, Color *earthColor, int earthHeight);
	void DisplayInversionOn();
	void DisplayInversionOff();
	int GetHeight();
	int GetWidth();
	void DrawFlappy(FlappyObject * flappy);
	void EraseObjects(PipePair * pipes, int numPairs, FlappyObject * flappy, unsigned int color, int speed);
	void DrawText(const unsigned char * data, long int dataLength, int width, int height, int xCenter, int yCenter, unsigned int backgroundColor, unsigned int textColor);
	void WriteText(char* text, int startX, int startY, unsigned int textColor, unsigned int backgroundColor);
	void UpdateScore(int score, Color * textColor, Color * backgroundColor);
	void DrawScore(int score, Color * textColor, Color * backgroundColor);
	void DrawTextButton(UIObject * button, bool clicked, const unsigned char * data, long int dataLength, int width, int height, unsigned int backgroundColor, unsigned int textColor, int padding);
	//void UpdateDisplay();
private:
	void SleepOut();
	void MemoryAccessControl(unsigned char parameter);
	void InterfacePixelFormat(unsigned char parameter);
	void WritePixel(int encodedColor);
	void SetColumnAddress(unsigned int Start, unsigned int End);
	void SetPageAddress(unsigned int Start, unsigned int End);
	void MemoryWrite();
	void WriteCommand(unsigned int command);
	void WriteData(unsigned int data);
	
};
#endif



