/**
 * @file peripherals.c
 * @author Subgrupo Control
 * @brief Implementaciones de periféricos utilizados del microcontrolador
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "peripherals.h"

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de los periféricos a utilizar del microcontrolador.
 * 
 * @param None
 * @retval None
 */
void BOARD_PERIPHERALS_Init(void)
{
  CAN_DRIVER_Init();    // inicializa driver CAN

  GPIO_Init();          // inicializa LEDs, BUZZER

  TIMER_Init();         // inicializa timers
}
