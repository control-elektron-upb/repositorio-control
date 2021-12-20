/**
 * @file timers.h
 * @author Juan
 * @brief Declaraciones hardware de timers utilizados
 * @version 0.1
 * @date 2021-12-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _TIMERS_H_
#define _TIMERS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <stdint.h>

#include "stm32f4xx_hal.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/** @brief Duración de la espera hasta timeout en ms: estado kINIT maquina modos de manejo */
#define TIMEOUT_DURATION    5000

/***********************************************************************************************************************
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función de inicialización de timers.
 *  
 * @param None
 * @retval None
 */
void TIMER_Init(void);

/**
 * @brief Comienza timer
 * 
 * @param None
 * @retval None
 */
void TIMER_Start(void);

/**
 * @brief Parar timer
 * 
 * @param None
 * @retval None
 */
void TIMER_Stop(void);

/**
 * @brief Handler de interrupción de timer cuando
 * 
 * @param None
 * @retval None
 */
extern void TIM10_IRQHandler(void);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/** @brief Bandera timer en la interrupción */
extern uint8_t flag_timer;

#endif /* _TIMERS_H_ */