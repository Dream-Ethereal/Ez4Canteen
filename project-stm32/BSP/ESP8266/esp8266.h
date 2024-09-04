#ifndef __ESP8266_H__
#define __ESP8266_H__


#include "main.h"
#include "utf2gbk2312.h"

// Order 结构体的定义
typedef struct {
    char amount[32];
    char orderNo[32];
    char postscript[128];
    char completedTime[32];
    char mobile[16];
    char sortNum[16];
    char remark[128];
    char userName[32];
    char targetDevice[32];
    int goodsCount;
    struct {
        char name[64];
        char amount[32];
        int number;
        int price;
    } goodsDetails[30]; // 假设最大数量为30
} Order;

extern void EM5820_printData(Order order);

void ESP8266_DataParse(char *data);
void ESP8266_DataPrint(Order order);


#endif
