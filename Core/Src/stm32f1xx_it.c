/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include <stdio.h>
#include "usart.h"
#include "fifo.h"
#include "wifi4g.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */

  /* USER CODE END DMA1_Channel3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_LEFT_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_ESC_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */
	USER_UART_IRQHandler(&huart3);
  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_OK_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_UP_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_DOWN_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_RIGHT_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	static uint32_t old_uwTick = 0 ; // 只能被初始化1次
	if( (uwTick - old_uwTick ) < 200 ) 	return ;
	// uwTick每隔1ms 值自动加1 , 系统嘀嗒定时器中断完成的操作
	// 第1次进入HAL_GPIO_EXTI_Callback, if( (uwTick - old_uwTick ) < 200 ), 条件为假的,if不执行
	// 第2次进入HAL_GPIO_EXTI_Callback, 如果时间差小于200ms, 条件不满足,会直接返回
	// 等时间差大于200ms时, if( (uwTick - old_uwTick ) < 200 )不成立,可以再次触发中断
	old_uwTick = uwTick ;  
	
		
	
	// 表示UP按键被按下后触发中断
	if(GPIO_Pin == KEY_UP_Pin)  // PB13 按键UP 
	{
			// LED1 亮 
			//LED_Control(LED1,ON);
			Key_Value = KEY_UP;
			//printf("Key Up Pressed\n");
	}
	// 表示DOWN按键被按下后触发中断
	else if(GPIO_Pin == KEY_DOWN_Pin)  // PB14 按键DOWN
	{
			// LED1 灭 
			//LED_Control(LED1,OFF);
			Key_Value = KEY_DOWN;
			//printf("Key Down Pressed\n");
	}
	// 表示LEFT按键被按下后触发中断
	else if(GPIO_Pin == KEY_LEFT_Pin)  // PB5 按键LEFT
	{
			// LED2 亮 
			//LED_Control(LED2,ON);
			Key_Value = KEY_LEFT;
			//printf("Key Left Pressed\n");
	}
	// 表示RIGHT按键被按下后触发中断
	else if(GPIO_Pin == KEY_RIGHT_Pin)  // PB15 按键RIGHT
	{
			// LED2 灭 
			//LED_Control(LED2,OFF);
			Key_Value = KEY_RIGHT;
			//printf("Key Right Pressed\n");
	}
		// 表示OK按键被按下后触发中断
	else if(GPIO_Pin == KEY_OK_Pin)  // PB12 按键OK
	{
			// BEEP 工作 
			//BEEP_Control(ON);
			Key_Value = KEY_OK;
			//printf("Key OK Pressed\n");
	}
	// 表示ESC按键被按下后触发中断
	else if(GPIO_Pin == KEY_ESC_Pin)  // PA8 按键ESC
	{
			// BEEP 不工作 
			//BEEP_Control(OFF);
			Key_Value = KEY_ESC;
			//printf("Key ESC Pressed\n");
		
	}

}


// DMA 接收到一半的中断 
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
		if(huart->Instance == USART3)
		{
			uint8_t Length  =  DMA_BUF_SIZE/2 - RX3_Offset ; 
			if(Enqueue_Bytes(&QUART3,RX3_Buf+RX3_Offset,Length) <0)
			{
					printf("FIFO Full\n");
			}
			RX3_Offset += Length; 		
		}
}

// DMA传输完成中断   , 就是接收满了的时候 触发中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		if(huart->Instance == USART3)
    {
        uint8_t Length  =  DMA_BUF_SIZE - RX3_Offset ; 
				if(Enqueue_Bytes(&QUART3,RX3_Buf+RX3_Offset,Length) <0)
				{
						printf("FIFO Full\n");
				}	
        RX3_Offset = 0 ; // 清空dma 位置基准值
    }
}

// 用户自定义的函数 ， 处理串口空闲中断
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
		if(huart->Instance == USART3)                                 
    {
				/* UART frame error interrupt occurred --------------------------------------*/
				if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) ||  
						__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) )== SET )   //判断是否是帧错误或者噪音中断
				{
					__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
					__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);

					huart->ErrorCode &= HAL_UART_ERROR_FE; // 清除错误标志位
					huart->ErrorCode &= HAL_UART_ERROR_NE; // 清除错误标志位
					HAL_UART_DMAStop(huart); // 关闭DMA
					HAL_UART_Receive_DMA(huart,RX3_Buf,DMA_BUF_SIZE);// 重新启动DMA
				}
        if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET )   //判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);    //清除空闲中断标志（否则会一直不断进入中断）

            //计算接收到的数据长度 : BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx)
            uint8_t Length  =  DMA_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx) - RX3_Offset;

						// 这里启动TIM4 开始计时， 用来检测接收到数据包后，多久要处理 ，设立使用10ms即可
						HAL_TIM_Base_Start_IT(&htim4); // 使能定时器4中断 
						if(Enqueue_Bytes(&QUART3,RX3_Buf+RX3_Offset,Length) <0){
								printf("FIFO is Full\n");
						}	
            RX3_Offset += Length; 		   
        }
    }
}

/* USER CODE END 1 */
