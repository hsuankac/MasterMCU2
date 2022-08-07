/*
 * it.c
 *
 *  Created on: Jul 27, 2022
 *      Author: hsuankai.chang
 */

#include "main.h"


void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

