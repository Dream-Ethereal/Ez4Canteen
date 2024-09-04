#include "esp8266.h"

// 使用 Order 结构体
Order order = {0};

void ESP8266_DataParse(char *data)
{
    const char *json_start = strchr(data, '{');
    if (json_start == NULL) {
        printf("JSON not found\r\n");
        return;
    }

    // 解析 JSON
    json_error_t error;
    json_t *root = json_loads(json_start, 0, &error);
    if (!root) {
        printf("JSON parsing error: %s\n", error.text);
        return;
    }


    

    // 获取各个字段
    json_t *amount = json_object_get(root, "amount");
    json_t *goodsDetails = json_object_get(root, "goodsDetails");
    json_t *orderNo = json_object_get(root, "orderNo");
    json_t *postscript = json_object_get(root, "postscript");
    json_t *completedTime = json_object_get(root, "completedTime");
    json_t *mobile = json_object_get(root, "mobile");
    json_t *sortNum = json_object_get(root, "sortNum");
    json_t *remark = json_object_get(root, "remark");
    json_t *userName = json_object_get(root, "userName");
    json_t *targetDevice = json_object_get(root, "TargetDevice");

    // 检查字段是否为 NULL
    if (!amount || !goodsDetails || !orderNo || !postscript || !completedTime || !mobile || !sortNum || !remark || !userName || !targetDevice) {
        printf("One or more JSON fields are missing\n");
        json_decref(root);
        return;
    }

    // 临时存储 GBK2312 格式的字符串
    char gbkStr[256];

    // 将数据存储到结构体，转换为 GBK2312 格式
    strncpy(order.amount, json_string_value(amount), sizeof(order.amount) - 1);
    strncpy(order.orderNo, json_string_value(orderNo), sizeof(order.orderNo) - 1);
    strncpy(order.completedTime, json_string_value(completedTime), sizeof(order.completedTime) - 1);
    strncpy(order.mobile, json_string_value(mobile), sizeof(order.mobile) - 1);
    strncpy(order.sortNum, json_string_value(sortNum), sizeof(order.sortNum) - 1);

    // 转换字段为 GBK2312 格式
    utf8ToGbk2312(json_string_value(postscript), gbkStr);
    strncpy(order.postscript, gbkStr, sizeof(order.postscript) - 1);

    utf8ToGbk2312(json_string_value(userName), gbkStr);
    strncpy(order.userName, gbkStr, sizeof(order.userName) - 1);

    utf8ToGbk2312(json_string_value(remark), gbkStr);
    strncpy(order.remark, gbkStr, sizeof(order.remark) - 1);

    // 处理 goodsDetails 数组
    if (json_is_array(goodsDetails)) {
        size_t goodsCount = json_array_size(goodsDetails);
        order.goodsCount = (goodsCount > 30) ? 30 : goodsCount; // 限制最大数量为30
        for (size_t i = 0; i < order.goodsCount; i++) {
            json_t *goodsDetail = json_array_get(goodsDetails, i);
            json_t *goodsName = json_object_get(goodsDetail, "name");
            json_t *goodsAmount = json_object_get(goodsDetail, "amount");
            json_t *goodsNumber = json_object_get(goodsDetail, "number");
            json_t *goodsPrice = json_object_get(goodsDetail, "price");

            if (goodsName && goodsAmount && json_is_string(goodsName) && json_is_string(goodsAmount)) {
                // 转换 goodsName 为 GBK2312 格式
                utf8ToGbk2312(json_string_value(goodsName), gbkStr);
                strncpy(order.goodsDetails[i].name, gbkStr, sizeof(order.goodsDetails[i].name) - 1);
                
                strncpy(order.goodsDetails[i].amount, json_string_value(goodsAmount), sizeof(order.goodsDetails[i].amount) - 1);
                order.goodsDetails[i].number = json_integer_value(goodsNumber);
                order.goodsDetails[i].price = json_integer_value(goodsPrice);
            }
        }
    }

	//ESP8266_DataPrint(order);
    // 释放 JSON 对象
    json_decref(root);
}


void ESP8266_DataPrint(Order order)
{
    // 打印 Order 数据
    printf("Amount: %s\n", order.amount);
    for (int i = 0; i < order.goodsCount; i++) {
        printf("Goods %d Name: %s\n", i + 1, order.goodsDetails[i].name);
        printf("Goods %d Number: %d\n", i + 1, order.goodsDetails[i].number);
        printf("Goods %d Amount: %s\n", i + 1, order.goodsDetails[i].amount);
        printf("Goods %d Price: %d\n", i + 1, order.goodsDetails[i].price);
    }
    printf("Order No: %s\n", order.orderNo);
    printf("Postscript: %s\n", order.postscript);
    printf("Completed Time: %s\n", order.completedTime);
    printf("Mobile: %s\n", order.mobile);
    printf("Sort Number: %s\n", order.sortNum);
    printf("Remark: %s\n", order.remark);
    printf("User Name: %s\n", order.userName);
    printf("Target Device: %s\n", order.targetDevice);
}


