/*
 * freertos_task.h
 *
 *  Created on: Dec 8, 2021
 *      Author: Аня
 */

#ifndef APP_FREERTOS_TASK_H_
#define APP_FREERTOS_TASK_H_

void var10_task(void const * argument);
void var10_task2(void const * argument);
void var10_task_create(QueueHandle_t  queue);

osMessageQId myQueue01Handle;
//osMessageQDef(myQueue01, 4, *char);//4- сколько ячеек

#endif /* APP_FREERTOS_TASK_H_ */
