/**
 * @file decode_data.h
 * @author Juan
 * @brief Definiciones para decodificación de datos provenientes de CAN
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef _DECODE_DATA_H_
#define _DECODE_DATA_H_

/**
 * @brief  Tipo de dato float para variables analógicas decodificadas 
 * 
 */
typedef float rx_var_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de Periféricos
 * 
 */
typedef struct
{
	rx_var_t        pedal;						
	dead_man_state  dead_man;					
	buttons_state   buttons_change_state;

	module_info     peripherals_ok;			

}rx_peripherals_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de BMS
 * 
 */
typedef struct
{
    rx_var_t    voltaje;
    rx_var_t    corriente;
    rx_var_t    voltaje_min_celda;
    rx_var_t    potencia;
    rx_var_t    t_max;
    rx_var_t    nivel_bateria;

    module_info bms_ok;

}rx_bms_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de DCDC
 * 
 */
typedef struct 
{
    rx_var_t    voltaje_bateria;
    rx_var_t    t_max;

    module_info dcdc_ok;

}rx_dcdc_vars_t;


/**
 * @brief Definición tipo de estructura para variables decodificadas de Inversor
 * 
 */
typedef struct 
{
    rx_var_t    velocidad;
    rx_var_t    V;
    rx_var_t    I;
    rx_var_t    temp_max;
    rx_var_t    temp_motor;
    rx_var_t    potencia;

    module_info inversor_ok;

}rx_inversor_vars_t;


#endif /* _DECODE_DATA_H_ */