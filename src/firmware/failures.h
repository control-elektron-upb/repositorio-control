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
 * Macros
 **********************************************************************************************************************/

/** @brief Valor CAN para variable estado_falla del bus de salida can */
#define CAN_OK			0x00

/** @brief Valor CAN para variable estado_falla del bus de salida can */
#define CAN_CAUTION_1	0x01

/** @brief Valor CAN para variable estado_falla del bus de salida can */
#define CAN_CAUTION_2	0x02

/** @brief Valor CAN para variable estado_falla del bus de salida can */
#define CAN_AUTOKILL	0x03

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
 * Public functions prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de fallas.
 *
 * Determina estado general de cada uno de los modulos segun el estado de las
 * variables decodificadas. 
 * 
 * Llama a la función máquina de estados de fallas.
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void FAILURES(void);

/**
 * @brief Lee estado de la máquina de estados de fallas.
 *
 * Lee estado de la máquina de estados de fallas. No es static, por lo que puede ser
 * usada por otros archivos.
 *
 * @param None
 * @return uint8_t Estado de la máquina de estados
 */
uint8_t FAILURES_Get_State(void);

#endif /* _FAILURES_H_ */
