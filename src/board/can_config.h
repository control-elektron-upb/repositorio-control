/**
 * @file can_config.h
 * @author Subgrupo Control
 * @brief Declaraciones para código de inicialización y configuración del CAN
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _CAN_CONFIG_H_
#define _CAN_CONFIG_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "stm32f4xx_hal.h"
#include "buses.h"

/***********************************************************************************************************************
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de driver CAN.
 * 
 * @param None
 * @retval None
 */
void CAN_Driver_Init(void);         // CAN Driver Initialization Function

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/**
 * @brief CAN handle structure instance
 * 
 */
extern CAN_HandleTypeDef hcan1;     // Debe ser global porque el código de CAN utiliza esta estructura handle

#endif /* _CAN_CONFIG_H_ */