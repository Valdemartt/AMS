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

GameController::GameController(TFTDriver *tftDriver, PhysicsEngine * engine, long seed, int pipeWidth, int pipeGap, int pipeDistance)
{
	_tftDriver = tftDriver;
	_engine = engine;
	_rngState = seed;
	_lastPipeOffset = 0;
	_pipeWidth = pipeWidth;
	_pipeDistance = pipeDistance;
	_pipeGap = pipeGap;
	_numPipePairs = _tftDriver->GetWidth()/(_pipeWidth + _pipeDistance) + 1;
	_score = 0;
	_highscore = 0;
	_earthHeight = 20;
	_numButtons = 1;
}

void GameController::SetPipes(PipePair * pipes)
{
	_pipes = pipes;
}

void GameController::SetButtons(UIObject * buttons)
{
	_buttons = buttons;
}

void GameController::StartGame()
{
	Color Green(0,255,0);
	Color Blue(0,0,255);
	Color Brown(42,42,165);
	_isPlaying = true;
	_score = 0;
	_elapsedTimeSinceClick = 0;
	
	for (int i = 0; i < _numPipePairs; i++)
	{
		unsigned int temp = GenerateRandomNumber(75,175);
		_lastPipeOffset = temp;
		UIObject lowerPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)) , _lastPipeOffset + _pipeGap/2, _tftDriver->GetHeight() - _lastPipeOffset - _pipeGap/2 - _earthHeight, _pipeWidth, &Green);
		UIObject upperPipe(_tftDriver->GetWidth() + (i * (_pipeDistance + _pipeWidth)), 0, _lastPipeOffset - _pipeGap/2, _pipeWidth, &Green);
		PipePair pair(upperPipe, lowerPipe);
		_pipes[i] = pair;
	}
	FlappyObject flappy(70, 108);
	_flappy = flappy;
	
	_tftDriver->DrawBackground(&Blue, &Brown, _earthHeight);
	_tftDriver->DrawGame(_pipes, _numPipePairs, &_flappy, _engine->GetSpeed());
	_tftDriver->DrawScore(_score, &Green, &Brown);
}

int GameController::GetNumPipes()
{
	return _numPipePairs;
}

int GameController::GetNumButtons() 
{
	return _numButtons;
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
	_tftDriver->EraseObjects(_pipes, _numPipePairs, &_flappy, Blue.getEncodedColor(), _engine->GetSpeed());
	UpdatePipes();
	UpdateFlappy(screenPressed);

	if(CheckIncrementScore())
	{
		_score++;
		_tftDriver->UpdateScore(_score, &Green, &Brown);
		if((_score % 7) == 0 && _score != 0)
		{
			_engine->SetSpeed(_engine->GetSpeed() + 1);
		}
	}
	_tftDriver->DrawGame(_pipes, _numPipePairs, &_flappy, _engine->GetSpeed());
	
}

void GameController::Pause()
{
	
}

void GameController::Menu()
{
	Color buttonColor(255,255,0);
	Color backgroundColor(0,0,255);
	Color earthColor(42,42,165);
	Color textColor(0,0,0);
	
	int buttonPadding = 20;
	UIObject startGameButton(_tftDriver->GetWidth()/2 - (_startGameWidth + 2*buttonPadding)/2, _tftDriver->GetHeight()/2, _startGameHeight + 2*buttonPadding, _startGameWidth + 2*buttonPadding, &buttonColor);
	gameControllerCallback callback = &GameController::StartGame;
	startGameButton.SetCallback(callback);
	_buttons[0] = startGameButton;
	_tftDriver->DrawBackground(&backgroundColor, &earthColor, 20);
	_tftDriver->DrawTextButton(&_buttons[0], false, startGameText, sizeof(startGameText), _startGameWidth, _startGameHeight, startGameButton.GetColor(), textColor.getEncodedColor(), buttonPadding);
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
			_pipes[i].SetIsPassed(false);
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
	for(int i = 0; i < _numButtons; i++)
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
	_score = 0;
}

void GameController::GameOver()
{
	Color backgroundColor(0,0,255);
	Color textColor(0,0,0);
	Color earthColor(42,42,165);
	_tftDriver->DrawBackground(&backgroundColor, &earthColor, _earthHeight);
	_tftDriver->DrawText(_gameOverText, sizeof(_gameOverText), _gameOverWidth, _gameOverHeight, 160, 40, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->DrawText(_scoreText, sizeof(_scoreText), _scoreWidth, _scoreHeight, 140, 100, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	char scoreString [(sizeof(int)*8+1)];
	
	_tftDriver->WriteText(itoa(_score, scoreString, 10), 170, 92, textColor.getEncodedColor(), backgroundColor.getEncodedColor());
	_tftDriver->DrawText(_highText, sizeof(_highText), _highWidth, _highHeight, 90, 140, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->DrawText(_scoreText, sizeof(_scoreText), _scoreWidth, _scoreHeight, 160, 144, backgroundColor.getEncodedColor(), textColor.getEncodedColor());
	_tftDriver->WriteText(itoa(_highscore, scoreString, 10), 190, 132, textColor.getEncodedColor(), backgroundColor.getEncodedColor());
	
	_buttons[0].SetStartY(165);
	_buttons[0].SetHeight(40);
	int buttonPadding = 5;
	_tftDriver->DrawTextButton(&_buttons[0], false, startGameText, sizeof(startGameText), _startGameWidth, _startGameHeight, _buttons[0].GetColor(), textColor.getEncodedColor(), buttonPadding);
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