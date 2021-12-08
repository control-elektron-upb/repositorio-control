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

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/** @brief Estados posibles de la máquina de estados */
enum FailuresStates
{
    kOK = 0,   /**< Estado falla OK */
    kCAUTION1, /**< Estado falla CAUTION1 */
    kCAUTION2, /**< Estado falla CAUTION2 */
    kAUTOKILL  /**< Estado falla AUTOKILL */
};
 
 /***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

 /**
  * @brief Función principal máquina de fallas
  *
  * Primero determina estado general de cada uno de los modulos segun el estado de las
  * variables decodificadas. Luego, llama a la función máquina de estados de fallas.
  * No es static, por lo que puede ser usada por otros archivos.
  *
  */
void FAILURES(void);

/**
 * @brief Lee estado de la máquina de estados de fallas
 *
 * Lee estado de la máquina de estados de fallas. No es static, por lo que puede ser
 * usada por otros archivos.
 *
 * @return uint8_t Estado de la máquina de estados
 */
uint8_t get_Failures_State(void);

#endif /* _FAILURES_H_ */
