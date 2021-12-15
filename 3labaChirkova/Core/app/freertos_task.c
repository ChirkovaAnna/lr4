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
void var10_task(void * argument) 											//прием с юарт и передача на очередь
{
	QueueHandle_t tasks_queue = (QueueHandle_t*)argument;
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  char data[20] = {1,2,3,4,5,6,7,8,9,10};								// бронируем в памяти 20 байт. Изначально они по 0
  char *pdata = data;
  for(;;)																//бесконечный цикл
  {
	 		//прием с юарта 100-размер, 50-таймаут
	  if (HAL_OK ==  HAL_UART_Receive(&huart2, data, 100, 50))
	  {  xQueueSend(tasks_queue, &pdata, 100);	//очередь.
	  }
	  }
 }
}
  /* USER CODE END 5 */

void var10_task2(void * argument) 			//читает с очереди и передает на консоль
{
	QueueHandle_t tasks_queue = (QueueHandle_t*)argument;

	char *data1; 							//буфер, который принимает значения с очереди
	uint8_t x; 										//переменная x?
	  for(;;)
	  {
		  data1 = NULL;
	   if(xQueueReceive(tasks_queue, &data1, portMAX_DELAY) == pdTRUE)											//pdPASS - вернется только тогда, когда данные успешно отправлены в очередь. Если верно, то переходит дальше
	  {
		   HAL_UART_Transmit(&huart2, data1, strlen(data1), 1000);	//передача на консоль
		   osDelay(100);										//задержка
	  }
	  }
}

void var10_task_create(QueueHandle_t  queue)
{
	xTaskCreate(		var10_task,       /* Function that implements the task. */
	                    "anna's task",          /* Text name for the task. */
	                    128,      /* Stack size in words, not bytes. */
						queue,    /* Parameter passed into the task. */
						osPriorityNormal ,/* Priority at which the task is created. */
						NULL );      /* Used to pass out the created task's handle. */

	xTaskCreate(		var10_task2,       /* Function that implements the task. */
	                    "anna's task2",          /* Text name for the task. */
	                    128,      /* Stack size in words, not bytes. */
						queue,    /* Parameter passed into the task. */
						osPriorityNormal ,/* Priority at which the task is created. */
						NULL );      /* Used to pass out the created task's handle. */
}




