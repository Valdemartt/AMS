/* 
* GameController.cpp
*
* Created: 07-05-2020 13:04:37
* Author: valde
*/


#include "GameController.h"
#include "../CollisionDetection.h"
#include "../CheckScore.h"
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
	_score = 0;
	_highscore = 0;
} //GameController

// default destructor
GameController::~GameController()
{
} //~GameController

GameController::GameController(TFTDriver *tftDriver, TouchDriver *touchDriver, PhysicsEngine * engine, long seed, int pipeWidth, int pipeGap)
{
	_tftDriver = tftDriver;
	_touchDriver = touchDriver;
	_engine = engine;
	_rngState = seed;
	_lastPipeOffset = 0;
	_pipeWidth = pipeWidth;
	_pipeDistance = 100;
	_pipeGap = pipeGap;
	_speed = 5;
	_numPipePairs = _tftDriver->GetWidth()/(_pipeWidth + _pipeDistance) + 1;
	_score = 0;
	_highscore = 0;
}

void GameController::StartGame()
{
	Color Green(0,255,0);
	Color Blue(0,0,255);
	Color Brown(42,42,165);
	_isPlaying = true;
	_score = 0;
	_earthHeight = 10;
	
	PipePair pipes[_numPipePairs];
	for (int i = 0; i < _numPipePairs; i++)
	{
		unsigned int temp = GenerateRandomNumber(75,175);
		_lastPipeOffset = temp;
		UIObject lowerPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)) , _lastPipeOffset + _pipeGap/2, _tftDriver->GetHeight() - _lastPipeOffset - _pipeGap/2 - _earthHeight, _pipeWidth, &Green);
		UIObject upperPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)), 0, _lastPipeOffset - _pipeGap/2, _pipeWidth, &Green);
		PipePair pair(upperPipe, lowerPipe);
		pipes[i] = pair;
	}
	_pipes = pipes;
	FlappyObject flappy = FlappyObject(70, 108);
	_flappy = &flappy;
	
	_tftDriver->DrawBackground(&Blue, &Brown, _earthHeight);
	_tftDriver->DrawGame(_pipes, _numPipePairs, _flappy);
}

void GameController::NextFrame(bool screenPressed)
{
	Color Blue(0,0,255);
	_tftDriver->EraseObjects(_pipes, _numPipePairs, _flappy, Blue.getEncodedColor());
	UpdatePipes();
	UpdateFlappy(screenPressed);
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
			lower->SetHeight(_tftDriver->GetHeight() - (_lastPipeOffset + _pipeGap/2) - _earthHeight);
		}
		if(CheckIncrementScore())
		{
			_score++;
		}
	}
}

void GameController::UpdateFlappy(bool screenPressed)
{
	_engine->Update(_speed, _flappy, screenPressed);
}	

bool GameController::IsPlaying()
{
	return _isPlaying;
}

bool GameController::DetectCollision()
{
	for(int i = 0; i < _numPipePairs; i++)
	{
		if(CollisionDetection::CheckCollision(_flappy, &_pipes[i], _tftDriver->GetHeight()-_earthHeight))
			return true;
	}
	return false;
}

bool GameController::CheckIncrementScore()
{
	for(int i = 0; i< _numPipePairs; i++)
	{
		if(CheckScore::CheckIncrementScore(69, &_pipes[i]))
			return true;
	}
	return false;
}

void GameController::GameOver()
{
	Color backgroundColor(0,0,255);
	Color textColor(0,0,0);
	Color earthColor(42,42,165);
	_tftDriver->DrawBackground(&backgroundColor, &earthColor, _earthHeight);
	_tftDriver->DrawText(_gameOverText, _gameOverWidth * _gameOverHeight, _gameOverWidth, _gameOverHeight, 160, 80, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	PipePair pipes[_numPipePairs];
	_pipes = pipes; //reset pipes
	if(_score>_highscore)
	{
		_highscore = _score;
	}
	StopGame();
}
void GameController::StopGame()
{
	_isPlaying = false;
}