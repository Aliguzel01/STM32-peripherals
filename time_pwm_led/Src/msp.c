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

  void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
  {
	  GPIO_InitTypeDef tim2OC_ch_gpios;
	  // 1. timer2 �evre birimi i�in �evresel saati etkinle�tirin
		 __HAL_RCC_TIM2_CLK_ENABLE();
		 __HAL_RCC_GPIOA_CLK_ENABLE();
		 __HAL_RCC_GPIOB_CLK_ENABLE();

	  // 2. Gpio'lar� timer2 kanal 1,2,3 ve 4 gibi davranacak �ekilde yap�land�r�n
		 /* PA0 -> TIM2_CH1
		    PA1 -> TIM2_CH2
		    PB10 -> TIM2_CH3
		    PB2 -> TIM2_CH4 */

		 tim2OC_ch_gpios.Pin=GPIO_PIN_0 ;/* Kiran hoca PA0 a harici led ba�layarak yapt� soruyu */
		 tim2OC_ch_gpios.Mode=GPIO_MODE_AF_PP;
		 tim2OC_ch_gpios.Pull=GPIO_NOPULL;
		 tim2OC_ch_gpios.Speed=GPIO_SPEED_FREQ_LOW;
		 tim2OC_ch_gpios.Alternate=GPIO_AF1_TIM2;
		 HAL_GPIO_Init(GPIOA,&tim2OC_ch_gpios);



	  // 3. nvic ayarlar�
		 HAL_NVIC_SetPriority(TIM2_IRQn, 15 , 0 );
		 HAL_NVIC_EnableIRQ (TIM2_IRQn);

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


