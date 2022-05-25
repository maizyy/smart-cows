/*
 * wire.c
 *
 *  Created on: May 25, 2022
 *      Author: Jogn
 */

#include <wire.h>
#include "gpio.h"
#include "tim.h"

/*
 * private functions
 */

static void delay_us(uint32_t us)
{
  __HAL_TIM_SET_COUNTER(&htim6, 0);

  while (__HAL_TIM_GET_COUNTER(&htim6) < us) {}
}

static int read_bit(void)
{
  int rc;
  __set_BASEPRI(1 << 4);
  HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_RESET);
  delay_us(6);
  HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_SET);
  delay_us(9);
  rc = HAL_GPIO_ReadPin(DS_GPIO_Port, DS_Pin);
  delay_us(55);
  __set_BASEPRI(1 << 4);
  return rc;
}

static void write_bit(int value)
{
	__set_BASEPRI(1 << 4);
  if (value) {
    HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_RESET);
    delay_us(6);
    HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_SET);
    delay_us(64);
  } else {
    HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_RESET);
    delay_us(60);
    HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_SET);
    delay_us(10);
  }
  __set_BASEPRI(0);
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
  return HAL_TIM_Base_Start(&htim6);
}


HAL_StatusTypeDef wire_reset(void)
{
  int rc;

  HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_RESET);
  delay_us(480);
  HAL_GPIO_WritePin(DS_GPIO_Port, DS_Pin, GPIO_PIN_SET);
  delay_us(70);
  rc = HAL_GPIO_ReadPin(DS_GPIO_Port, DS_Pin);
  delay_us(410);

  if (rc == 0)
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
