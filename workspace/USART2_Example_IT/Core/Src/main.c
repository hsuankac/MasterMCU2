/*
 * main.c
 *
 *  Created on: Jul 27, 2022
 *      Author: hsuankai.chang
 */

#include <string.h>
#include "main.h"

#define TRUE 				1
#define FALSE 				0

void SystemClockConfig();
void UART2_Init();
void Error_handler();
uint8_t convert_to_capital(uint8_t data);

UART_HandleTypeDef huart2;

char *user_data = "The application is running\r\n";
uint8_t data_buffer[100];
uint8_t rcvd_data;
uint32_t count = 0;
uint8_t reception_complete = FALSE;

int main(void) {
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t len_of_data = strlen(user_data);

	HAL_UART_Transmit(&huart2, (uint8_t*)user_data, len_of_data, HAL_MAX_DELAY);

	while(reception_complete != TRUE)
		HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);

	while(1);

	return 0;
}

uint8_t convert_to_capital(uint8_t data)
{
	if(data >= 'a' && data <= 'z')
	{
		data = data - ('a' - 'A');
	}
	return data;
}

void SystemClockConfig()
{

}

void UART2_Init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		//There is a problem
		Error_handler();
	}
}

void Error_handler()
{
	while(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (rcvd_data == '\r')
	{
		reception_complete = TRUE;
		data_buffer[count++] = '\r';
		HAL_UART_Transmit(huart, data_buffer, count, HAL_MAX_DELAY);
	}
	else
	{
		data_buffer[count++] = rcvd_data;
	}
}
