/**
 * @file driving_modes.h
 * @author Juan
 * @brief Declaraciones m�quina modos de manejo
 * @version 0.1
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _DRIVING_MODES_H_
#define _DRIVING_MODES_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/** @brief Estados posibles de la m�quina de estados */
enum DrivingModes_States
{
    kINIT = 0, /**< Estado de init */
    kECO,      /**< Estado modo de manejo ECO */
    kNORMAL,   /**< Estado modo de manejo NORMAL */
    kSPORT     /**< Estado modo de manejo SPORT */
};

/**
 * @brief Tipo de dato control_status_t para status de Control
 *
 */
typedef enum
{
    NOT_READY = 0, /**< Esperando respuesta echo */
    IM_READY = 1   /**< Todos los m�dulos OK, Control listo! */
} control_status_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Funci�n principal m�quina de modos de manejo
 *
 * Llama a la funci�n m�quina de estados de modos de manejo. No es static, por
 * lo que puede ser usada por otros archivos.
 *
 */
void DRIVING_MODES(void);

/**
 * @brief Lee estado de la m�quina de estados de modo de manejo
 *
 * Lee estado de la m�quina de estados de modo de manejo. No es static, por lo
 * que puede ser usada por otros archivos.
 *
 * @return uint8_t Estado de la m�quina de estados
 *
 */
uint8_t get_DrivingModes_State(void);

#endif /* _DRIVING_MODES_H_ */
