/**
 * @file failures.h
 * @author Juan
 * @brief Declaraciones m�quina de fallas
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

/** @brief Estados posibles de la m�quina de estados */
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
  * @brief Funci�n principal m�quina de fallas
  *
  * Primero determina estado general de cada uno de los modulos segun el estado de las
  * variables decodificadas. Luego, llama a la funci�n m�quina de estados de fallas.
  * No es static, por lo que puede ser usada por otros archivos.
  *
  */
void FAILURES(void);

/**
 * @brief Lee estado de la m�quina de estados de fallas
 *
 * Lee estado de la m�quina de estados de fallas. No es static, por lo que puede ser
 * usada por otros archivos.
 *
 * @return uint8_t Estado de la m�quina de estados
 */
uint8_t get_Failures_State(void);

#endif /* _FAILURES_H_ */
