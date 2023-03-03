#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"
typedef struct
{
	uint8_t current;
	uint8_t last;
	uint8_t filter; // trang thai nhieu
	uint8_t debounce; //phat hien co su thay doi trang thai (nhieu)
	uint32_t time_debounce; // luu lai thoi gian thay doi trang thai
	uint32_t time_startpressing; //thoi gian bat dau nhan nut
	uint32_t timeout; //thoi gian nhan giu lau
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typedef;
void nut(Button_Typedef *ButtonX);
void button_init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif
