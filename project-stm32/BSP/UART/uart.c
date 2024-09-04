#include "uart.h"

extern bool ESP8266_RX_DATA;


//发送一字节数据
void UART_SendByte(UART_HandleTypeDef huart,unsigned char Send_Dat)
{
	uint8_t data[1] = {Send_Dat};
	HAL_UART_Transmit(&huart, (uint8_t *)data, 1, 1000);
}

//接收一字节数据
unsigned char UART_RecByte(void)
{
	return 0;
}


char rxdata_buff_8266[1024];
int ESP8266_point = 0;
bool esp8266_RX = false;
QueueHandle_t ESP8266_Queue;
char ESP8266_BUFFER[10][1024]={"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	int i;
	if(huart->Instance == USART1)
	{
		//HAL_UART_Transmit(&huart1, (uint8_t *)rxdata_buff_pc, strlen(rxdata_buff_pc), 50);
		//HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t *)rxdata_buff_pc, sizeof(rxdata_buff_pc));
	}else if (huart->Instance == USART2)
    {
		for(i = 0; i < 10; i++)
		{
			if(!strcmp(ESP8266_BUFFER[i], "NULL"))
			{
				strcpy(ESP8266_BUFFER[i], rxdata_buff_8266);
				ESP8266_point++;
				break;
			}
		}
		if(i == 10) printf("队列已满！！");
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)rxdata_buff_8266, sizeof(rxdata_buff_8266));
    }
}



