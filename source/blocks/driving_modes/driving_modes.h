/**
 * @file driving_modes.h
 * @author Juan
 * @brief Declaraciones máquina modos de manejo
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DRIVING_MODES_H_
#define _DRIVING_MODES_H_

#include "def_buses.h"

/*******************************************************************************
 * Types declarations
 ******************************************************************************/

/**
 * @brief Estados posibles de la máquina de estados
 * 
 */
enum
{
    kINIT = 0, /**< Estado de init */
    kECO,      /**< Estado modo de manejo */
    kNORMAL,   /**< Estado modo de manejo */
    kSPORT     /**< Estado modo de manejo */
};

/**
 * @brief Control Status
 * 
 */
enum
{
    NOT_READY = 0, /**< Esperando respuesta echo */
    IM_READY = 1   /**< Todos los módulos OK, Control listo! */
};

/*******************************************************************************
 * Public function prototypes
 ******************************************************************************/

/**
 * @brief Función principal máquina de modo de manejo
 * 
 * Máquina de estados de modo de manejo. Se encarga de permitir las transiciones entre 
 * los diferentes modos de acuerdo a los botones de periféricos y a la máquina de fallas. 
 * Es una interfaz directa con el piloto pero es limitada por el estado en el que se
 * encuentre la máquina de fallas. No es static, por lo que puede ser usada por otros
 * archivos.
 * 
 */
void DRIVING_MODES_SM(void);

/**
 * @brief Función estado inicial máquina de modo de manejo
 * 
 * Establece el estado inicial de la máquina de estados de modo de manejo. No es static, por 
 * lo que puede ser usada por otros archivos. No es static, por lo que puede ser usada por 
 * otros archivos.
 * 
 * @param START_STATE Estado inicial
 */
void DRIVING_MODES_SM_Init(const uint8_t START_STATE);

#endif /* _DRIVING_MODES_H_ */