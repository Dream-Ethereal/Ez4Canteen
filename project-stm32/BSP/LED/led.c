#include "led.h"

void LED_Control(GPIO_TypeDef * GPIO_Base, uint16_t GPIO_Pin, int LED_Status)
{
	HAL_GPIO_WritePin(GPIO_Base, GPIO_Pin, LED_Status == LED_ON ? GPIO_PIN_RESET : GPIO_PIN_SET);
}



