/**
 ****************************************************************************************************
 * @file        usart.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.1
 * @date        2023-06-05
 * @brief       ���ڳ�ʼ������(һ���Ǵ���1)��֧��printf
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211103
 * ��һ�η���
 * V1.1 20230605
 * ɾ��USART_UX_IRQHandler()�����ĳ�ʱ�������޸�HAL_UART_RxCpltCallback()
 *
 ****************************************************************************************************
 */

#include "sys.h"
#include "usart.h"
#include "uart.h"
#include "stdio.h"

/* ���ʹ��os,����������ͷ�ļ�����. */
#if SYS_SUPPORT_OS
#include "os.h" /* os ʹ�� */
#endif

/******************************************************************************************/


/******************************************************************************************/


