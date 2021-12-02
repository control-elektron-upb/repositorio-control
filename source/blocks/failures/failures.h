/**
 * @file failures.h
 * @author Juan
 * @brief Declaraciones máquina de fallas
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _FAILURES_H_
#define _FAILURES_H_

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
    kOK = 0,   /**< Estado falla OK */
    kCAUTION1, /**< Estado falla CAUTION1 */
    kCAUTION2, /**< Estado falla CAUTION2 */
    kAUTOKILL  /**< Estado falla AUTOKILL */
};

/*******************************************************************************
 * Public function prototypes
 ******************************************************************************/

/**
 * @brief Función principal máquina de fallas
 * 
 * Máquina de estados de fallas. Se encarga de realizar transiciones entre diferentes 
 * fallas de acuerdo con el estado de las variables del vehículo. Establece el tope de 
 * modo de manejo. No es static, por lo que puede ser usada por otros archivos.
 * 
 */
void FAILURES_SM(void);

/**
 * @brief Función estado inicial máquina de modo de manejo
 * 
 * Establece el estado inicial de la máquina de estados de fallas. No es static, por 
 * lo que puede ser usada por otros archivos. No es static, por lo que puede ser usada 
 * por otros archivos.
 * 
 * @param START_STATE Estado inicial
 */
void FAILURES_SM_Init(const uint8_t START_STATE);

#endif /* _FAILURES_H_ */