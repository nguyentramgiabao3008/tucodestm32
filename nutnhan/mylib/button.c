#include "button.h"
//------------var button---------------
__weak void press_callback(Button_Typedef *ButtonX) //nhan nut
{
	
}
__weak void fastclick(Button_Typedef *ButtonX) //nhan nha nhanh
{
	
}
__weak void slowclick(Button_Typedef *ButtonX) //nhan nha cham
{
	
}
__weak void release_callback(Button_Typedef *ButtonX) //nha nut
{
	
}

void nut(Button_Typedef *ButtonX)
{
	//---------- Loc nhieu ----------
	uint8_t sta = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if(sta != ButtonX->filter) 
	{
		ButtonX->filter = sta; 
		ButtonX->debounce = 1;
		ButtonX->time_debounce = HAL_GetTick();
	}
	
	//---------- Tin hieu da xac lap ----------
	if(ButtonX->debounce &&  (HAL_GetTick() - ButtonX->time_debounce >=15))
	{
		ButtonX->current = ButtonX->filter;
		ButtonX->debounce = 0;
	}
	
	//---------- Xu ly nhan nut nha nut ----------
	if(ButtonX->current != ButtonX->last)
	{
		if(ButtonX->current==0) // an vao
		{
			ButtonX->timeout = 1;
			press_callback(ButtonX);
			ButtonX->time_startpressing = HAL_GetTick();
		}
		else // nha ra
		{
			if (HAL_GetTick() - ButtonX->time_startpressing <= 1500)
			{
				fastclick(ButtonX);
			}
			release_callback(ButtonX);
			ButtonX->timeout = 0;
		}
		ButtonX->last = ButtonX->current;
	}
	//---------- Nhan giu ----------
	if(ButtonX->timeout && (HAL_GetTick() - ButtonX->time_startpressing >= 2500))
	{
		slowclick(ButtonX);
		ButtonX->timeout = 0;
	}
}
void button_init(Button_Typedef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}