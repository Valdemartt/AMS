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
#include "../UIObjects/FlappyObject.h"
#include "../UIObjects/UIObject.h"
#include "../PhysicsEngine/PhysicsEngine.h"
class GameController
{
//variables
public:
protected:
private:
	TFTDriver * _tftDriver;
	TouchDriver * _touchDriver;
	PipePair* _pipes;
	FlappyObject* _flappy;
	PhysicsEngine* _engine;
	bool _isPlaying;
	unsigned long _rngState;
	unsigned int _lastPipeOffset;
	int _pipeGap;
	int _pipeWidth;
	int _speed;
	int _score;
	int _highscore;
	int _pipeDistance;
	int _numPipePairs;
//functions
public:
	GameController();
	GameController(TFTDriver* tftDriver, TouchDriver* touchDriver, PhysicsEngine* engine, long seed, int pipeWidth, int pipeGap);
	~GameController();
	void StartGame();
	void StopGame();
	void GameOver();
	bool IsPlaying();
	void NextFrame(bool screenPressed);
	void Pause();
	bool DetectCollision();
	bool CheckIncrementScore();
	unsigned int GenerateRandomNumber(unsigned int min, unsigned int max);
protected:
private:
	GameController( const GameController &c );
	GameController& operator=( const GameController &c );
	void UpdatePipes();
	void UpdateFlappy(bool screenPressed);
}; //GameController

#endif //__GAMECONTROLLER_H__
