/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <battery_3_7.h>
#include <GPS.h>
#include <ds18b20.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define LINE_MAX_LENGTH	60
#define JOIN_ALREADY "+JOIN: Joined already"
#define NETWORK_JOINED "+JOIN: Network joined"
#define JOIN_DONE "+JOIN: Done"
#define MSG_DONE "+MSG: Done"

// DS18B20 komendy
#define READ_ROM 0x33

#define TIME_SLEEP 60 // [s]
#define MAX_ATTEMPTS_CONNECTION 5

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

bool connectedToNetwork = false;
bool networkStatusReceived = false;
bool configStatusReceived = false;
bool messageDoneStatusReceived = false;

uint8_t rxData;
char line_buffer[LINE_MAX_LENGTH + 1];
uint32_t line_length;

int connectionRequestCounter = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(&huart2, &rxData, 1, HAL_MAX_DELAY);

	if(huart == &huart1)
	{
		if (rxData == '\r' || rxData == '\n') {
			if(line_length > 0) {
				line_buffer[line_length] = '\0';
				if(strcmp(line_buffer, JOIN_ALREADY) == 0) {
					connectedToNetwork = true;
					networkStatusReceived = true;
				} else if(strcmp(line_buffer, NETWORK_JOINED) == 0) {
					connectedToNetwork = true;
				} else if (strcmp(line_buffer, JOIN_DONE) == 0) {
					networkStatusReceived = true;
				} else if (strcmp(line_buffer, MSG_DONE) == 0) {
					messageDoneStatusReceived = true;
				} else {
					configStatusReceived = true;
				}
				line_length = 0;
			}
		}
		else {
			if(line_length >= LINE_MAX_LENGTH) {
				line_length = 0;
			}
			line_buffer[line_length++] = rxData;
		}
	}

	if (huart == &huart3)
	{
		GPS_UART_Callback(&rxData);
	}

	HAL_UART_Receive_IT(&huart1, &rxData, 1);
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

__weak void HAL_Delay(uint32_t Delay)
{
	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = Delay;

	if(wait < HAL_MAX_DELAY)
	{
		wait += (uint32_t)uwTickFreq;
	}

	while((HAL_GetTick() - tickstart) < wait)
	{
		HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	}
}

int __io_putchar(int ch)
{
	if (ch == '\n'){
		uint8_t ch2 = '\r';
		HAL_UART_Transmit(&huart1, &ch2, 1, HAL_MAX_DELAY);	// 1 - lora / 2 - pc
	}

	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY); // 1 - lora / 2 - pc
	return 1;
}

void sendConfigMessageToLora(const char* msg)
{
	configStatusReceived = false;
	printf(msg);
	while(!configStatusReceived){
	}
	configStatusReceived = false;
}

void sendJoinRequestToLora()
{
	printf("AT+JOIN\r\n");
	while(!networkStatusReceived){
	}
	networkStatusReceived = false;
}

void sendToPC(char* str){
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen (str), HAL_MAX_DELAY);
}


void goToDeepSleep() {
	  sendConfigMessageToLora("AT+LOWPOWER=AUTOON\r\n");
	  HAL_Delay(10);
	  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, TIME_SLEEP, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
	  sendToPC("STANDBY MODE is ON\n");
	  HAL_PWR_EnterSTANDBYMode();
}

void connectToLora()
{
	connectionRequestCounter++;
	sendJoinRequestToLora();

	while(connectedToNetwork == 0 && connectionRequestCounter < MAX_ATTEMPTS_CONNECTION){
		sendConfigMessageToLora("AT+ID=DevAddr\r\n");
//		sendConfigMessageToLora("AT+ID=DevEui\r\n");
//		sendConfigMessageToLora("AT+ID=AppEui\r\n");
//		sendConfigMessageToLora("AT+LW=VER\r\n");

		sendConfigMessageToLora("AT+DR=EU868\r\n");
		sendConfigMessageToLora("AT+CH=NUM,0-2\r\n");
		sendConfigMessageToLora("AT+MODE=LWOTAA\r\n");
		sendConfigMessageToLora("AT+KEY=APPKEY,\"F4D4B405FF7AB3C3DF60C78F399B1E3C\"\r\n");
		sendJoinRequestToLora();

		connectionRequestCounter++;
	}

	if(connectionRequestCounter == MAX_ATTEMPTS_CONNECTION) {
		goToDeepSleep();
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

  sendToPC("\nWakeup from the STANDBY MODE\r\n");

  /* Wy????czenie trybu LOW-POWER (lora) i po????czenie si?? z sieci?? */
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2) == 0) {
	  HAL_Delay(1200);	// Przy pierwszym w????czeniu nale??y poczeka??, a?? uruchomi si?? modu?? LoRa
	  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, 1);
  }
  HAL_UART_Receive_IT(&huart1, &rxData, 1);
  sendConfigMessageToLora("????????AT+LOWPOWER=AUTOOFF\r\n");
  connectToLora();

  sendToPC("\nStart GPS\n");

  /* W??aczenie modu??u GPS */
  HAL_GPIO_WritePin(GPS_POWER_GPIO_Port, GPS_POWER_Pin, GPIO_PIN_SET);

  GPS_Init(&rxData);
  GPS_Init(&rxData);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  /** Czekanie na lokalizacje */
	  if(gpsDataReady)
	  {
		  Position currentPosition;
		  GPS_getCurrentPosition(&currentPosition);

		  /** Wy????czenie modu??u GPS */
		  HAL_GPIO_WritePin(GPS_POWER_GPIO_Port, GPS_POWER_Pin, GPIO_PIN_RESET);
		  sendToPC("\nKoniec GPS\n");

		  /* Pomiary i wysy??anie danych do TTN */
		  if (ds18b20_init() != HAL_OK)
		  {
			   Error_Handler();
		  }
		  uint8_t ds1[DS18B20_ROM_CODE_SIZE];
		  while (ds18b20_read_address(ds1) != HAL_OK)
		  {
			 // Error_Handler();
		  }
		  ds18b20_start_measure(NULL);
		  float temperature = ds18b20_get_temp(NULL) - 1.5f;
		  char temp[50];
		  sprintf(temp, "T1 = %.1f*C\r\n", temperature);
		  sendToPC(temp);

		  battery_init(&hadc1, HAL_MAX_DELAY);
	//	  float voltage = battery_getBatteryVolts();
		  int batteryLevel = battery_getBatteryChargeLevel();

		  printf("AT+MSG=%d_%f_%f_%f\r\n", batteryLevel, temperature, currentPosition.longitude, currentPosition.latitude);
		  HAL_Delay(1500); 	// czas na wys??anie danych


		  /* U??pienie urz??dzenia wraz z pod????czonymi czujnikami */
		  goToDeepSleep();
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
