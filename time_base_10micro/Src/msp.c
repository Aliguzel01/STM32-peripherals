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



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	//TIM6 cevre birimi i�in saati etkinle�tir
	__HAL_RCC_TIM6_CLK_ENABLE();

	//	TIM6 IRQ yu etkinle�tir.
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//TIM6_DAC_IRQn ���N �NCEL��� YAPILANDIR.
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);

}
