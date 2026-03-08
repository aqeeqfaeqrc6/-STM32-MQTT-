#include "modbus.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "mb.h"
#include "gpio.h"
#include "aht20.h"
#include "ina226.h"
#include "adc.h"

uint8_t SlaveAddress = 1; // 设备的默认地址为1 
uint8_t Modify_SlaveAddress_Flag = 0; // 修改从机地址的标志位
uint8_t Timeout_Flag = 0; // 500ms 定时时间到的标志位,刷新各种传感


/**
 * @brief  从EEPROM中读取从机地址
 * @param   addr   :  EEPROM的存储地址
 *          pdata  :  读回来的数据
 * @retval SET RESET
 */
uint8_t ReadSlaveAddress(uint8_t addr,uint8_t *pdata)
{
		HAL_I2C_Mem_Read(&hi2c1, AT24C02_ADDRESS_READ,addr,I2C_MEMADD_SIZE_8BIT,pdata,1,1000); 
		if(*pdata == 0 )  // 如果读出的数据为0， 0不能作为从机的地址， 我们手动+1
		{
				*pdata = 1;
		}
		return SET;
}

/**
 * @brief  写设备的从机地址到EEPROM
 * @param   addr   :  EEPROM的存储地址
 *          pdata  :  要写入的数据
 * @retval  SET RESET
 */
uint8_t WriteSlaveAddress(uint8_t addr,uint8_t data)
{
		HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDRESS_WRITE,addr,I2C_MEMADD_SIZE_8BIT,&data,1, 1000); 
		return SET;
}

void Modbus_Init(void)
{
		// 程序执行后， 会自动从EEPROM中读取设备的地址
		ReadSlaveAddress(0,&SlaveAddress); 
		printf("SlaveAddress:%x\n",SlaveAddress);
	  eMBInit(MB_RTU, SlaveAddress, 0, 115200, MB_PAR_NONE);		// 初始化modbus为RTU方式，波特率115200，无校验
		eMBEnable();

}

void Modbus_Parse(void)
{
		if(Timeout_Flag) // 500ms 触发一次执行 
		{
				Timeout_Flag = 0 ; 
			
				// 读取温湿度 
				AHT20_Read();
			
				// 电流传感器
				INA226_Read();
			
				// 电位器和CPU
				ADC_VR_CPU_Read();
			
				
		}
		if(Modify_SlaveAddress_Flag) //修改从机地址
		{
				Modify_SlaveAddress_Flag=0;
				//printf("SlaveAddress:%d\n",REG_HOLD_BUF[9]);
				WriteSlaveAddress(0,REG_HOLD_BUF[9]);
				HAL_Delay(10);
				eMBDisable();
				eMBClose();
				Modbus_Init();
		}
		// 解析REG_HOLD_BUF[0]中的数据, 控制板子的设备
		if(REG_HOLD_BUF[0] & LED1_CMD )
		{
				LED_Control(LED1,ON);
		}
		else 
		{
				LED_Control(LED1,OFF);
		}
		
		// 解析REG_HOLD_BUF[0]中的数据, 控制板子的设备
		if(REG_HOLD_BUF[0] & LED2_CMD )
		{
				LED_Control(LED2,ON);
		}
		else 
		{
				LED_Control(LED2,OFF);
		}
		
		// 解析REG_HOLD_BUF[0]中的数据, 控制板子的设备
		if(REG_HOLD_BUF[0] & BEEP_CMD )
		{
				BEEP_Control(ON);
		}
		else 
		{
				BEEP_Control(OFF);
		}
		
		// 解析REG_HOLD_BUF[0]中的数据, 控制板子的设备
		if(REG_HOLD_BUF[0] & RELAY_CMD )
		{
				RELAY_Control(ON);
		}
		else 
		{
				RELAY_Control(OFF);
		}
}








