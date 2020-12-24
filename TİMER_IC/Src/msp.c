/*
 * msp.c
 *
 *  Created on: 1 Eki 2020
 *      Author: HP
 */

#include "main.h"

  void HAL_MspInit(void)
{
   // Burada düþük seviyeli iþlemciye özgü baþlangýçlar yapacaðýz.
	  // 1. Arm cortex mx iþlemcisinin öncelikli gruplamasýný ayarlayýn
	  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  // 2. Arm cortex mx iþlemcisinin gerekli sistem istisnalarýný etkinleþtirin
	  SCB->SHCSR |= 0X7 << 16; //usg fault ,memoryfault  and bus fault system exceptions.

	  // 3. sistem istisnalarý için önceliði yapýlandýrýn
	  HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	  HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	  HAL_NVIC_SetPriority(UsageFault_IRQn ,0,0);

}

 void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
 {
	 GPIO_InitTypeDef  tim2ch1_gpio;

    //TIM2 için saati etkinleþtir
	 __HAL_RCC_TIM2_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	 //timer2 kanal 1 yapýsýný gpýo yapýlantýrmasý yapmamýz lazým yani alternatif fonksiyon yapýsý */
	tim2ch1_gpio.Pin=GPIO_PIN_0;
	tim2ch1_gpio.Mode=GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate=GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA,&tim2ch1_gpio);

	//NVIC ayarlarý
	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
 }



 void  HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htimer)
 {

 	// 1. TIM6 çevre birimi için saati etkinleþtirin
 	__HAL_RCC_TIM6_CLK_ENABLE ();

 	// 2. TIM6'nýn IRQ'sunu etkinleþtirin
 	HAL_NVIC_EnableIRQ (TIM6_DAC_IRQn);

 	// 3. TIM6_DAC_IRQn için önceliði ayarlayýn
 	HAL_NVIC_SetPriority (TIM6_DAC_IRQn, 15 , 0 );

 }



 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
  {
 	 GPIO_InitTypeDef gpio_uart;
 	 // burada düþük seviyeli inits yapacaðýz. USART2 çevre birimi

 	 // 1. USART2 çevre birimi ve GPIOA çevre birimi için saati etkinleþtirin
 	 __HAL_RCC_USART2_CLK_ENABLE();
 	 __HAL_RCC_GPIOA_CLK_ENABLE();
 	 // 2. Pin muxing yapýlandýrmalarýný yapýn
 	 gpio_uart.Pin=GPIO_PIN_2;
 	 gpio_uart.Mode=GPIO_MODE_AF_PP;
 	 gpio_uart.Pull=GPIO_PULLUP;
 	 gpio_uart.Alternate=GPIO_AF7_USART2;//UART2_TX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);

 	 gpio_uart.Pin=GPIO_PIN_3;//UART2_RX
 	 HAL_GPIO_Init(GPIOA,&gpio_uart);
 	 // 3. IRQ'yu etkinleþtirin ve önceliði ayarlayýn (NVIC ayarlarý)
 	 HAL_NVIC_EnableIRQ (USART2_IRQn);
 	 HAL_NVIC_SetPriority (USART2_IRQn, 15 , 0 );

  }


