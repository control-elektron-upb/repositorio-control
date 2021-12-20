/**
 * @file decode_data.h
 * @author Juan
 * @brief Declaraciones decodificación de datos provenientes de bus CAN
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _DECODE_DATA_H_
#define _DECODE_DATA_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/** @brief Valor CAN para las variables peripherals_ok, bms_ok, dcdc_ok, inversor_ok  */
#define CAN_OK          0x01

/** @brief Valor CAN para las variables peripherals_ok, bms_ok, dcdc_ok, inversor_ok  */
#define CAN_ERROR       0x02

/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN1        0x01

/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN2        0x02

/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN3        0x03

/** @brief Valor CAN para dead_man */
#define CAN_PRESS       0x01

/** @brief Valor CAN para dead_man */
#define CAN_NOPRESS     0x02

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato decode_status_t para bandera de decodificación
 *
 */
typedef enum
{
    DECODIFICA = 0, /**< Valor para decodificar */
    NO_DECODIFICA   /**< Valor para no decodificar */
} decode_status_t;

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal de decodificación de datos de bus CAN.
 *
 * Decodifica los datos que se reciben desde el bus CAN de: periféricos, BMS,
 * DCDC, e inversor. Los datos decodificados quedan guardados en estructuras
 * de tipo rx_peripherals_vars_t, rx_bms_vars_t, rx_dcdc_vars_t, y rx_inversor_vars_t,
 * en el bus_data. Estas estructuras son Rx_Peripherals, Rx_Bms, Rx_Dcdc y Rx_Inversor.
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void DECODE_DATA(void);

/***********************************************************************************************************************
 * Global variables declarations
 **********************************************************************************************************************/

/**
 * @brief Bandera para ejecutar bloque de decodificación de datos
 * 
 */
extern decode_status_t flag_decodificar;    // puede ser manipulada por otros archivos

#endif /* _DECODE_DATA_H_ */