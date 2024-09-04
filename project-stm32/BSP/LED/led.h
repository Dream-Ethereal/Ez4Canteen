#ifndef LED_H
#define LED_H

#include "main.h"

enum
{
	LED_OFF,
	LED_ON
};


void LED_Control(GPIO_TypeDef * GPIO_Base, uint16_t GPIO_Pin, int LED_Status);

#endif


