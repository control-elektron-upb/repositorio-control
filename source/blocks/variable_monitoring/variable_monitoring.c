/**
 * @file variable_monitoring.c
 * @author Andrés
 * @brief Implementación monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "variable_monitoring.h"

/*******************************************************************************
 * Private variables definitions
 ******************************************************************************/

/** @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t *p_Rx_Peripherals = &bus_data.Rx_Peripherals;

/** @brief Puntero a estructura de tipo rx_bms_vars_t que contiene los valores de las variables decodificadas del BMS */
static rx_bms_vars_t *p_Rx_Bms = &bus_data.Rx_Bms;

/** @brief Puntero a estructura de tipo rx_dcdc_vars_t que contiene los valores de las variables decodificadas del DCDC */
static rx_dcdc_vars_t *p_Rx_Dcdc = &bus_data.Rx_Dcdc;

/** @brief Puntero a estructura de tipo rx_inversor_vars_t que contiene los valores de las variables decodificadas del inversor */
static rx_inversor_vars_t *p_Rx_Inversor = &bus_data.Rx_Inversor;

/** @brief Puntero a estructura de tipo st_bms_vars_t que contiene los estados de las variables del BMS */
static st_bms_vars_t *p_St_Bms = &bus_data.St_Bms;

/** @brief Puntero a estructura de tipo st_dcdc_vars_t que contiene los estados de las variables del DCDC */
static st_dcdc_vars_t *p_St_Dcdc = &bus_data.St_Dcdc;

/** @brief Puntero a estructura de tipo st_inversor_vars_t que contiene los estados de las variables del inversor */
static st_inversor_vars_t *p_St_Inversor = &bus_data.St_Inversor;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/

static void bms_variable_monitoring(void);
static void dcdc_variable_monitoring(void);
static void inversor_variable_monitoring(void);

static var_state_t current_var_state(rx_var_t D_max, rx_var_t D_min, rx_var_t Data);

/*******************************************************************************
 * Public functions implementation
 ******************************************************************************/

/**
 * @brief Función principal de monitoreo de variables
 * 
 * Determina los estados de las variables decodificadas del BMS, DCDC e inversor y
 * los guarda en una estructura de tipo st_bms_vars_t. No es static, por lo que 
 * puede ser usada por otros archivos.
 * 
 */
void variable_Monitoring(void)
{
    bms_variable_monitoring();      /* Actualiza estado de las variables del BMS */
    dcdc_variable_monitoring();     /* Actualiza estado de las variables del DCDC */
    inversor_variable_monitoring(); /* Actualiza estado de las variables del inversor */
}

/*******************************************************************************
 * Private functions implementation
 ******************************************************************************/

/**
 * @brief Monitoreo de las variables decodificadas del BMS
 * 
 * Actualiza los estados de las variables decodificadas del BMS de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en una estructura de tipo st_bms_vars_t.
 * 
 */
static void bms_variable_monitoring()
{
    p_St_Bms->voltaje = current_var_state(V_MAX_BMS, V_MIN_BMS, p_Rx_Bms->voltaje);

    p_St_Bms->corriente = current_var_state(I_MAX_BMS, I_MIN_BMS, p_Rx_Bms->corriente);

    p_St_Bms->voltaje_min_celda = current_var_state(P_MAX_BMS, P_MIN_BMS, p_Rx_Bms->voltaje_min_celda);

    p_St_Bms->potencia = current_var_state(T_MAX_BMS, T_MIN_BMS, p_Rx_Bms->potencia);

    p_St_Bms->t_max = current_var_state(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS, p_Rx_Bms->t_max);

    p_St_Bms->nivel_bateria = current_var_state(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, p_Rx_Bms->nivel_bateria);
}

/**
 * @brief Monitoreo de las variables decodificadas del DCDC
 * 
 * Actualiza los estados de las variables decodificadas del DCDC de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo st_dcdc_vars_t.
 * 
 */
static void dcdc_variable_monitoring()
{
    p_St_Dcdc->voltaje_bateria = current_var_state(V_BAT_MAX_DCDC, V_BAT_MIN_DCDC, p_Rx_Dcdc->voltaje_bateria);

    p_St_Dcdc->t_max = current_var_state(T_MAX_DCDC, T_MIN_DCDC, p_Rx_Dcdc->t_max);
}

/**
 * @brief Monitoreo de las variables decodificadas del inversor
 * 
 * Actualiza los estados de las variables decodificadas del inversor de acuerdo a sus valores actuales, 
 * límites máximo y mínimo y porcentaje de zona regular. Dichos estados son guardados por referencia
 * en la estructura de tipo st_inversor_vars_t.
 * 
 */
static void inversor_variable_monitoring()
{
    p_St_Inversor->velocidad = current_var_state(VEL_MAX_INV, VEL_MIN_INV, p_Rx_Inversor->velocidad);

    p_St_Inversor->V = current_var_state(V_MAX_INV, V_MIN_INV, p_Rx_Inversor->V);

    p_St_Inversor->I = current_var_state(I_MAX_INV, I_MIN_INV, p_Rx_Inversor->I);

    p_St_Inversor->temp_max = current_var_state(T_MAX_INV, T_MIN_INV, p_Rx_Inversor->temp_max);

    p_St_Inversor->temp_motor = current_var_state(T_MAX_MOTOR, T_MIN_MOTOR, p_Rx_Inversor->temp_motor);

    p_St_Inversor->potencia = current_var_state(P_MAX_INV, P_MIN_INV, p_Rx_Inversor->potencia);
}

/**
 * @brief Función para determinar el estado actual de la variable a evaluar
 * 
 * @param D_max Valor máximo de la variable
 * @param D_min Valor mínimo de la variable
 * @param Data  Valor actual de la variable 
 * @return var_state_t Estado actual de la variable
 */
static var_state_t current_var_state(rx_var_t D_max, rx_var_t D_min, rx_var_t Data)
{
    if ((Data < (D_max * (-REGULAR_ZONE + 1))) && (Data > (D_min * (REGULAR_ZONE + 1))))
    {
        return OK;
    }
    else if ((Data > (D_max * (REGULAR_ZONE + 1))) || (Data < (D_min * (-REGULAR_ZONE + 1))))
    {
        return REGULAR;
    }
    else if (((Data < (D_max * (REGULAR_ZONE + 1))) && (Data > (D_max * (-REGULAR_ZONE + 1)))) ||
             ((Data > (D_min * (-REGULAR_ZONE + 1))) && (Data < (D_min * (REGULAR_ZONE + 1)))))
    {
        return PROBLEM;
    }
    else
    {
        return DATA_PROBLEM;
    }
}

//matriz de los valores de las variables

int i,j;
int Value_buffer = 3;
char buffer[20,20];
for(i=0;i++;i==13){
    for(j=0;j++;j==buffer_memoria){
        buffer[i,j]
    }
}
/*
// V_bms -> buffer[1,0]
//
//if value buffer=3
[ OK PROBLEM OK]
//if(OK>PROBLEM){
    return OK;

}*/