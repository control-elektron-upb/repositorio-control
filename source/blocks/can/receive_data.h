/**
 * @file receive_data.h
 * @author Juan
 * @brief Declaraciones recepción de datos CAN
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _RECEIVE_DATA_H_
#define _RECEIVE_DATA_H_

#include "decode_data.h"

/*******************************************************************************
 * Types declarations
 ******************************************************************************/

/**
 * @brief Valores para la bandera de decodificación
 * 
 */
enum
{
    kDECODIFICA = 0, /**< Valor para decodificar */
    kNO_DECODIFICA   /**< Valor para no decodificar */
};

/**
 * @brief Tipo de dato para bandera de decodificación
 * 
 */
typedef uint8_t decode_status_t;

/*******************************************************************************
 * Global variables declarations
 ******************************************************************************/

extern decode_status_t flag_decodificar; /* puede ser manipulada por otros archivos */

#endif /* _RECEIVE_DATA_H_ */