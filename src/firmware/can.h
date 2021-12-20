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
 * @brief Función de envío de datos CAN.
 * 
 * Realiza el envío de los datos que se encuentran en el bus de salida CAN (bus 2) a driver CAN que interactúa con el
 * tranceiver CAN de la tarjeta.
 * 
 * @param bus_can_output Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 * @retval None
 */
void CAN_Send(typedef_bus2_t *bus_can_output);

/**
 * @brief Función handler de interrupción de recepción de datos de driver CAN.
 * 
 * Realiza la recepción de los datos que llegan desde el driver CAN y los guarda en la estructura de bus de entrada
 * de datos CAN (bus 3). Cuando se active la interrupción, activa la bandera de decodificación para indicar que
 * se puede ejecutar el bloque de decodificación de los datos que vienen de CAN.
 * 
 * @param None
 * @retval None
 */
extern void USB_LP_CAN1_RX0_IRQHandler(void);

#endif /* _CAN_H_ */