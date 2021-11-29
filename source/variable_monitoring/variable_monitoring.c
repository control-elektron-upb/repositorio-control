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


/**
 * @brief Estado por defecto de las variables
 * 
 */
#define DEFAULT_STATE       DATA_PROBLEM

/**
 * @brief Inicializa instancia de estructura de tipo bms_vars_states_t con los estados de las variables del BMS en DEFAULT_STATE
 * 
 */
bms_vars_states_t       Bms_States = {DEFAULT_STATE};

/**
 * @brief Inicializa instancia de estructura de tipo dcdc_vars_states_t con los estados de las variables del DCDC en DEFAULT_STATE
 * 
 */
dcdc_vars_states_t      Dcdc_States = {DEFAULT_STATE};

/**
 * @brief Inicializa instancia de estructura de tipo inversor_vars_states_t con los estados de las variables del inversor en DEFAULT_STATE
 * 
 */
inversor_vars_states_t  Inversor_States = {DEFAULT_STATE};


/**
 * @brief Función principal de monitoreo de variables
 * 
 */
void Variable_Monitoring (void)
{
    bms_variable_monitoring(&Bms_States);               
    //dcdc_variable_monitoring(&Dcdc_States);      
    //inversor_variable_monitoring(&Inversor_States);
}


/**
 * @brief Monitoreo de las variables decodificadas del BMS
 * 
 * Actualiza estados de las variables decodificadas del BMS de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en una estructura de tipo bms_vars_states_t.
 * 
 * @param p_Bms_States Puntero a estructura de tipo bms_vars_states_t que contiene los estados de las variables del BMS
 */
static void bms_variable_monitoring(bms_vars_states_t *p_Bms_States)
{
    p_Bms_States->voltaje = current_var_state(V_MAX_BMS, V_MIN_BMS, bus_data.Rx_Bms.voltaje, REGULAR_ZONE, p_Bms_States->voltaje);

    p_Bms_States->corriente = current_var_state(I_MAX_BMS, I_MIN_BMS, bus_data.Rx_Bms.corriente, REGULAR_ZONE, p_Bms_States->corriente);
    
    p_Bms_States->voltaje_min_celda = current_var_state(P_MAX_BMS, P_MIN_BMS, bus_data.Rx_Bms.voltaje_min_celda, REGULAR_ZONE, p_Bms_States->voltaje_min_celda);
    
    p_Bms_States->potencia = current_var_state(T_MAX_BMS, T_MIN_BMS, bus_data.Rx_Bms.potencia, REGULAR_ZONE, p_Bms_States->potencia);
    
    p_Bms_States->t_max = current_var_state(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS, bus_data.Rx_Bms.t_max, REGULAR_ZONE, p_Bms_States->t_max);
    
    p_Bms_States->nivel_bateria = current_var_state(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, bus_data.Rx_Bms.nivel_bateria, REGULAR_ZONE, p_Bms_States->nivel_bateria);
}


/**
 * @brief Monitoreo de las variables decodificadas del DCDC
 * 
 * Actualiza estados de las variables decodificadas del DCDC de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo dcdc_vars_states_t.
 * 
 * @param p_Dcdc_States Puntero a estructura de tipo dcdc_vars_states_t que contiene los estados de las variables del DCDC
 */
static void dcdc_variable_monitoring(dcdc_vars_states_t *p_Dcdc_States)
{
    asm("nop");
}


/**
 * @brief Monitoreo de las variables decodificadas del inversor
 * 
 * Actualiza estados de las variables decodificadas del inversor de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo inversor_vars_states_t.
 * 
 * @param p_Inversor_States Puntero a estructura de tipo inversor_vars_states_t que contiene los estados de las variables del inversor
 */
static void inversor_variable_monitoring(inversor_vars_states_t *p_Inversor_States)
{
    asm("nop");
}


/**
 * @brief Función para determinar el estado actual de la variable a evaluar
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @param reg_percent Porcentaje de zona regular
 * @return var_state Estado actual de la variable
 */
static var_state current_var_state(rx_var_t D_max, rx_var_t D_min, rx_var_t Data, rx_var_t reg_percent, var_state current_state)
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
 * @return var_state Estado actual de la variable
 */
static var_state comparaciones (rx_var_t D_max, rx_var_t D_min, rx_var_t Data, rx_var_t reg_percent){

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