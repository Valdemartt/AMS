/*
 * Process3.c
 *
 * Created: 05-03-2020 10:47:13
 *  Author: math0
 */ 
/******************************************************
FreeRTOS demo program.
Implementing 2 tasks, each blinking a LED.

Target = "Arduino Mega2560" + "PR I/O Shield"

Henning Hargaard 25.2.2018
*******************************************************/
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "switch.h"
#include "semphr.h"
#include "uart.h"

xSemaphoreHandle xSemaphore1 = NULL;
unsigned char counter = 0;
xQueueHandle xQueue1;

void DecrementCountTask1( void *pvParameters )
{
	while(1)
	{
		if(switchOn(0)>0){
			xSemaphoreTake(xSemaphore1,1000);
			if(counter>0)
				counter--;
			xSemaphoreGive(xSemaphore1);
			xQueueSendToBack(xQueue1,&counter,1000);
			vTaskDelay(100);
		}
	}
}

void IncrementCountTask2(void *pvParameters )
{
	while(1)
	{
		if(switchOn(1)>0){
			xSemaphoreTake(xSemaphore1,1000);
			counter++;
			xSemaphoreGive(xSemaphore1);
			xQueueSendToBack(xQueue1,&counter,1000);
			vTaskDelay(100);
		}
	}
}

void ConsumerTask3( void *pvParameters )
{
	unsigned char buffer;
	
	while(1)
	{
		if(xQueueReceive(xQueue1,&buffer,9999)>0)
		{
			writeAllLEDs(buffer);
			SendInteger(buffer);
		}
	}
}

int main(void)
{
	initLEDport();
	initSwitchPort();
	InitUART(9600,8,'N');
	SendString("This is the start of main - Hello");
	vSemaphoreCreateBinary(xSemaphore1);
	xQueue1=xQueueCreate(10,sizeof(unsigned char));
	xTaskCreate( DecrementCountTask1, ( signed char * ) "DEC", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( IncrementCountTask2, ( signed char * ) "INC", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate(ConsumerTask3,( signed char * ) "SW0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	vTaskStartScheduler();
	while(1)
	{}
}


