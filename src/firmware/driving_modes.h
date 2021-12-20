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

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"
#include "decode_data.h"
#include "can.h"
#include "timers.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/** @brief Valor CAN para variable estado_manejo del bus de salida can */
#define CAN_NORMAL		0x02

/** @brief Valor CAN para variable estado_manejo del bus de salida can */
#define	CAN_ECO			0x03

/** @brief Valor CAN para variable estado_manejo del bus de salida can */
#define CAN_SPORT		0x04

/** @brief Valor CAN para variable control_ok del bus de salida can utilizado en transmisón de echo a demás módulos */
#define CAN_IDLE		0x00

/** @brief Valor CAN para variable control_ok del bus de salida can utilizado en transmisón de echo a demás módulos */
#define CAN_ECHO		0x01

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/** @brief Estados posibles de la máquina de estados */
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
    IM_READY = 1   /**< Todos los módulos OK, Control listo! */
} control_status_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de modos de manejo.
 *
 * Llama a la función máquina de estados de modos de manejo. No es static, por
 * lo que puede ser usada por otros archivos.
 * 
 * @param None
 * @retval None
 */
void DRIVING_MODES(void);

/**
 * @brief Lee estado de la máquina de estados de modo de manejo.
 *
 * Lee estado de la máquina de estados de modo de manejo. No es static, por lo
 * que puede ser usada por otros archivos.
 * 
 * @param None
 * @return uint8_t Estado de la máquina de estados
 */
uint8_t DRIVING_MODES_Get_State(void);

#endif /* _DRIVING_MODES_H_ */
