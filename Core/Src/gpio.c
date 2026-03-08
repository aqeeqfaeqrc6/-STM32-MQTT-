/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
uint8_t Key_Value = 0 ;  // 按键的值, 全局变量
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */




/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RELAY_Pin|RS485_WR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FLASH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(FLASH_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = RELAY_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RS485_WR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(RS485_WR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = KEY_OK_Pin|KEY_UP_Pin|KEY_DOWN_Pin|KEY_RIGHT_Pin
                          |KEY_LEFT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_ESC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_ESC_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
/**
 * @brief  控制LED1 LED2 亮灭的函数
 * @note   详细细节描述 , ON 控制LED亮 , OFF 控制LED灭
 * @param   device :  可以是LED1,LED2 , 两个宏, 在gpio.h 中定义
 *          cmd  :  用控制 LED亮灭的指令
 *              ON : LED 亮
 *              OFF :  LED 灭
 * @retval None
 */

void LED_Control(uint8_t device, uint8_t cmd)
{
	if (device == LED1)
	{
		if (cmd == ON)
		{
			HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET); // 设置引脚输出低电平 ， LED1亮
		}
		else if (cmd == OFF)
		{
			HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET); // 设置引脚输出高电平 ， LED1灭
		}
	}
	else if (device == LED2)
	{
		if (cmd == ON)
		{
			HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET); // 设置引脚输出低电平 ， LED2亮
		}
		else if (cmd == OFF)
		{
			HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET); // 设置引脚输出高电平 ， LED2灭
		}
	}
}

void LED_Test(void)
{
	LED_Control(LED1, ON);
	LED_Control(LED2, OFF);
	HAL_Delay(500);
	LED_Control(LED1, OFF);
	LED_Control(LED2, ON);
	HAL_Delay(500);
}

/**
 * @brief  控制BEEP 亮灭的函数
 * @note   详细细节描述 , ON 控制BEEP工作 , OFF 控制不工作
 *          cmd  :  用控制 BEEP的指令
 *            ON : BEEP 工作
 *           OFF :  BEEP 不工作
 * @retval None
 */

void BEEP_Control(uint8_t cmd)
{

	if (cmd == ON)
	{
		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET); // 设置引脚输出高电平 , 蜂鸣器工作
	}
	else if (cmd == OFF)
	{

		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET); // 设置引脚输出低电平 , 蜂鸣器不工作
	}
}

void BEEP_Test(void)
{
	BEEP_Control(ON);
	HAL_Delay(200);
	BEEP_Control(OFF);
	HAL_Delay(800);
}

/**
 * @brief  控制继电器的函数
 * @note   详细细节描述 , ON 控制继电器工作 , OFF 控制不工作
 *          cmd  :  控制 继电器的指令
 *            ON : 继电器 工作
 *           OFF :  继电器 不工作
 * @retval None
 */

void RELAY_Control(uint8_t cmd)
{

	if (cmd == ON)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET); // 设置引脚输出高电平 , 继电器工作
	}
	else if (cmd == OFF)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET); // 设置引脚输出低电平 , 继电器不工作
	}
}

void RELAY_Test(void)
{
	RELAY_Control(ON);
	HAL_Delay(1000);
	RELAY_Control(OFF);
	HAL_Delay(1000);
}

/**
 * @brief  获取按键的值
 * @note   详细细节描述 , 根据按下的按键,返回对应的键值
 * @retval 按下的键值 ， 定义在gpio.h 当中
 */
uint8_t KEY_Scan(void)
{
	uint8_t keyval = 0; // 按键的键值
	// UP 按键被按下后,引脚 变为低电平
	if (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_UP;
	}

	// DOWN 按键被按下后,引脚 变为低电平
	else if (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_DOWN;
	}
	// LEFT 按键被按下后,引脚 变为低电平
	else if (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_LEFT;
	}
	// RIGHT 按键被按下后,引脚 变为低电平
	else if (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_RIGHT;
	}
	// OK 按键被按下后,引脚 变为低电平
	else if (HAL_GPIO_ReadPin(KEY_OK_GPIO_Port, KEY_OK_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_OK;
	}
	// ESC 按键被按下后,引脚 变为低电平
	else if (HAL_GPIO_ReadPin(KEY_ESC_GPIO_Port, KEY_ESC_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_ESC;
	}

	return keyval;
}

void KEY_Test(void)
{
	uint8_t keyval = KEY_Scan();
	if (keyval > 0) // 有按键被按下
	{
		if (keyval == KEY_UP)
		{
			LED_Control(LED1, ON);
		}
		else if (keyval == KEY_DOWN)
		{
			LED_Control(LED1, OFF);
		}
		else if (keyval == KEY_LEFT)
		{
			LED_Control(LED2, ON);
		}
		else if (keyval == KEY_RIGHT)
		{
			LED_Control(LED2, OFF);
		}
		else if (keyval == KEY_OK)
		{
			BEEP_Control(ON);
		}
		else if (keyval == KEY_ESC)
		{
			BEEP_Control(OFF);
		}
	}
}

/* USER CODE END 2 */
