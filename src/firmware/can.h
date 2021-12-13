/**
 * @file can.h
 * @author Juan
 * @brief Declaraciones código de recepción y envío de datos CAN
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _CAN_H_
#define _CAN_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "stm32f4xx_hal.h"
#include "can_config.h"
#include "buses.h"
#include "decode_data.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de envío de datos a driver CAN.
 * 
 * Realiza el envío de los datos que se encuentran en el bus de salida CAN (bus 3) al driver CAN que interactúa con el
 * tranceiver de CAN de la tarjeta.
 * 
 * @param bus_can_output Puntero a estructura bus de salida CAN
 * @retval None
 */
void CAN_Driver_Send(typedef_bus2_t *bus_can_output);

/**
 * @brief Función handler de interrupción de recepción de datos de driver CAN.
 * 
 * Realiza la recepción de los datos que llegan desde el driver CAN y los guarda en la estructura de bus de entrada
 * de datos CAN (bus 2). Cuando se active una interrupción, activa la bandera de decodificación para indicar que
 * se puede ejecutar el bloque de decodificación de los datos que vienen de CAN.
 * 
 */
extern void USB_LP_CAN1_RX0_IRQHandler(void);

/**
 * @brief Función handler de interrupción de recepción de datos de driver CAN.
 * 
 * Realiza la recepción de los datos que llegan desde el driver CAN y los guarda en la estructura de bus de entrada
 * de datos CAN (bus 2). Cuando se active una interrupción, activa la bandera de decodificación para indicar que
 * se puede ejecutar el bloque de decodificación de los datos que vienen de CAN.
 * 
 * @param bus_can_input Puntero a estructura bus de recepción de datos CAN
 */
//extern void USB_LP_CAN1_RX0_IRQHandler(typedef_bus3_t *bus_can_input);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

extern CAN_HandleTypeDef hcan1;     // CAN handle structure instance

#endif /* _CAN_H_ */
