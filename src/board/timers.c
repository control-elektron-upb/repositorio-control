/**
 * @file timers.c
 * @author Juan
 * @brief Implementaciones hardware de timers utilizados
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "timers.h"

/***********************************************************************************************************************
 * Variables definitions
 **********************************************************************************************************************/

/** @brief TIM Time Base Handle Structure */
static TIM_HandleTypeDef htim10;

/** @brief Bandera timer en la interrupción */
uint8_t flag_timer = 0;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void TIM10_Init(void);

static void ErrorHandler(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de timers.
 * 
 * @param None
 * @retval None
 */
void TIMER_Init(void)
{
    TIM10_Init();   // inicializa timer para duración de TIMEOUT_DURATION
}

/**
 * @brief Comienza timer
 * 
 * @param None
 * @retval None
 */
void TIMER_Start(void)
{
    HAL_TIM_Base_Start(&htim10);
}

/**
 * @brief Parar timer
 * 
 * @param None
 * @retval None
 */
void TIMER_Stop(void)
{
    HAL_TIM_Base_Stop(&htim10);
}

/**
 * @brief Handler de interrupción de timer cuando
 * 
 * @param None
 * @retval None
 */
void TIM10_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim10);
	flag_timer = 1;
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief TIM10 Initialization Function
 * 
 * @param None
 * @retval None
 */
static void TIM10_Init(void)
{
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 1600-1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 10000-1;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief This function is executed in case of error occurrence.
 * 
 * @retval None
 */
static void ErrorHandler(void)
{
  //__disable_irq();
  while (1)
  {
  }
}