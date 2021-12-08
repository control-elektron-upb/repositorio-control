/**
 * @file rampa_pedal.h
 * @author Subgrupo Control
 * @brief Declaraciones rampa pedal
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _RAMPA_PEDAL_H_
#define _RAMPA_PEDAL_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <math.h>

#include "buses.h"

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal de bloque rampa pedal
 *
 * Rampa pedal se encarga de transformar el valor de pedal registrado de periféricos
 * a un valor de velocidad que será empleado por inversor. Para cada modo de manejo
 * se tiene una función de transferencia diferente para determinar el valor de
 * velocidad asociado al valor de pedal registrado desde periféricos.
 *
 * Lee la variable pedal de la estructura de variables decodificadas de periféricos,
 * es decir, la estructura de tipo rx_peripherals_t que se encuentra en el bus_data.
 *
 * Escribe en la variable velocidad del bus_data.
 *
 */
void RAMPA_PEDAL(void);

#endif /* _RAMPA_PEDAL_H_ */
