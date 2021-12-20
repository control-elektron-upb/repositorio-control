/**
 * @file gpio.c
 * @author Subgrupo Control
 * @brief Implementaciones hardware GPIO de Tarjeta de Control
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "gpio.h"

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief 
 * 
 * @param value 
 */
void GPIO_LED1_SetValue(bool value)
{
    HAL_GPIO_WritePin(LED1_GPIOx, LED1_GPIO_PIN, value);
}

/**
 * @brief 
 * 
 * @param value 
 */
void GPIO_LED2_SetValue(bool value)
{
    HAL_GPIO_WritePin(LED2_GPIOx, LED2_GPIO_PIN, value);
}

/**
 * @brief 
 * 
 * @param value 
 */
void GPIO_LED3_SetValue(bool value)
{
    HAL_GPIO_WritePin(LED3_GPIOx, LED3_GPIO_PIN, value);
}

/**
 * @brief 
 * 
 * @param value 
 */
void GPIO_BUZZER_SetValue(bool value)
{
    HAL_GPIO_WritePin(BUZZER_GPIOx, BUZZER_GPIO_PIN, value);
}

/**
 * @brief Función de inicialización de GPIO.
 * 
 * @param None
 * @retval None
 */
void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE7 PE8 PE9 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}