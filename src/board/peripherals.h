/**
 * @file peripherals.h
 * @author Subgrupo Control
 * @brief Declaraciones de periféricos utilizados del microcontrolador
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "stm32f4xx_hal.h"
#include "can_config.h"
#include "timers.h"
#include "gpio.h"

/***********************************************************************************************************************
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de los periféricos a utilizar del microcontrolador.
 * 
 * @param None
 * @retval None
 */
void BOARD_PERIPHERALS_Init(void);  // Board peripherals inicialization function

#endif