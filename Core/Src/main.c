/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "game.h"
#include "lcd.h"

uint8_t key;
volatile uint32_t timer = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

const uint16_t boardRedPins[3][3] = {
	{Red_11_Pin, Red_12_Pin, Red_13_Pin},
	{Red_21_Pin, Red_22_Pin, Red_23_Pin},
	{Red_31_Pin, Red_32_Pin, Red_33_Pin}
};

const uint16_t boardGreenPins[3][3] = {
	{Green_11_Pin, Green_12_Pin, Green_13_Pin},
	{Green_21_Pin, Green_22_Pin, Green_23_Pin},
	{Green_31_Pin, Green_32_Pin, Green_33_Pin}
};

GPIO_TypeDef* redPinPorts[3][3] = {
	{GPIOC, GPIOC, GPIOC},
	{GPIOC, GPIOA, GPIOC},
	{GPIOC, GPIOC, Red_33_GPIO_Port}
};

GPIO_TypeDef* greenPinPorts[3][3] = {
	{GPIOB, GPIOB, GPIOA},
	{GPIOA, GPIOA, GPIOB},
	{GPIOB, GPIOB, GPIOB}
};

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

void renderState(TicTacToe_State* state);
void renderOnLCD(uint8_t redScore, uint8_t greenScore, char* msg1, char* msg2);
void userInputAndUpdateDisplay(uint8_t* key, uint8_t* timer, TicTacToe_State* state);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void renderState(TicTacToe_State* state) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (state->board[r][c] == 'r') {
				HAL_GPIO_WritePin(
					redPinPorts[r][c],
					boardRedPins[r][c],
					1
				);
			} else if (state->board[r][c] == 'g') {
				HAL_GPIO_WritePin(
					greenPinPorts[r][c],
					boardGreenPins[r][c],
					1
				);
			} else if (state->board[r][c] == '-') {
				HAL_GPIO_WritePin(
					redPinPorts[r][c],
					boardRedPins[r][c],
					0
				);

				HAL_GPIO_WritePin(
					greenPinPorts[r][c],
					boardGreenPins[r][c],
					0
				);
			}
		}
	}
}

void renderOnLCD(uint8_t redScore, uint8_t greenScore, char* msg1, char* msg2) {
	char redScoreMsg[20];
	char greenScoreMsg[20];

	sprintf(redScoreMsg, "%s%u", "Red Score: ", redScore);
	sprintf(greenScoreMsg, "%s%u", "Green Score: ", greenScore);

	lcd_write_pos(&huart1, redScoreMsg, strlen(redScoreMsg), 0, 0);
	lcd_write_pos(&huart1, greenScoreMsg, strlen(greenScoreMsg), 1, 0);
	lcd_write_pos(&huart1, msg1, strlen(msg1), 2, 0);
	lcd_write_pos(&huart1, msg2, strlen(msg2), 3, 0);
}

void userInputAndUpdateDisplay(uint8_t* key, uint8_t* timer, TicTacToe_State* state) {
	if (*timer < 100) {
		return;
	}

	if (*key == 0) {
		return;
	}

	uint8_t rowToMove = 0;
	uint8_t colToMove = 0;
	switch(*key) {
		case '1':
			rowToMove = 0;
	  	colToMove = 0;
	  	break;
	  case '2':
	  	rowToMove = 0;
	  	colToMove = 1;
	  	break;
	  case '3':
	  	rowToMove = 0;
	  	colToMove = 2;
	  	break;
	  case '4':
	  	rowToMove = 1;
	  	colToMove = 0;
	  	break;
	  case '5':
	  	rowToMove = 1;
	  	colToMove = 1;
	  	break;
	  case '6':
	  	rowToMove = 1;
	  	colToMove = 2;
	  	break;
	  case '7':
	  	rowToMove = 2;
	  	colToMove = 0;
	  	break;
	  case '8':
	  	rowToMove = 2;
	  	colToMove = 1;
	  	break;
	  case '9':
	  	rowToMove = 2;
	  	colToMove = 2;
	  	break;
	}

	if (state->board[rowToMove][colToMove] != '-') {
		return;
	}
	*state = act(state, rowToMove, colToMove);

	renderState(state);
	lcd_clearScreen(&huart1);

	*key = 0;
	*timer = 0;
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  TicTacToe_State state = getInitialState();
  key = 0;
  HAL_GPIO_WritePin(GPIOB, COL_1_Pin|COL_0_Pin|COL_3_Pin|COL_2_Pin, 1);

  renderState(&state);

  uint8_t redScore = 0;
  uint8_t greenScore = 0;
  uint8_t inGame = 0;
  uint8_t isAi = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  	if (inGame == 0) {
  		renderOnLCD(redScore, greenScore, "Press A for Human", "Press B for AI");

  		if (timer < 100) {
  		  continue;
  		}

  		if (key == 0) {
  		  continue;
  		}
  		switch(key) {
  			case 'A':
  				isAi = 0;
  				break;
  			case 'B':
  				isAi = 1;
  				break;
  			default:
  				isAi = 0;
  				break;
  		}
  		lcd_clearScreen(&huart1);
  		inGame = 1;

  		key = 0;
  		timer = 0;
  	} else if (inGame == 1) {

  		if (isTerminal(&state) == 1) {
  			if (hasWon(&state, 'r') == 1) {
  				redScore += 1;
  			}

  			if (hasWon(&state, 'g') == 1) {
  				greenScore += 1;
  		  }

  			state = getInitialState();
  			renderState(&state);
  			inGame = 0;
  		}

  		if (state.greenTurn == 1) {
  			renderOnLCD(redScore, greenScore, "Green's Turn", "");
  			userInputAndUpdateDisplay(&key, &timer, &state);

  		}
  		else if (state.greenTurn == 0) {

  			 if (isAi == 1) {
  				 moveToMake AIMove = findMoveByAI(&state);
  				 state = act(&state, AIMove.rowToMove, AIMove.colToMove);

  				 renderState(&state);
  				 lcd_clearScreen(&huart1);
  			 } else {
  				 renderOnLCD(redScore, greenScore, "Red's Turn", "");
  				 userInputAndUpdateDisplay(&key, &timer, &state);
  			 }

  		 }
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Red_21_Pin|Red_13_Pin|Red_12_Pin|Red_11_Pin
                          |Green_31_Pin|Red_31_Pin|Red_32_Pin|Red_23_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Green_13_Pin|Green_21_Pin|Green_22_Pin|Green_23_Pin
                          |Red_22_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Green_33_Pin|COL_1_Pin|COL_0_Pin|COL_3_Pin
                          |COL_2_Pin|Green_12_Pin|Green_11_Pin|Green_32_Pin
                          |Green_31B7_Pin|Green_23B8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Red_33_GPIO_Port, Red_33_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Red_21_Pin Red_13_Pin Red_12_Pin Red_11_Pin
                           Green_31_Pin Red_31_Pin Red_32_Pin Red_23_Pin */
  GPIO_InitStruct.Pin = Red_21_Pin|Red_13_Pin|Red_12_Pin|Red_11_Pin
                          |Green_31_Pin|Red_31_Pin|Red_32_Pin|Red_23_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Green_13_Pin Green_21_Pin Green_22_Pin Green_23_Pin
                           Red_22_Pin */
  GPIO_InitStruct.Pin = Green_13_Pin|Green_21_Pin|Green_22_Pin|Green_23_Pin
                          |Red_22_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW_0_Pin ROW_1_Pin ROW_2_Pin ROW_3_Pin */
  GPIO_InitStruct.Pin = ROW_0_Pin|ROW_1_Pin|ROW_2_Pin|ROW_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Green_33_Pin COL_1_Pin COL_0_Pin COL_3_Pin
                           COL_2_Pin Green_12_Pin Green_11_Pin Green_32_Pin
                           Green_31B7_Pin Green_23B8_Pin */
  GPIO_InitStruct.Pin = Green_33_Pin|COL_1_Pin|COL_0_Pin|COL_3_Pin
                          |COL_2_Pin|Green_12_Pin|Green_11_Pin|Green_32_Pin
                          |Green_31B7_Pin|Green_23B8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Red_33_Pin */
  GPIO_InitStruct.Pin = Red_33_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Red_33_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
