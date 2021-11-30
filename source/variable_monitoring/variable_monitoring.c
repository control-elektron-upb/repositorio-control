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
 * @brief Función principal de monitoreo de variables
 * 
 */
void variable_monitoring (void)
{

    /** Actualiza estado de las variables de BMS */
    bms_variable_monitoring(&Bms_States);

    /** Actualiza estado de las variables de DCDC */
    dcdc_variable_monitoring(&Dcdc_States);

    /** Actualiza estado de las variables de Inversor */
    inversor_variable_monitoring(&Inversor_States);
}


/**
 * @brief Monitoreo de las variables decodificadas del BMS
 * 
 * @param Bms_States Estructura con estados de las variables del BMS
 */
static void bms_variable_monitoring(bms_vars_states_t *p_Bms_States)
{
    p_Bms_States->voltaje = current_var_state(V_MAX_BMS, V_MIN_BMS, bus_data.Rx_Bms.voltaje);

    p_Bms_States->corriente = current_var_state(I_MAX_BMS, I_MIN_BMS, bus_data.Rx_Bms.corriente);
    
    p_Bms_States->voltaje_min_celda = current_var_state(P_MAX_BMS, P_MIN_BMS, bus_data.Rx_Bms.voltaje_min_celda);
    
    p_Bms_States->potencia = current_var_state(T_MAX_BMS, T_MIN_BMS, bus_data.Rx_Bms.potencia);
    
    p_Bms_States->t_max = current_var_state(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS, bus_data.Rx_Bms.t_max);
    
    p_Bms_States->nivel_bateria = current_var_state(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, bus_data.Rx_Bms.nivel_bateria);
}


/**
 * @brief Monitoreo de las variables decodificadas del DCDC
 * 
 * @param Dcdc_States Estructura con estados de las variables del DCDC
 */
static void dcdc_variable_monitoring(dcdc_vars_states_t *p_Dcdc_States)
{
    p_Dcdc_States->voltaje_bateria = current_var_state(V_BAT_MAX_DCDC, V_BAT_MIN_DCDC, bus_data.Rx_Dcdc.voltaje_bateria);
    
    p_Dcdc_States->t_max = current_var_state(T_MAX_DCDC, T_MIN_DCDC, bus_data.Rx_Dcdc.t_max);
    
}

/**
 * @brief Monitoreo de las variables decodificadas del Inversor
 * 
 * @param Inversor_States Estructura con estados de las variables del Inversor
 */
static void inversor_variable_monitoring(inversor_vars_states_t *p_Inversor_States)
{
    p_Inversor_States->velocidad = current_var_state(VEL_MAX_INV, VEL_MIN_INV, bus_data.Rx_Inversor.velocidad);

    p_Inversor_States->V = current_var_state(V_MAX_INV, V_MIN_INV, bus_data.Rx_Inversor.voltaje);
    
    p_Inversor_States->I = current_var_state(I_MAX_INV, I_MIN_INV, bus_data.Rx_Inversor.voltaje);
    
    p_Inversor_States->temp_max = current_var_state(T_MAX_INV, T_MIN_INV, bus_data.Rx_Inversor.temp_max);
    
    p_Inversor_States->temp_motor = current_var_state(T_MAX_MOTOR, T_MIN_MOTOR, bus_data.Rx_Inversor.temp_motor);
    
    p_Inversor_States->potencia = current_var_state(P_MAX_INV, P_MIN_INV, bus_data.Rx_Inversor.potencia);
}



/**
 * @brief Función de comparaciones
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @return var_state 
 */
static var_state comparaciones (float D_max, float D_min, float Data){

    if((Data < (D_max * (-REGULAR_ZONE + 1))) & (Data > (D_min*(REGULAR_ZONE + 1)))) {
        return OK; 

    }else if((Data > (D_max * (REGULAR_ZONE + 1))) | (Data < (D_min*(-REGULAR_ZONE + 1)))) {
        return PROBLEM; 

    }else if(((Data < (D_max * (REGULAR_ZONE + 1))) & (Data > (D_max * (-REGULAR_ZONE + 1))))  | 
    ((Data > (D_min*(-REGULAR_ZONE + 1))) & (Data < (D_min*(REGULAR_ZONE + 1))))){
        return REGULAR; 

    }else{
        return DATA_PROBLEM;

    }
}