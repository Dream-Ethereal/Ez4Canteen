#ifndef UART_H
#define UART_H

#include "main.h"
 #include "FreeRTOS.h"
#include "queue.h"
#include "cmsis_os2.h"

#include "utf2gbk2312.h"
#include "esp8266.h"



//����һ�ֽ�����
void UART_SendByte(UART_HandleTypeDef huart,unsigned char Send_Dat);


//����һ�ֽ�����
unsigned char UART_RecByte(void);



#endif

