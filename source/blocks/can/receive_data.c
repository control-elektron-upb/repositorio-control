/**
 * @file receive_data.c
 * @author Juan
 * @brief Recepción de datos CAN
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "receive_data.h"

/*******************************************************************************
 * Variables definitions
 ******************************************************************************/

/**
 * @brief Inicialización bandera para ejecutar bloque de decodificación
 * 
 */
decode_status_t flag_decodificar = kNO_DECODIFICA;