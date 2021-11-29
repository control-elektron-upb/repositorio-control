/**
 * @file variable_monitoring.h
 * @author Andrés
 * @brief Definiciones para monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _VARIABLE_MONITORING_H_
#define _VARIABLE_MONITORING_H_

#include "buses/def_buses.h"
#include "buses/def_buses.c"


/** @brief Porcentaje para zona regular (+/- 5% por defecto) */
#define REGULAR_ZONE     0.05


/** @brief Valor máximo de voltaje BMS */
#define V_MAX_BMS           0

/** @brief Valor mínimo de voltaje BMS */
#define V_MIN_BMS           0

#define I_MAX_BMS           0
#define I_MIN_BMS           0

#define P_MAX_BMS           0
#define P_MIN_BMS           0

#define T_MAX_BMS           0
#define T_MIN_BMS           0

#define V_CELDA_MAX_BMS     0
#define V_CELDA_MIN_BMS     0  

#define NIV_BAT_MAX_BMS     0
#define NIV_BAT_MIN_BMS     0


/** @brief Valor máximo de voltaje batería de DCDC */
#define V_BAT_MAX_DCDC      0

/** @brief Valor mínimo de voltaje batería de DCDC */
#define V_BAT_MIN_DCDC      0

#define T_MAX_DCDC          0
#define T_MIN_DCDC          0


/** @brief Valor máximo de velocidad de inversor */
#define VEL_MAX_INV         0

/** @brief Valor mínimo de velocidad de inversor */
#define VEL_MIN_INV         0

#define T_MAX_MOTOR         0
#define T_MIN_MOTOR         0

#define V_MAX_INV           0
#define V_MIN_INV           0

#define I_MAX_INV           0
#define I_MIN_INV           0

#define T_MAX_INV           0
#define T_MIN_INV           0

#define P_MAX_INV           0
#define P_MIN_INV           0


/**
 * @brief Función principal de monitoreo de variables
 * 
 */
void variable_monitoring (void);


/**
 * @brief Tipo de dato enum var_state para los estados de las variables
 * 
 */
typedef enum {
    OK,                 /**< Estado OK */
    REGULAR,            /**< Estado REGULAR */
    PROBLEM,            /**< Estado PROBLEM */
    DATA_PROBLEM        /**< Problema con el dato */
} var_state;


/**
 * @brief Definición tipo de estructura para estado de las variables del BMS
 * 
 */
typedef struct bms_vars_states_t
{
    var_state   voltaje;
    var_state   corriente;
    var_state   voltaje_min_celda;
    var_state   potencia;
    var_state   t_max;
    var_state   nivel_bateria;

}bms_vars_states_t;


/**
 * @brief Definición tipo de estructura para estado de las variables del DCDC
 * 
 */
typedef struct dcdc_vars_states_t
{
    var_state   voltaje_bateria;
    var_state   t_max;

}dcdc_vars_states_t;


/**
 * @brief Definición tipo de estructura para estado de las variables del inversor
 * 
 */
typedef struct inversor_vars_states_t
{
    var_state   velocidad;
    var_state   V;
    var_state   I;
    var_state   temp_max;
    var_state   temp_motor;
    var_state   potencia;

}inversor_vars_states_t;

#endif /* _VARIABLE_MONITORING_H_ */