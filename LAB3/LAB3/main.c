/*
 * LAB3.c
 *
 * Created: 06-02-2020 09:18:46
 * Author : valde
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "LCDDriver.h"


int main(void)
{
	LCDInit();
    /* Replace with your application code */
	char smiley[8] = {0, 10, 10, 10, 0, 17, 14, 0};
	LCDLoadUDC(1, smiley);
    while (1) 
    {
		LCDDispChar(1);
		_delay_ms(500);
    }
}

