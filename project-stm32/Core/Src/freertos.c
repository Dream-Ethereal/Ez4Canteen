/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "DP_Print_inc.h"
#include "uart.h"
#include "esp8266.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern char rxdata_buff_8266[1024];
extern int ESP8266_point;
extern bool esp8266_RX;
extern Order order;
extern char ESP8266_BUFFER[10][1024];

bool ESP8266_RX_DATA = false;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_PrintCtrl */
osThreadId_t Task_PrintCtrlHandle;
const osThreadAttr_t Task_PrintCtrl_attributes = {
  .name = "Task_PrintCtrl",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_UsartRX */
osThreadId_t Task_UsartRXHandle;
const osThreadAttr_t Task_UsartRX_attributes = {
  .name = "Task_UsartRX",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Func_PrintCtrl(void *argument);
void Func_UsartRX(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  //HAL_UARTEx_ReceiveToIdle_IT(&huart1, (uint8_t *)rxdata_buff_pc, sizeof(rxdata_buff_pc));
  //HAL_UART_Receive_IT(&huart1, &rxdata_pc, 1);
  
  HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *)rxdata_buff_8266, sizeof(rxdata_buff_8266));
  //HAL_UART_Receive_IT(&huart2, &rxdata_8266, 1);
  EM5820_init();
  
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task_PrintCtrl */
  Task_PrintCtrlHandle = osThreadNew(Func_PrintCtrl, NULL, &Task_PrintCtrl_attributes);

  /* creation of Task_UsartRX */
  Task_UsartRXHandle = osThreadNew(Func_UsartRX, NULL, &Task_UsartRX_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
//  	LED_Control(LED0_GPIO_Port, LED0_Pin, LED_ON);
//    vTaskDelay(20);
//    LED_Control(LED0_GPIO_Port, LED0_Pin, LED_OFF);
//    vTaskDelay(20);
		//printf("runing!\r\n");
		vTaskDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Func_PrintCtrl */
/**
* @brief Function implementing the Task_PrintCtrl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Func_PrintCtrl */
void Func_PrintCtrl(void *argument)
{
  /* USER CODE BEGIN Func_PrintCtrl */
  /* Infinite loop */
  uint32_t ret = 0;
  for(;;)
  {
	
	ret = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

	if(ret != 0)
	{
		taskENTER_CRITICAL();
		{
			EM5820_printData(order);
			ESP8266_point--;
		}
		taskEXIT_CRITICAL();
	}
   vTaskDelay(10);
  }
  /* USER CODE END Func_PrintCtrl */
}

/* USER CODE BEGIN Header_Func_UsartRX */
/**
* @brief Function implementing the Task_UsartRX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Func_UsartRX */
void Func_UsartRX(void *argument)
{
  /* USER CODE BEGIN Func_UsartRX */
  /* Infinite loop */
  for(;;)
  {
  	if(ESP8266_point != 0)
  	{
  		for(int i = 0; i < 10; i++)
  		{
			if(!strcmp(ESP8266_BUFFER[i], "NULL"))
				continue;
			taskENTER_CRITICAL();
			{
				ESP8266_DataParse(ESP8266_BUFFER[i]);
				xTaskNotifyGive(xTaskGetHandle(Task_PrintCtrl_attributes.name));
			}
			taskEXIT_CRITICAL();
			
		}
  	}
    osDelay(10);
  }
  /* USER CODE END Func_UsartRX */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

