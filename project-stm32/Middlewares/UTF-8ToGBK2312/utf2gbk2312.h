#ifndef UTFTOGBK2312_H
#define UTFTOGBK2312_H

#include "main.h"



// 简化的Unicode到GBK2312的映射表
typedef struct {
    uint16_t unicode;
    uint16_t gbk;
} UnicodeToGbkMap;






uint16_t unicodeToGbk(uint16_t unicode);
uint16_t utf8ToUnicode(const char *utf8Str, int *bytesProcessed);
void utf8ToGbk2312(const char *utf8Str, char *gbkStr);









#endif

