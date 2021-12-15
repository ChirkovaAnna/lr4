/*
 * 10var.h
 *
 *  Created on: Dec 8, 2021
 */

#ifndef INC_10VAR_H_
#define INC_10VAR_H_



#endif /* INC_10VAR_H_ */

struct lock {
uint8_t i;
uint8_t a;
uint8_t pin_c;
uint16_t count1;
uint16_t count2;
uint8_t x;
};

struct lock ex;         //структура данных для переменных прерывания, и цикла вкл и выкл светодиодов
struct lock tim;        //структура данных для переменных таймера
uint8_t pin = 131;
