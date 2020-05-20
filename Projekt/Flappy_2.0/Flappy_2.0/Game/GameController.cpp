/* 
* GameController.cpp
*
* Created: 07-05-2020 13:04:37
* Author: valde
*/


#include "GameController.h"
#include "../CollisionDetection.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>

// default constructor
GameController::GameController()
{
	_tftDriver = nullptr;
	_touchDriver = nullptr;
	_rngState = 42;
	_lastPipeOffset = 0;
	_pipeWidth = 30;
	_pipeDistance = 80;
	_pipeGap = 50;
	_speed = 10;
	_numPipePairs = 2;
} //GameController

// default destructor
GameController::~GameController()
{
} //~GameController

GameController::GameController(TFTDriver *tftDriver, TouchDriver *touchDriver, long seed, int pipeWidth, int pipeGap)
{
	_tftDriver = tftDriver;
	_touchDriver = touchDriver;
	_rngState = seed;
	_lastPipeOffset = 0;
	_pipeWidth = pipeWidth;
	_pipeDistance = 60;
	_pipeGap = pipeGap;
	_speed = 3;
	_numPipePairs = _tftDriver->GetWidth()/(_pipeWidth + _pipeDistance) + 1;
}

void GameController::StartGame()
{
	Color Green(0,255,0);
	Color Blue(0,0,255);
	_isPlaying = true;
	
	PipePair pipes[_numPipePairs];
	for (int i = 0; i < _numPipePairs; i++)
	{
		unsigned int temp = GenerateRandomNumber(75,175);
		_lastPipeOffset = temp;
		UIObject lowerPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)) , _lastPipeOffset + _pipeGap/2, _tftDriver->GetHeight() - _lastPipeOffset - _pipeGap/2, _pipeWidth, &Green);
		UIObject upperPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)), 0, _lastPipeOffset - _pipeGap/2, _pipeWidth, &Green);
		PipePair pair(upperPipe, lowerPipe);
		pipes[i] = pair;
	}
	_pipes = pipes;
	FlappyObject flappy = FlappyObject(70, 108);
	_flappy = &flappy;
	
	_tftDriver->DrawBackground(&Blue);
	_tftDriver->DrawGame(_pipes, _numPipePairs, _flappy);
}

void GameController::NextFrame()
{
	Color Blue(0,0,255);
	_tftDriver->ErasePipes(_pipes, _numPipePairs, Blue.getEncodedColor());
	UpdatePipes();
	UpdateFlappy();
	_tftDriver->DrawGame(_pipes, _numPipePairs, _flappy);
}

void GameController::Pause()
{
	
}

//Taken from https://en.wikipedia.org/wiki/Xorshift
unsigned int GameController::GenerateRandomNumber(unsigned int min, unsigned int max)
{
	unsigned long x = _rngState;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	_rngState = x;
	return (_rngState % (max - min)) + min;
}

void GameController::UpdatePipes()
{
	for(int i = 0; i < _numPipePairs; ++i)
	{
		UIObject * lower = _pipes[i].GetLower();
		UIObject * upper = _pipes[i].GetUpper();
		lower->SetStartX(lower->GetStartX() - _speed);
		upper->SetStartX(upper->GetStartX() - _speed);
		if((lower->GetStartX() + lower->GetWidth()) < 0)
		{
			lower->SetStartX(_tftDriver->GetWidth());
			upper->SetStartX(_tftDriver->GetWidth());
			//Generate new height for pipes
			_lastPipeOffset = GenerateRandomNumber(50,200);
			upper->SetHeight(_lastPipeOffset - _pipeGap/2);
			lower->SetStartY(_lastPipeOffset + _pipeGap/2);
			lower->SetHeight(_tftDriver->GetHeight() - (_lastPipeOffset + _pipeGap/2));
		}
	}
}

void GameController::UpdateFlappy()
{
	
}	

bool GameController::IsPlaying()
{
	return _isPlaying;
}

bool GameController::DetectCollision()
{
	for(int i = 0; i < _numPipePairs; i++)
	{
		if(CollisionDetection::CheckCollision(_flappy, &_pipes[i]))
			return true;
	}
	return false;
}

void GameController::GameOver()
{
	Color color(0,0,0);
	_tftDriver->DrawBackground(&color);
	StopGame();
}
void GameController::StopGame()
{
	_isPlaying = false;
}