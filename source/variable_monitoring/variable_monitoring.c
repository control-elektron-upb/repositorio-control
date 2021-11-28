/**
 * @file variable_monitoring.c
 * @author Andrés
 * @brief Monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "variable_monitoring.h"


/** Estado por defecto de las variables */
#define DEFAULT_STATE       DATA_PROBLEM

/** Inicializa la estructura con los estados de las variables del BMS en DEFAULT_STATE */
bms_vars_states_t       Bms_States = {DEFAULT_STATE};

/** Inicializa la estructura con los estados de las variables del DCDC en DEFAULT_STATE */
dcdc_vars_states_t      Dcdc_States = {DEFAULT_STATE};

/** Inicializa la estructura con los estados de las variables del Inversor en DEFAULT_STATE */
inversor_vars_states_t  Inversor_States = {DEFAULT_STATE};


/**
 * @brief Función principal de monitoreo de variables
 * 
 */
void variable_monitoring (void)
{

    /** Actualiza estado de las variables de BMS */
    bms_variable_monitoring(&Bms_States);

    /** Actualiza estado de las variables de DCDC */
    //dcdc_variable_monitoring(&Dcdc_States);

    /** Actualiza estado de las variables de Inversor */
    //inversor_variable_monitoring(&Inversor_States);
}


/**
 * @brief Monitoreo de las variables decodificadas del BMS
 * 
 * @param Bms_States Estructura con estados de las variables del BMS
 */
static void bms_variable_monitoring(bms_vars_states_t* Bms_States)
{
    Bms_States->voltaje = current_var_state(V_MAX_BMS, V_MIN_BMS, bus_data.Rx_Bms.voltaje, REGULAR_ZONE, Bms_States->voltaje);

    Bms_States->corriente = current_var_state(I_MAX_BMS, I_MIN_BMS, bus_data.Rx_Bms.corriente, REGULAR_ZONE, Bms_States->corriente);
    
    Bms_States->voltaje_min_celda = current_var_state(P_MAX_BMS, P_MIN_BMS, bus_data.Rx_Bms.voltaje_min_celda, REGULAR_ZONE, Bms_States->voltaje_min_celda);
    
    Bms_States->potencia = current_var_state(T_MAX_BMS, T_MIN_BMS, bus_data.Rx_Bms.potencia, REGULAR_ZONE, Bms_States->potencia);
    
    Bms_States->t_max = current_var_state(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS, bus_data.Rx_Bms.t_max, REGULAR_ZONE, Bms_States->t_max);
    
    Bms_States->nivel_bateria = current_var_state(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, bus_data.Rx_Bms.nivel_bateria, REGULAR_ZONE, Bms_States->nivel_bateria);
}


/**
 * @brief Monitoreo de las variables decodificadas del DCDC
 * 
 * @param Dcdc_States Estructura con estados de las variables del DCDC
 */


/**
 * @brief Monitoreo de las variables decodificadas del Inversor
 * 
 * @param Inversor_States Estructura con estados de las variables del Inversor
 */


/**
 * @brief Función para determinar el estado actual de la variable a evaluar
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @param reg_percent Porcentaje de zona regular
 * @return var_state Estado actual de la variable
 */
static var_state current_var_state(float D_max, float D_min, float Data, float reg_percent, var_state current_state)
{
    if(current_state == DATA_PROBLEM){
        return DATA_PROBLEM;
    }else{
        var_state resultado;
        resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
        return resultado;
    }
}


/**
 * @brief Función de comparaciones
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @param reg_percent Porcentaje de zona regular
 * @return var_state 
 */
static var_state comparaciones (float D_max, float D_min, float Data, float reg_percent){

    if((Data < (D_max * (-reg_percent + 1))) & (Data > (D_min*(reg_percent + 1)))) {
        return OK; 

    }else if((Data > (D_max * (reg_percent + 1))) | (Data < (D_min*(-reg_percent + 1)))) {
        return REGULAR; 

    }else if(((Data < (D_max * (reg_percent + 1))) & (Data > (D_max * (-reg_percent + 1))))  | 
    ((Data > (D_min*(-reg_percent + 1))) & (Data < (D_min*(reg_percent + 1))))){
        return PROBLEM; 

    }else{
        return DATA_PROBLEM;

    }
}