#ifndef __MQTT_H__
#define __MQTT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"



// 十路保持寄存器  可读可写的2字节寄存器
extern uint16_t REG_HOLD_BUF[];

extern __IO uint8_t MQTT_UPLoad_Flag ;  // 数据上传服务器标志位 , 每隔5秒标志位置1 
extern __IO uint8_t MQTT_Download_Flag ;  // 对接收到的json数据进行解析的标志位
uint8_t *Get_CPUID(void);
uint8_t MQTT_WIFI_Connect_Server(void);
uint8_t MQTT_SendData(void);
uint8_t MQTT_Parse_JsonData(uint8_t *json);

#ifdef __cplusplus
}
#endif
#endif /*__MQTT_H__ */

