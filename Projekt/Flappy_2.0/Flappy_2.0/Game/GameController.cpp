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
	_tftDriver = 0;
	_touchDriver = 0;
	_rngState = 42;
	_lastPipeOffset = 0;
	_pipeWidth = 30;
	_pipeDistance = 80;
	_pipeGap = 50;
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
	_numPipePairs = _tftDriver->GetWidth()/(_pipeWidth + _pipeDistance) + 1;
	_score = 0;
	_highscore = 0;
	_earthHeight = 20;
}

void GameController::StartGame()
{
	Color Green(0,255,0);
	Color Blue(0,0,255);
	Color Brown(42,42,165);
	_isPlaying = true;
	_score = 0;
	_elapsedTimeSinceClick = 0;
	
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
	FlappyObject flappy(70, 108);
	_flappy = flappy;
	
	_tftDriver->DrawBackground(&Blue, &Brown, _earthHeight);
	_tftDriver->DrawGame(_pipes, _numPipePairs, &_flappy, _engine->GetSpeed());
	_tftDriver->DrawScore(_score, &Green, &Brown);
}

void GameController::NextFrame(bool screenPressed)
{
	Color Blue(0,0,255);
	Color Green(0,255,0);
	Color Brown(42,42,165);
	if(DetectCollision())
	{
		GameOver();
		return;
	}
	_tftDriver->EraseObjects(_pipes, GameController::_numPipePairs, &_flappy, Blue.getEncodedColor(), _engine->GetSpeed());
	UpdatePipes();
	UpdateFlappy(screenPressed);

	if(CheckIncrementScore())
	{
		_score++;
		_tftDriver->UpdateScore(_score, &Green, &Brown);
	}
	_tftDriver->DrawGame(_pipes, _numPipePairs, &_flappy, _engine->GetSpeed());
	//_tftDriver->UpdateDisplay();
}

void GameController::Pause()
{
	
}

void GameController::Menu()
{
	Color buttonColor(255,255,255);
	Color backgroundColor(0,0,255);
	Color earthColor(42,42,165);
	Color textColor(0,0,0);
	
	UIObject buttons [1];
	int buttonPadding = 5;
	UIObject startGameButton(_tftDriver->GetWidth()/2 - _startGameWidth + 2*buttonPadding, 180, _startGameHeight + 2*buttonPadding, _startGameWidth + 2*buttonPadding, &buttonColor);
	buttons[0] = startGameButton;
	void (GameController::* callback)() = &GameController::StartGame;
	buttons[0].SetCallback(callback);
	_buttons = buttons;
	_tftDriver->DrawBackground(&backgroundColor, &earthColor, 20);
	_tftDriver->DrawTextButton(&_buttons[0], false, startGameText, sizeof(startGameText), _startGameWidth, _startGameHeight, backgroundColor.getEncodedColor(), textColor.getEncodedColor(), buttonPadding);
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
		lower->SetStartX(lower->GetStartX() - _engine->GetSpeed());
		upper->SetStartX(upper->GetStartX() - _engine->GetSpeed());
		if((lower->GetStartX() + lower->GetWidth()) < 0)
		{
			lower->SetStartX((_pipeDistance * _numPipePairs) + (_numPipePairs - 1) * _pipeWidth);
			upper->SetStartX(lower->GetStartX());
			//Generate new height for pipes
			_lastPipeOffset = GenerateRandomNumber(50,200);
			upper->SetHeight(_lastPipeOffset - _pipeGap/2);
			lower->SetStartY(_lastPipeOffset + _pipeGap/2);
			lower->SetHeight(_tftDriver->GetHeight() - (_lastPipeOffset + _pipeGap/2) - _earthHeight);
		}
	}
}

void GameController::UpdateFlappy(bool screenPressed)
{
	if(screenPressed)
	{
		_elapsedTimeSinceClick = 0;
	}
	else
		_elapsedTimeSinceClick++;
		
	_engine->Update(_elapsedTimeSinceClick, &_flappy, screenPressed);
}	

bool GameController::IsPlaying()
{
	return _isPlaying;
}

bool GameController::DetectCollision()
{
	if(CollisionDetection::CheckEarthCollision(&_flappy, _tftDriver->GetHeight() - _earthHeight ))
		return true;
	for(int i = 0; i < _numPipePairs; i++)
	{
		if(CollisionDetection::CheckCollision(&_flappy, &_pipes[i]))
			return true;
	}
	return false;
}

void GameController::DetectClick(Position * position)
{
	int numButtons = sizeof(_buttons);
	for(int i = 0; i < numButtons; i++)
	{
		if(CollisionDetection::CheckButtonClicked(&_buttons[i], position))
		{
			_buttons[i].Callback(this);
		}
	}
}

bool GameController::CheckIncrementScore()
{
	for(int i = 0; i< _numPipePairs; i++)
	{
		if(CheckScore::CheckIncrementScore(&_flappy, &_pipes[i]))
			return true;
	}
	return false;
}

void GameController::Reset()
{
	_engine->Reset();
	PipePair pipes[_numPipePairs];
	_pipes = pipes; //reset pipes
	_score = 0;
}

void GameController::GameOver()
{
	Color backgroundColor(0,0,255);
	Color textColor(0,0,0);
	Color earthColor(42,42,165);
	Color white(255, 255, 255);
	_tftDriver->DrawBackground(&backgroundColor, &earthColor, _earthHeight);
	_tftDriver->DrawText(_gameOverText, sizeof(_gameOverText), _gameOverWidth, _gameOverHeight, 160, 60, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->DrawText(_scoreText, sizeof(_scoreText), _scoreWidth, _scoreHeight, 140, 120, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	char scoreString [(sizeof(int)*8+1)];
	_tftDriver->WriteText(itoa(_score, scoreString, 10), 200, 112, textColor.getEncodedColor(), backgroundColor.getEncodedColor());
	_tftDriver->DrawText(_highText, sizeof(_highText), _highWidth, _highHeight, 90, 160, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->DrawText(_scoreText, sizeof(_scoreText), _scoreWidth, _scoreHeight, 170, 164, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->WriteText(itoa(_highscore, scoreString, 10), 220, 152, textColor.getEncodedColor(), backgroundColor.getEncodedColor());
	if(_score > _highscore)
	{
		_highscore = _score;
	}
	Reset();
	StopGame();
}
void GameController::StopGame()
{
	_isPlaying = false;
}