/*
 * msp.c
 *
 *  Created on: 1 Eki 2020
 *      Author: HP
 */

#include "main.h"

  void HAL_MspInit(void)
{
   // Burada d���k seviyeli i�lemciye �zg� ba�lang��lar yapaca��z.
	  // 1. Arm cortex mx i�lemcisinin �ncelikli gruplamas�n� ayarlay�n
	  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  // 2. Arm cortex mx i�lemcisinin gerekli sistem istisnalar�n� etkinle�tirin
	  SCB->SHCSR |= 0X7 << 16; //usg fault ,memoryfault  and bus fault system exceptions.

	  // 3. sistem istisnalar� i�in �nceli�i yap�land�r�n
	  HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	  HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	  HAL_NVIC_SetPriority(UsageFault_IRQn ,0,0);

}

 void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
 {
	 GPIO_InitTypeDef  tim2ch1_gpio;

    //TIM2 i�in saati etkinle�tir
	 __HAL_RCC_TIM2_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	 //timer2 kanal 1 yap�s�n� gp�o yap�lant�rmas� yapmam�z laz�m yani alternatif fonksiyon yap�s� */
	tim2ch1_gpio.Pin=GPIO_PIN_0;
	tim2ch1_gpio.Mode=GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate=GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA,&tim2ch1_gpio);

	//NVIC ayarlar�
	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
 }



 void  HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htimer)
 {

 	// 1. TIM6 �evre birimi i�in saati etkinle�tirin
 	__HAL_RCC_TIM6_CLK_ENABLE ();

 	// 2. TIM6'n�n IRQ'sunu etkinle�tirin
 	HAL_NVIC_EnableIRQ (TIM6_DAC_IRQn);

 	// 3. TIM6_DAC_IRQn i�in �nceli�i ayarlay�n
 	HAL_NVIC_SetPriority (TIM6_DAC_IRQn, 15 , 0 );

 }



 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
  {
 	 GPIO_InitTypeDef gpio_uart;
 	 // burada d���k seviyeli inits yapaca��z. USART2 �evre birimi

 	 // 1. USART2 �evre birimi ve GPIOA �evre birimi i�in saati etkinle�tirin
 	 __HAL_RCC_USART2_CLK_ENABLE();
 	 __HAL_RCC_GPIOA_CLK_ENABLE();
 	 // 2. Pin muxing yap�land�rmalar�n� yap�n
 	 gpio_uart.Pin=GPIO_PIN_2;
 	 gpio_uart.Mode=GPIO_MODE_AF_PP;
 	 gpio_uart.Pull=GPIO_PULLUP;
 	 gpio_uart.Alternate=GPIO_AF7_USART2;//UART2_TX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);

 	 gpio_uart.Pin=GPIO_PIN_3;//UART2_RX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);
 	 // 3. IRQ'yu etkinle�tirin ve �nceli�i ayarlay�n (NVIC ayarlar�)
 	 HAL_NVIC_EnableIRQ (USART2_IRQn);
 	 HAL_NVIC_SetPriority (USART2_IRQn, 15 , 0 );

  }


