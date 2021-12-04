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

#include "def_buses.h"

/*******************************************************************************
 * Types declarations
 ******************************************************************************/

/**
 * @brief  Tipo de dato rx_var_t para variables analógicas decodificadas 
 * 
 */
typedef float rx_var_t;

/**
 * @brief Tipo de dato buttons_state_t para variable botones de periféricos
 * 
 */
typedef enum
{
    ECO,    /**< Botón de modo ECO */
    NORMAL, /**< Botón de modo NORMAL */
    SPORT   /**< Botón de modo SPORT */
} buttons_state_t;

/**
 * @brief Tipo de dato module_info_t para variable info de cada módulo: 
 * periféricos, BMS, DCDC, inversor.
 * 
 */
typedef enum
{
    OK,   /**< Modulo OK */
    ERROR /**< Modulo ERROR */
} module_info_t;

/**
 * @brief Tipo de dato dead_man_state_t para variable dead_man de periféricos
 * 
 */
typedef enum
{
    PRESS,  /**< Hombre muerto presionado */
    NOPRESS /**< Hombre muerto no presionado */
} dead_man_state_t;

/**
 * @brief Tipo de estructura para variables decodificadas de periféricos
 * 
 */
typedef struct rx_peripherals_vars_t
{
    rx_var_t pedal;
    dead_man_state_t dead_man;
    buttons_state_t buttons_change_state;

    module_info_t peripherals_ok;

} rx_peripherals_vars_t;

/**
 * @brief Tipo de estructura para variables decodificadas del BMS
 * 
 */
typedef struct rx_bms_vars_t
{
    rx_var_t voltaje;
    rx_var_t corriente;
    rx_var_t voltaje_min_celda;
    rx_var_t potencia;
    rx_var_t t_max;
    rx_var_t nivel_bateria;

    module_info_t bms_ok;

} rx_bms_vars_t;

/**
 * @brief Tipo de estructura para variables decodificadas del DCDC
 * 
 */
typedef struct rx_dcdc_vars_t
{
    rx_var_t voltaje_bateria;
    rx_var_t t_max;

    module_info_t dcdc_ok;

} rx_dcdc_vars_t;

/**
 * @brief Tipo de estructura para variables decodificadas del inversor
 * 
 */
typedef struct rx_inversor_vars_t
{
    rx_var_t velocidad;
    rx_var_t V;
    rx_var_t I;
    rx_var_t temp_max;
    rx_var_t temp_motor;
    rx_var_t potencia;

    module_info_t inversor_ok;

} rx_inversor_vars_t;

/*******************************************************************************
 * Public function prototypes
 ******************************************************************************/

/**
 * @brief Función principal de decodificación de datos de bus CAN
 * 
 * Decodifica los datos que se reciben desde el bus CAN de: periféricos, BMS,
 * DCDC, inversor. Los datos decodificados quedan guardados en estructuras
 * de tipo rx_peripherals_vars_t, rx_bms_vars_t, rx_dcdc_vars_t, y rx_inversor_vars_t, 
 * en el bus_data. Estas estructuras son Rx_Peripherals, Rx_Bms, Rx_Dcdc y Rx_Inversor. 
 * No es static, por lo que puede ser usada por otros archivos.
 * 
 * @param flag_decodificar Bandera para ejecutar bloque de decodificación
 */
void decode_Data(decode_status_t flag_decodificar);

#endif /* _DECODE_DATA_H_ */