/**
 * @file peripherals.c
 * @author Subgrupo Control
 * @brief Implementaciones de periféricos de la tarjeta de Control
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
 * @brief Función de inicialización de los periféricos configurados de la tarjeta de Control.
 * 
 * @param None
 * @retval None
 */
void Board_Peripherals_Init(void)
{
  /* Initialize components */
  CAN_Driver_Init();
  //GPIO_Init();
}
