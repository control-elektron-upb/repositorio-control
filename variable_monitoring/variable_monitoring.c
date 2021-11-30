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


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** @brief Estado por defecto de las variables */
#define DEFAULT_STATE       DATA_PROBLEM


/*******************************************************************************
 * Variables
 ******************************************************************************/

/** @brief Inicializa instancia de estructura de tipo bms_vars_states_t con los estados de las variables del BMS en DEFAULT_STATE */
static bms_vars_states_t        Bms_States = {DEFAULT_STATE};

/** @brief Inicializa instancia de estructura de tipo dcdc_vars_states_t con los estados de las variables del DCDC en DEFAULT_STATE */
static dcdc_vars_states_t       Dcdc_States = {DEFAULT_STATE};

/** @brief Inicializa instancia de estructura de tipo inversor_vars_states_t con los estados de las variables del inversor en DEFAULT_STATE */
static inversor_vars_states_t   Inversor_States = {DEFAULT_STATE};


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void Variable_Monitoring(void);    /* No es static, por lo que puede ser usada por otros archivos */

static void bms_variable_monitoring(bms_vars_states_t *p_Bms_States);
static void dcdc_variable_monitoring(dcdc_vars_states_t *p_Dcdc_States);
static void inversor_variable_monitoring(inversor_vars_states_t *p_Inversor_States);

static var_state current_var_state(rx_var_t D_max, rx_var_t D_min, rx_var_t Data);


/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief Función principal de monitoreo de variables
 * 
 *  Actualiza los estados de las variables decodificadas del BMS, DCDC e inversor.
 * 
 */
void Variable_Monitoring(void)
{
    bms_variable_monitoring(&Bms_States);               /* Actualiza estado de las variables del BMS */
    dcdc_variable_monitoring(&Dcdc_States);             /* Actualiza estado de las variables del DCDC */
    inversor_variable_monitoring(&Inversor_States);     /* Actualiza estado de las variables del inversor */
}


/**
 * @brief Monitoreo de las variables decodificadas del BMS
 * 
 * Actualiza los estados de las variables decodificadas del BMS de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en una estructura de tipo bms_vars_states_t.
 * 
 * @param p_Bms_States Puntero a estructura de tipo bms_vars_states_t que contiene los estados de las variables del BMS
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
 * Actualiza los estados de las variables decodificadas del DCDC de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo dcdc_vars_states_t.
 * 
 * @param p_Dcdc_States Puntero a estructura de tipo dcdc_vars_states_t que contiene los estados de las variables del DCDC
 */
static void dcdc_variable_monitoring(dcdc_vars_states_t *p_Dcdc_States)
{
    p_Dcdc_States->voltaje_bateria = current_var_state(V_BAT_MAX_DCDC, V_BAT_MIN_DCDC, bus_data.Rx_Dcdc.voltaje_bateria);
    
    p_Dcdc_States->t_max = current_var_state(T_MAX_DCDC, T_MIN_DCDC, bus_data.Rx_Dcdc.t_max);
}


/**
 * @brief Monitoreo de las variables decodificadas del inversor
 * 
 * Actualiza los estados de las variables decodificadas del inversor de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo inversor_vars_states_t.
 * 
 * @param p_Inversor_States Puntero a estructura de tipo inversor_vars_states_t que contiene los estados de las variables del inversor
 */
static void inversor_variable_monitoring(inversor_vars_states_t *p_Inversor_States)
{
    p_Inversor_States->velocidad = current_var_state(VEL_MAX_INV, VEL_MIN_INV, bus_data.Rx_Inversor.velocidad);

    p_Inversor_States->V = current_var_state(V_MAX_INV, V_MIN_INV, bus_data.Rx_Inversor.V);
    
    p_Inversor_States->I = current_var_state(I_MAX_INV, I_MIN_INV, bus_data.Rx_Inversor.I);
    
    p_Inversor_States->temp_max = current_var_state(T_MAX_INV, T_MIN_INV, bus_data.Rx_Inversor.temp_max);
    
    p_Inversor_States->temp_motor = current_var_state(T_MAX_MOTOR, T_MIN_MOTOR, bus_data.Rx_Inversor.temp_motor);
    
    p_Inversor_States->potencia = current_var_state(P_MAX_INV, P_MIN_INV, bus_data.Rx_Inversor.potencia);
}


/**
 * @brief Función para determinar el estado actual de la variable a evaluar
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @return var_state Estado actual de la variable
 */
static var_state current_var_state(rx_var_t D_max, rx_var_t D_min, rx_var_t Data)
{
    if((Data < (D_max * (-REGULAR_ZONE + 1))) & (Data > (D_min*(REGULAR_ZONE + 1)))) {
        return OK; 

    }else if((Data > (D_max * (REGULAR_ZONE + 1))) | (Data < (D_min*(-REGULAR_ZONE + 1)))) {
        return REGULAR; 

    }else if(((Data < (D_max * (REGULAR_ZONE + 1))) & (Data > (D_max * (-REGULAR_ZONE + 1))))  | 
    ((Data > (D_min*(-REGULAR_ZONE + 1))) & (Data < (D_min*(REGULAR_ZONE + 1))))){
        return PROBLEM; 

    }else{
        return DATA_PROBLEM;
    }
}

