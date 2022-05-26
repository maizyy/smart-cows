/*
 * wire.c
 *
 *  Created on: May 25, 2022
 *      Author: Jogn
 */

#include <wire.h>
#include "gpio.h"
#include "tim.h"
#include "usart.h"

/*
 * private functions
 */


static void set_baudrate(uint32_t baudrate)
{
  huart4.Instance = UART4;
  huart4.Init.BaudRate = baudrate;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
  huart4.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
	Error_Handler();
  }
}

static void delay_us(uint32_t us)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);

  while (__HAL_TIM_GET_COUNTER(&htim1) < us) {
  }
}

static void write_bit(int value)
{
  if (value) {
      uint8_t data_out = 0xff;
    HAL_UART_Transmit(&huart4, &data_out, 1, HAL_MAX_DELAY);
  } else {
      uint8_t data_out = 0x0;
    HAL_UART_Transmit(&huart4, &data_out, 1, HAL_MAX_DELAY);
  }
}

static int read_bit(void)
{
  uint8_t data_out = 0xFF;
  uint8_t data_in = 0;
  HAL_UART_Transmit(&huart4, &data_out, 1, HAL_MAX_DELAY);
  HAL_UART_Receive(&huart4, &data_in, 1, HAL_MAX_DELAY);

  return data_in & 0x01;
}

static uint8_t byte_crc(uint8_t crc, uint8_t byte)
{
  int i;
  for (i = 0; i < 8; i++) {
    uint8_t b = crc ^ byte;
    crc >>= 1;
    if (b & 0x01)
      crc ^= 0x8c;
    byte >>= 1;
  }
  return crc;
}

/*
 * public functions
 */

HAL_StatusTypeDef wire_init(void)
{
  return HAL_TIM_Base_Start(&htim1);
}

HAL_StatusTypeDef wire_reset(void)
{
  uint8_t data_out = 0xF0;
  uint8_t data_in = 0;

  set_baudrate(9600);
  HAL_UART_Transmit(&huart4, &data_out, 1, HAL_MAX_DELAY);
  HAL_UART_Receive(&huart4, &data_in, 1, HAL_MAX_DELAY);
  set_baudrate(115200);

  if (data_in != 0xF0)
    return HAL_OK;
  else
    return HAL_ERROR;
}

uint8_t wire_read(void)
{
  uint8_t value = 0;
  int i;
  for (i = 0; i < 8; i++) {
    value >>= 1;
    if (read_bit())
      value |= 0x80;
  }
  return value;
}


void wire_write(uint8_t byte)
{
  int i;
  for (i = 0; i < 8; i++) {
    write_bit(byte & 0x01);
    byte >>= 1;
  }
}


uint8_t wire_crc(const uint8_t* data, int len)
{
  int i;
    uint8_t crc = 0;

    for (i = 0; i < len; i++)
      crc = byte_crc(crc, data[i]);

    return crc;
}
