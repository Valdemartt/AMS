/* 
* GameController.cpp
*
* Created: 07-05-2020 13:04:37
* Author: valde
*/


#include "GameController.h"

// default constructor
GameController::GameController()
{
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
	_pipeDistance = 80;
	_pipeGap = pipeGap;
	_speed = 10;
	_numPipePairs = _tftDriver->GetWidth()/(_pipeWidth + _pipeDistance);
}

void GameController::StartGame()
{
	Color Green(0,255,0);
	Color Blue(0,0,255);
	_isPlaying = true;
	
	PipePair* pipes[_numPipePairs];
	for (int i = 0; i < _numPipePairs; i++)
	{
		_lastPipeOffset = GenerateRandomNumber(50,200);
		UIObject lowerPipe(290, _lastPipeOffset, 240 - _lastPipeOffset, _pipeWidth, &Green);
		UIObject upperPipe(290, 0, 240 - _pipeGap - _lastPipeOffset, _pipeWidth, &Green);
		PipePair pair1 = PipePair(&upperPipe, &lowerPipe);
	}
	_pipes = pipes;
	
	_flappy = UIObject();
	
	_tftDriver->DrawBackground(&Blue);
	_tftDriver->DrawGame(_pipes, sizeof(_pipes), &_flappy);
	while(!DetectCollision() && _isPlaying)
	{
		UpdatePipes();
		UpdateFlappy();
		_tftDriver->DrawGame(_pipes, sizeof(_pipes), &_flappy);
	}
	GameOver();
}
//Taken from https://en.wikipedia.org/wiki/Xorshift
int GameController::GenerateRandomNumber(int min, int max)
{
	long x = _rngState;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	_rngState = x;
	return (_rngState % (max - min)) + min;
}

void GameController::UpdatePipes()
{
	for(int i = 0; i < sizeof(_pipes); ++i)
	{
		//_pipes[i]->SetStartX(_pipes[i]->GetStartX() - _speed);
		//if(_pipes[i]->GetStartX() + _pipes[i]->GetWidth() < 0)
		//{
			//_pipes[i]->SetStartX(_tftDriver->GetWidth());
		//}
		UIObject * lower = _pipes[i]->GetLower();
		UIObject * upper = _pipes[i]->GetUpper();
		lower->SetStartX(lower->GetStartX() - _speed);
		upper->SetStartX(upper->GetStartX() - _speed);
		if((lower->GetStartX() + lower->GetWidth()) < 0)
		{
			_lastPipeOffset = GenerateRandomNumber(50,200);
			lower->SetStartX(_tftDriver->GetWidth());
			upper->SetStartX(_tftDriver->GetWidth());
			upper->SetHeight(_tftDriver->GetHeight() - _pipeGap - _lastPipeOffset);
			lower->SetHeight(_tftDriver->GetHeight() - _lastPipeOffset);
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
	//Check for collision on all objects and flappy
	return false;
}

void GameController::GameOver()
{
	_isPlaying = false;
}
void GameController::StopGame()
{
	_isPlaying = false;
}