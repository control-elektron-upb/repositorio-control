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

#include <stdint.h>

#include "buses/def_buses.h"
#include "buses/def_buses.c"

/** Porcentaje para zona regular (+/- 5% por defecto) */
#define REGULAR_ZONE     0.05


/** Valores mínimos y máximos del BMS */
#define V_MAX_BMS           0
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


/** Valores mínimos y máximos del DCDC */
#define V_BAT_MAX_DCDC      0
#define V_BAT_MIN_DCDC      0

#define T_MAX_DCDC          0
#define T_MIN_DCDC          0


/** Valores mínimos y máximos del Inversor*/
#define VEL_MAX_INV         0
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
    OK,
    REGULAR,
    PROBLEM,
    DATA_PROBLEM
} var_state;


/**
 * @brief Definición tipo de estructura para estado de las variables de BMS
 * 
 */
typedef struct
{
    var_state   voltaje;
    var_state   corriente;
    var_state   voltaje_min_celda;
    var_state   potencia;
    var_state   t_max;
    var_state   nivel_bateria;

}bms_vars_states_t;


/**
 * @brief Definición tipo de estructura para estado de las variables de DCDC
 * 
 */
typedef struct 
{
    var_state   voltaje_bateria;
    var_state   t_max;

}dcdc_vars_states_t;


/**
 * @brief Definición tipo de estructura para estado de las variables de Inversor
 * 
 */
typedef struct 
{
    var_state   velocidad;
    var_state   V;
    var_state   I;
    var_state   temp_max;
    var_state   temp_motor;
    var_state   potencia;

}inversor_vars_states_t;

#endif /* _VARIABLE_MONITORING_H_ */