/*
 * Test.c
 *
 * Created: 20-02-2020 10:11:29
 * Author : valde
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"

int main(void)
{
    /* Replace with your application code */
    InitUART(9600, 8, 'N');
	while(1)
	{
		SendString("Oskar er lang");
		_delay_ms(1000);
		
	}
}

