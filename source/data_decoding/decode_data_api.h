/**
 * @file decode_data_api.h
 * @author Juan
 * @brief Definiciones API para decodificación de datos provenientes de CAN
 * @version 0.1
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "def_buses.h"
#include "receive_data.h"


/*******************************************************************************
 * Definitions
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
	ECO,        /**< Botón de modo ECO */ 
	NORMAL,     /**< Botón de modo NORMAL */ 
	SPORT       /**< Botón de modo SPORT */ 
}buttons_state_t;

/**
 * @brief Tipo de dato module_info_t para variable info de cada módulo
 * 
 */
typedef enum
{
	OK,         /**< Modulo OK */ 
	ERROR       /**< Modulo ERROR */ 
}module_info_t;

/**
 * @brief Tipo de dato dead_man_state_t para variable dead_man de periféricos
 * 
 */
typedef enum
{
	PRESS,      /**< Hombre muerto presionado */          
	NOPRESS     /**< Hombre muerto no presionado */ 
}dead_man_state_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de Periféricos
 * 
 */
typedef struct
{
	rx_var_t            pedal;						
	dead_man_state_t    dead_man;					
	buttons_state_t     buttons_change_state;

	module_info_t       peripherals_ok;			

}rx_peripherals_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de BMS
 * 
 */
typedef struct
{
    rx_var_t        voltaje;
    rx_var_t        corriente;
    rx_var_t        voltaje_min_celda;
    rx_var_t        potencia;
    rx_var_t        t_max;
    rx_var_t        nivel_bateria;

    module_info_t   bms_ok;

}rx_bms_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de DCDC
 * 
 */
typedef struct 
{
    rx_var_t        voltaje_bateria;
    rx_var_t        t_max;

    module_info_t   dcdc_ok;

}rx_dcdc_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de Inversor
 * 
 */
typedef struct 
{
    rx_var_t        velocidad;
    rx_var_t        V;
    rx_var_t        I;
    rx_var_t        temp_max;
    rx_var_t        temp_motor;
    rx_var_t        potencia;

    module_info_t   inversor_ok;

}rx_inversor_vars_t;


/*******************************************************************************
 * Variables
 ******************************************************************************/

extern uint8_t flag_decodificar;

