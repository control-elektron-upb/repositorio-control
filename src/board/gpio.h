/**
 * @file gpio.h
 * @author Subgrupo Control
 * @brief Declaraciones hardware GPIO de Tarjeta de Control
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <stdbool.h>

#include "stm32f4xx_hal.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

#define LED1_GPIOx          (GPIOE)
#define LED1_GPIO_PIN       (GPIO_PIN_7)

#define LED2_GPIOx          (GPIOE)
#define LED2_GPIO_PIN       (GPIO_PIN_8)

#define LED3_GPIOx          (GPIOE)
#define LED3_GPIO_PIN       (GPIO_PIN_9)

#define BUZZER_GPIOx        (GPIOA)
#define BUZZER_GPIO_PIN     (GPIO_PIN_10)

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de GPIO.
 *  
 * @param None
 * @retval None
 */
void GPIO_Init(void);

void GPIO_LED1_SetValue(bool value);

void GPIO_LED2_SetValue(bool value);

void GPIO_LED3_SetValue(bool value);

void GPIO_BUZZER_SetValue(bool value);