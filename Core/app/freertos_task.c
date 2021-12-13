/*
 * freertos_task.c
 *
 *  Created on: Dec 8, 2021
 *      Author: Аня
 */
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
extern UART_HandleTypeDef huart2;
osMessageQId myQueue01Handle;

/* USER CODE END Header_StartDefaultTask */
void var10_task(void const * argument) 				//прием с юарт и передача на очередь
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  char *data[20] = {0};								// бронируем в памяти 20 байт. Изначально они по 0
  for(;;)											//бесконечный цикл
  {
	  HAL_UART_Receive(&huart2, data, 100, 50);		//прием с юарта 100-размер, 50-таймаут
	  xQueueSendToBack(myQueue01Handle, data, 0);	//очередь.
 }
}
  /* USER CODE END 5 */

void var10_task2(void const * argument) 			//читает с очереди и передает на консоль
{
	char data1[20] = {0}; 							//буфер, который принимает значения с очереди
	uint8_t x; 										//переменная x
	  for(;;)
	  {
	   x = xQueueReceive(myQueue01Handle, &data1, 1000);		//определение состояние очереди. 1 если в очереди есть элементы. 0 если пустая очередь
	   if(x == pdPASS)											//pdPASS - вернется только тогда, когда данные успешно отправлены в очередь. Если верно, то переходит дальше
	  {
	   HAL_UART_Transmit(&huart2, data1, strlen(data1), 1000);	//передача на консоль
		   osDelay(100);										//задержка
	  }
	  }
}

void var10_task_create(void)
{
	xTaskCreate(		var10_task,       /* Function that implements the task. */
	                    "anna's task",          /* Text name for the task. */
	                    128,      /* Stack size in words, not bytes. */
	                    ( void * ) 1,    /* Parameter passed into the task. */
						osPriorityNormal ,/* Priority at which the task is created. */
	                    NULL );      /* Used to pass out the created task's handle. */

	xTaskCreate(		var10_task2,       /* Function that implements the task. */
	                    "anna's task2",          /* Text name for the task. */
	                    128,      /* Stack size in words, not bytes. */
	                    ( void * ) 1,    /* Parameter passed into the task. */
						osPriorityNormal ,/* Priority at which the task is created. */
	                    NULL );      /* Used to pass out the created task's handle. */
}




