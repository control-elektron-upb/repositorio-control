/**
 * @file variable_monitoring.h
 * @author Andrés
 * @brief Declaraciones monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _VARIABLE_MONITORING_H_
#define _VARIABLE_MONITORING_H_

#include "def_buses.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/

/** @brief Porcentaje para zona regular (+/- 5% por defecto) */
#define REGULAR_ZONE 0.05

/** @brief Valor máximo voltaje BMS */
#define V_MAX_BMS 0

/** @brief Valor mínimo voltaje BMS */
#define V_MIN_BMS 0

/** @brief Valor máximo corriente BMS */
#define I_MAX_BMS 0

/** @brief Valor mínimo corriente BMS */
#define I_MIN_BMS 0

/** @brief Valor máximo potencia BMS */
#define P_MAX_BMS 0

/** @brief Valor mínimo potencia BMS */
#define P_MIN_BMS 0

/** @brief Valor máximo temperatura BMS */
#define T_MAX_BMS 0

/** @brief Valor mínimo temperatura BMS */
#define T_MIN_BMS 0

/** @brief Valor máximo voltaje celda BMS */
#define V_CELDA_MAX_BMS 0

/** @brief Valor mínimo voltaje celda BMS */
#define V_CELDA_MIN_BMS 0

/** @brief Valor máximo nivel batería BMS */
#define NIV_BAT_MAX_BMS 0

/** @brief Valor mínimo nivel batería BMS */
#define NIV_BAT_MIN_BMS 0

/** @brief Valor máximo voltaje batería DCDC */
#define V_BAT_MAX_DCDC 0

/** @brief Valor mínimo voltaje batería DCDC */
#define V_BAT_MIN_DCDC 0

/** @brief Valor máximo voltaje batería DCDC */
#define V_OUT_MAX_DCDC 0

/** @brief Valor mínimo voltaje batería DCDC */
#define V_OUT_MIN_DCDC 0

/** @brief Valor máximo voltaje batería DCDC */
#define P_MAX_DCDC 0

/** @brief Valor mínimo voltaje batería DCDC */
#define P_MIN_DCDC 0

/** @brief Valor máximo temperatura DCDC*/
#define T_MAX_DCDC 0

/** @brief Valor mínimo temperatura DCDC*/
#define T_MIN_DCDC 0

/** @brief Valor máximo velocidad inversor */
#define VEL_MAX_INV 0

/** @brief Valor mínimo velocidad inversor */
#define VEL_MIN_INV 0

/** @brief Valor máximo temperatura motor */
#define T_MAX_MOTOR 0

/** @brief Valor mínimo temperatura motor */
#define T_MIN_MOTOR 0

/** @brief Valor máximo voltaje inversor */
#define V_MAX_INV 0

/** @brief Valor mínimo voltaje inversor */
#define V_MIN_INV 0

/** @brief Valor máximo corriente inversor */
#define I_MAX_INV 0

/** @brief Valor mínimo corriente inversor */
#define I_MIN_INV 0

/** @brief Valor máximo temperatura inversor */
#define T_MAX_INV 0

/** @brief Valor mínimo temperatura inversor */
#define T_MIN_INV 0

/** @brief Valor máximo potencia inversor */
#define P_MAX_INV 0

/** @brief Valor mínimo potencia inversor */
#define P_MIN_INV 0

/*******************************************************************************
 * Types declarations
 ******************************************************************************/

/**
 * @brief Tipo de dato enum var_state_t para los estados de las variables
 * 
 */
typedef enum
{
    OK,          /**< Estado OK */
    REGULAR,     /**< Estado REGULAR */
    PROBLEM,     /**< Estado PROBLEM */
    DATA_PROBLEM /**< Problema con el dato */
} var_state_t;

/**
 * @brief Tipo de estructura para estado de las variables del BMS
 * 
 */
typedef struct st_bms_vars_t
{
    var_state_t voltaje;
    var_state_t corriente;
    var_state_t voltaje_min_celda;
    var_state_t potencia;
    var_state_t t_max;
    var_state_t nivel_bateria;

} st_bms_vars_t;

/**
 * @brief Tipo de estructura para estado de las variables del DCDC
 * 
 */
typedef struct st_dcdc_vars_t
{
    var_state_t voltaje_bateria;
    var_state_t voltaje_salida;
    var_state_t potencia;
    var_state_t t_max;

} st_dcdc_vars_t;

/**
 * @brief Tipo de estructura para estado de las variables del inversor
 * 
 */
typedef struct st_inversor_vars_t
{
    var_state_t velocidad;
    var_state_t V;
    var_state_t I;
    var_state_t temp_max;
    var_state_t temp_motor;
    var_state_t potencia;

} st_inversor_vars_t;

/*******************************************************************************
 * Public function prototypes
 ******************************************************************************/

/**
 * @brief Función principal de monitoreo de variables
 * 
 * Determina los estados de las variables decodificadas del BMS, DCDC e inversor y
 * los guarda en una estructura de tipo st_bms_vars_t. No es static, por lo que 
 * puede ser usada por otros archivos.
 * 
 */
void variable_Monitoring(void);

#endif /* _VARIABLE_MONITORING_H_ */