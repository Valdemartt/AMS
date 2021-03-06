/*
 * TouchDriver.h
 *
 * Created: 19-03-2020 11:05:04
 *  Author: math0
 */ 


#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_

#include "Position.h"
#include <avr/io.h>

#define sbi(b,n) ((b) |= (1<<(n)))			// Set bit number n in byte b
#define cbi(b,n) ((b) &= (~(1<<(n))))		// Clear bit number n in byte b
#define rbi(b,n) ((b) & (1<<(n)))			// Read bit number n in byte b

#define CLK_PORT PORTH
#define CLK_PIN 3
#define CLK_DDR DDRH
#define CS_PORT PORTE
#define CS_PIN 3
#define CS_DDR DDRE
#define DIN_PORT PORTG
#define DIN_PIN 5
#define DIN_DDR DDRG
#define DOUT_PORT PINE
#define DOUT_PIN 5
#define DOUT_DDR DDRE
#define IRQ_PORT PINE
#define IRQ_PIN 4
#define IRQ_DDR DDRE

#define ADC_RES_MAX 4096
#define ADC_RES_MIN 0

class TouchDriver
{
public:
	TouchDriver();
	TouchDriver(int xRightOffset, int xLeftOffset, int yTopOffset, int yBottomOffset, int conversion_resolution, int x_pixels, int y_pixels, int precision);
	void Init();
	int getX();
	int getY();
	bool ReadPosition();
	bool ScreenTouched();
	void SetTimer1_EnableInterrupt();
	Position * GetPosition() { return &position; };
private:
	void WriteData(unsigned char data);
	int16_t ReadData();
	void ClockPulse();
	void ClearClock();
	Position position;
	int _xRightOffset;
	int _xLeftOffset;
	int _yTopOffset;
	int _yBottomOffset;
	int _timer0_duration;
	int _conversionResolution;
	int _xPixels;
	int _yPixels;
	int _xResPerPixel;
	int _yResPerPixel;
	int _precision;
};
#endif /* TOUCHDRIVER_H_ */