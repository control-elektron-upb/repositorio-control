/**
 * @file receive_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "def_buses.h"


/**
 * @brief Valores para la bandera de decodificación
 * 
 */
enum
{
    kDECODIFICA,        /**< Valor para decodificar */
    kNO_DECODIFICA      /**< Valor para no decodificar */
};


/**
 * @brief Tipo de dato para bandera de decodificación
 * 
 */
typedef uint8_t decode_status_t;


/**
 * @brief Bandera para ejecutar bloque de decodificación
 * 
 */
decode_status_t flag_decodificar;
