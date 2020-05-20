/* 
* GameController.h
*
* Created: 07-05-2020 13:04:37
* Author: valde
*/


#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include "../TFT/Color.h"
#include "../TFT/TFTdriver.h"
#include "../TouchDriver/TouchDriver.h"
#include "../UIObjects/PipePair.h"
class GameController
{
//variables
public:
protected:
private:
	TFTDriver * _tftDriver;
	TouchDriver * _touchDriver;
	PipePair** _pipes;
	UIObject _flappy;
	bool _isPlaying;
	long _rngState;
	int _lastPipeOffset;
	int _pipeGap;
	int _pipeWidth;
	int _speed;
	int _score;
	int _pipeDistance;
	int _numPipePairs;
//functions
public:
	GameController();
	GameController(TFTDriver* tftDriver, TouchDriver* touchDriver, long seed, int pipeWidth, int pipeGap);
	~GameController();
	void StartGame();
	void StopGame();
	void GameOver();
	bool IsPlaying();
	int GenerateRandomNumber(int min, int max);
protected:
private:
	GameController( const GameController &c );
	GameController& operator=( const GameController &c );
	void UpdatePipes();
	void UpdateFlappy();
	bool DetectCollision();
}; //GameController

#endif //__GAMECONTROLLER_H__
