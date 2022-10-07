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
#include "can.h"
#include "crc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "App\c_interface\sig_gen_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void TestFreqChange();
void MY_SIG_GEN_Init();
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
  SIG_GEN_HandleTypeDef sig_gen_0 = {0};
  SIG_GEN_HandleTypeDef sig_gen_1 = {0};
  SIG_GEN_HandleTypeDef sig_gen_2 = {0};
  SIG_GEN_HandleTypeDef sig_gen_3 = {0};
  SIG_GEN_HandleTypeDef sig_gen_4 = {0};
  SIG_GEN_HandleTypeDef sig_gen_5 = {0};
  SIG_GEN_HandleTypeDef sig_gen_6 = {0};
  SIG_GEN_HandleTypeDef sig_gen_7 = {0};
  static const uint32_t DELAY = 6000;

  static SIG_GEN_RangeCoeff amp_array_[] = {
    { 0., 0.3, 1.0 },
    { 0.3, 0.5, 1.0 },
    { 0.5, 1.0, 1.0 }
  };

  static SIG_GEN_RangeCoeff freq_array_[] = {
    { 0., 20., 1.0 },
    { 20., 50., 1.0 },
    { 50., 5000., 1.0 }
  };

  static SIG_GEN_CoeffsInitStruct corr_array_[] = {
    amp_array_,
    3,
    freq_array_,
    3
  };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_CAN1_Init();
  MX_CRC_Init();
  MX_TIM5_Init();
  MX_TIM7_Init();
  MX_UART5_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
//  InitPwmControllers();
  MY_SIG_GEN_Init();
  HAL_TIM_Base_Start_IT(&htim14);
//  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SQUARE);
//  HAL_Delay(DELAY);
//  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_TRIANGLE);
//  HAL_Delay(DELAY);
//  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SAW);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SINUS);
//    HAL_Delay(3000);
//    TestAmpChange();
    TestFreqChange();
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SQUARE);
//    TestAmpChange();
//    TestFreqChange();
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_TRIANGLE);
//    TestAmpChange();
//    TestFreqChange();
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SAW);
//    TestAmpChange();
//    TestFreqChange();
//    TestAmpModChange();
  
//    SIG_GEN_SetCarrierAmp(&sig_gen_3, 1.0);
//    SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 10);
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SINUS);
//    HAL_Delay(DELAY);
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SQUARE);
//    HAL_Delay(DELAY);
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_TRIANGLE);
//    HAL_Delay(DELAY);
//    SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SAW);
//    HAL_Delay(DELAY);
//    TestModDepthChange();
//    TestModSensChange();
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void MY_SIG_GEN_Init() {
  sig_gen_0.pwm_timer = &htim1;
  sig_gen_0.channels[0] = TIM_CHANNEL_1;
  sig_gen_0.channels[1] = TIM_CHANNEL_2;
  sig_gen_0.min_duty_cycle_percent = 60;
  sig_gen_0.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_0) != SIG_GEN_OK) {
    Error_Handler();
  }
  
  sig_gen_1.pwm_timer = &htim2;
  sig_gen_1.channels[0] = TIM_CHANNEL_1;
  sig_gen_1.channels[1] = TIM_CHANNEL_2;
  sig_gen_1.min_duty_cycle_percent = 60;
  sig_gen_1.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_1) != SIG_GEN_OK) {
    Error_Handler();
  }

  sig_gen_2.pwm_timer = &htim2;
  sig_gen_2.channels[0] = TIM_CHANNEL_3;
  sig_gen_2.channels[1] = TIM_CHANNEL_4;
  sig_gen_2.min_duty_cycle_percent = 60;
  sig_gen_2.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_2) != SIG_GEN_OK) {
    Error_Handler();
  }

  sig_gen_3.pwm_timer = &htim3;
  sig_gen_3.channels[0] = TIM_CHANNEL_1;
  sig_gen_3.channels[1] = TIM_CHANNEL_2;
  sig_gen_3.min_duty_cycle_percent = 55;
  sig_gen_3.max_duty_cycle_percent = 85;
  sig_gen_3.coeffs = corr_array_;
  if (SIG_GEN_Init(&sig_gen_3) != SIG_GEN_OK) {
    Error_Handler();
  }
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_TYPE_SINUS);
  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 100.);

  sig_gen_4.pwm_timer = &htim3;
  sig_gen_4.channels[0] = TIM_CHANNEL_3;
  sig_gen_4.channels[1] = TIM_CHANNEL_4;
  sig_gen_4.min_duty_cycle_percent = 60;
  sig_gen_4.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_4) != SIG_GEN_OK) {
    Error_Handler();
  }

  sig_gen_5.pwm_timer = &htim4;
  sig_gen_5.channels[0] = TIM_CHANNEL_1;
  sig_gen_5.channels[1] = TIM_CHANNEL_2;
  sig_gen_5.min_duty_cycle_percent = 60;
  sig_gen_5.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_5) != SIG_GEN_OK) {
    Error_Handler();
  }

  sig_gen_6.pwm_timer = &htim8;
  sig_gen_6.channels[0] = TIM_CHANNEL_1;
  sig_gen_6.channels[1] = TIM_CHANNEL_2;
  sig_gen_6.min_duty_cycle_percent = 60;
  sig_gen_6.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_6) != SIG_GEN_OK) {
    Error_Handler();
  }

  sig_gen_7.pwm_timer = &htim12;
  sig_gen_7.channels[0] = TIM_CHANNEL_1;
  sig_gen_7.channels[1] = TIM_CHANNEL_2;
  sig_gen_7.min_duty_cycle_percent = 60;
  sig_gen_7.max_duty_cycle_percent = 75;
  if (SIG_GEN_Init(&sig_gen_7) != SIG_GEN_OK) {
    Error_Handler();
  }
}

void TestAmpChange() {
  SIG_GEN_SetCarrierAmp(&sig_gen_3, 0.0);
  HAL_Delay(DELAY);
  SIG_GEN_SetCarrierAmp(&sig_gen_3, 0.3);
  HAL_Delay(DELAY);
  SIG_GEN_SetCarrierAmp(&sig_gen_3, 0.5);
  HAL_Delay(DELAY);
  SIG_GEN_SetCarrierAmp(&sig_gen_3, 1.0);
  HAL_Delay(DELAY);
}

void TestFreqChange() {
//  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 1.);
//  HAL_Delay(DELAY);
//  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 10.);
//  HAL_Delay(DELAY);
//  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 30.);
//  HAL_Delay(DELAY);
  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 100.);
  HAL_Delay(DELAY);
}

void TestAmpModChange() {
  SIG_GEN_SetCarrierAmp(&sig_gen_3, 1.0);
  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, 50);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_NONE);
  HAL_Delay(DELAY);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SINUS);
  HAL_Delay(DELAY);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SQUARE);
  HAL_Delay(DELAY);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_TRIANGLE);
  HAL_Delay(DELAY);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_SAW);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreq(&sig_gen_3, SIG_GEN_CARRIER, SIG_GEN_DEFAULT_SENS_AMP);
  SIG_GEN_SetSignalType(&sig_gen_3, SIG_GEN_AMP_MOD, SIG_GEN_TYPE_NONE);
}

void TestModDepthChange() {
  SIG_GEN_SetAmpModDepth(&sig_gen_3, SIG_GEN_DEFAULT_SENS_AMP);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 90);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 80);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 70);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 60);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 50);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 40);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 30);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 20);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 10);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, 0);
  HAL_Delay(DELAY);
  SIG_GEN_SetAmpModDepth(&sig_gen_3, SIG_GEN_DEFAULT_SENS_AMP);
}

void TestModSensChange() {
  SIG_GEN_SetFreqModSens(&sig_gen_3, 0);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 10);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 20);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 30);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 40);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 50);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 60);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 70);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 80);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, 90);
  HAL_Delay(DELAY);
  SIG_GEN_SetFreqModSens(&sig_gen_3, SIG_GEN_DEFAULT_SENS_AMP);
  HAL_Delay(DELAY);
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  else if (htim->Instance == TIM14) {
    SIG_GEN_Run(&sig_gen_3);
  }
  /* USER CODE END Callback 1 */
}

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

