/**
 * @file peripherals.h
 * @author Subgrupo Control
 * @brief Declaraciones de periféricos de la tarjeta de Control
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

#include "can_config.h"

/***********************************************************************************************************************
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de los periféricos configurados de la tarjeta de Control.
 * 
 * @param None
 * @retval None
 */
void Board_Peripherals_Init(void);  // Board peripherals inicialization function

#endif