///******************************************************
//FreeRTOS demo program.
//Implementing 2 tasks, each blinking a LED.
//
//Target = "Arduino Mega2560" + "PR I/O Shield"
//
//Henning Hargaard 25.2.2018
//*******************************************************/
//#include <avr/io.h>
//#include "FreeRTOS.h"
//#include "task.h"
//#include "led.h"
//#include "switch.h"
//#include "semphr.h"
//
//
//xSemaphoreHandle xSemaphore1 = NULL;
//
//void vLEDFlashTask1( void *pvParameters )
//{
//portTickType xLastWakeTime;
//xLastWakeTime=xTaskGetTickCount();
  //while(1)
  //{
    //toggleLED(0);
    //vTaskDelayUntil(&xLastWakeTime,1000);
  //}
//}
//
//void vLEDFlashTask2( void *pvParameters )
//{
//portTickType xLastWakeTime;
//xLastWakeTime=xTaskGetTickCount();
  //while(1)
  //{
    //toggleLED(1);
    //vTaskDelayUntil(&xLastWakeTime,500);
  //}
//}
//
//void vSWTask3(void *pvParameters)
//{
	//while(1)
	//{
		//while(switchOn(0)==0)
		//{
			//
		//}
		//xSemaphoreGive(xSemaphore1);
	//}
//}
//
//void vSWTask4(void *pvParameters)
//{
	//while(1)
	//{
		//if (xSemaphoreTake(xSemaphore1,1000))
		//{
			//toggleLED(7);
			//vTaskDelay(100);
			//toggleLED(7);
		//}
		//else
		//{
			//toggleLED(6);
			//vTaskDelay(100);
			//toggleLED(6);	
		//}
	//}
//}
//
//int main(void)
//{
  //initLEDport();
  //initSwitchPort();
  //xTaskCreate( vLEDFlashTask1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
  //xTaskCreate( vLEDFlashTask2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );	
  //vSemaphoreCreateBinary(xSemaphore1);
  //xTaskCreate(vSWTask3,( signed char * ) "SW0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
  //xTaskCreate(vSWTask4,( signed char * ) "SW1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
  //vTaskStartScheduler();
  //while(1)
  //{}
//}
//
