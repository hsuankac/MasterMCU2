/*
 * msp.c
 *
 *  Created on: Jul 27, 2022
 *      Author: hsuankai.chang
 */
#include "main.h"

void HAL_MspInit(void)
{
	// Here we will do low level processor specific inits
	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= (0x7 << 16); //usage fault, memory fault and bus fault system exception

	// 3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{
	// 1. Enable the clock for the TIM6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	// 2. Enable IRQ of TIM6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	// 3. Set up the priority for this IRQ number
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}
