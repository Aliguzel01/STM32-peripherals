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



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	//TIM6 cevre birimi için saati etkinleþtir
	__HAL_RCC_TIM6_CLK_ENABLE();

	//	TIM6 IRQ yu etkinleþtir.
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//TIM6_DAC_IRQn ÝÇÝN ÖNCELÝÐÝ YAPILANDIR.
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);

}
