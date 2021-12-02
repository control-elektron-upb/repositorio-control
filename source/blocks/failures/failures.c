/**
 * @file failures.c
 * @author Juan
 * @brief Implementación máquina de fallas
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "failures.h"

/*******************************************************************************
 * Private variables definitions
 ******************************************************************************/

/** @brief Estado de la máquina de estados */
static uint8_t Failures_state;

/** @brief Puntero a estructura de tipo st_bms_vars_t que contiene los estados de las variables del BMS */
static st_bms_vars_t *p_St_Bms = &bus_data.St_Bms;

/** @brief Puntero a estructura de tipo st_dcdc_vars_t que contiene los estados de las variables del DCDC */
static st_dcdc_vars_t *p_St_Dcdc = &bus_data.St_Dcdc;

/** @brief Puntero a estructura de tipo st_inversor_vars_t que contiene los estados de las variables del inversor */
static st_inversor_vars_t *p_St_Inversor = &bus_data.St_Inversor;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/

static var_state_t bms_current_status(void);

static var_state_t dcdc_current_status(void);

static var_state_t inversor_current_status(void);

static bool EV_AUTOKILL(void);

static void FAILURES_SM_Send_Failure(failure_t to_send, typedef_bus1_t *p_bus_data);

/*******************************************************************************
 * Public functions implementation
 ******************************************************************************/

void FAILURES_SM_Init(const uint8_t START_STATE)
{
    Failures_state = START_STATE;
}

void FAILURES_SM(void)
{
    switch (Failures_state)
    {
    case kOK:
        /* Actualiza falla a OK en bus_data */
        FAILURES_SM_Send_Failure(OK, &bus_data);

        if (EV_AUTOKILL()) {
            Failures_state = kAUTOKILL;
        }
        else if ( bms_current_status() == PROBLEM 
                || dcdc_current_status() == PROBLEM
                || inversor_current_status() == PROBLEM )
        {
            Failures_state = kCAUTION2;
        }
        else if ( bms_current_status() == REGULAR 
                || dcdc_current_status() == REGULAR 
                || inversor_current_status() == REGULAR )
        {
            Failures_state = kCAUTION1;
        }
        break;
    case kCAUTION1:
        /* Actualiza falla a CAUTION1 en bus_data */
        FAILURES_SM_Send_Failure(CAUTION1, &bus_data);

        if (EV_AUTOKILL) {
            Failures_state = kAUTOKILL;
        }
        else if ( bms_current_status() == PROBLEM 
                || dcdc_current_status() == PROBLEM
                || inversor_current_status() == PROBLEM )
        {
            Failures_state = kCAUTION2;
        }
        else if ( bms_current_status() == OK 
                && dcdc_current_status() == OK 
                && inversor_current_status() == OK )
        {
            Failures_state = kOK;
        }
        break;
    case kCAUTION2:
        /* Actualiza falla a CAUTION2 en bus_data */
        FAILURES_SM_Send_Failure(CAUTION2, &bus_data);

        if (EV_AUTOKILL) {
            Failures_state = kAUTOKILL;
        }
        else if ( (bms_current_status() == REGULAR || bms_current_status() == OK)
                && (dcdc_current_status() == REGULAR || dcdc_current_status() == OK)
                && (inversor_current_status() == REGULAR || inversor_current_status() == OK) )
        {
            Failures_state = kCAUTION1;
        }
        break;
    case kAUTOKILL:
        /* Actualiza falla a AUTOKILL en bus_data */
        FAILURES_SM_Send_Failure(AUTOKILL, &bus_data);
        /* Luego enviar mensaje de maxima prioridad CAN (¿cómo? ¿interrupciones?) */
        break;
    
    default:
        break;
    }
}

/*******************************************************************************
 * Private functions implementation
 ******************************************************************************/

/**
 * @brief Función de estado del módulo BMS 
 * 
 * A partir de los estados de las variables codificadas guardados en la estructura
 * St_Bms del bus_data, retorna el estado general del módulo BMS.
 * 
 * @return var_state_t Estado del módulo BMS
 */
static var_state_t bms_current_status(void)
{
    /* condicion OK */
    if ( p_St_Bms->voltaje == OK && p_St_Bms->corriente == OK 
            && p_St_Bms->voltaje_min_celda == OK && p_St_Bms->potencia == OK 
            && p_St_Bms->t_max == OK && p_St_Bms->nivel_bateria == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( p_St_Bms->nivel_bateria == REGULAR 
            || p_St_Bms->t_max == REGULAR
            || p_St_Bms->voltaje_min_celda == REGULAR
            || (p_St_Bms->voltaje == REGULAR && p_St_Bms->corriente == REGULAR && p_St_Bms->potencia == REGULAR) ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( p_St_Bms->voltaje == PROBLEM || p_St_Bms->corriente == PROBLEM 
            || p_St_Bms->voltaje_min_celda == PROBLEM || p_St_Bms->potencia == PROBLEM 
            || p_St_Bms->t_max == PROBLEM || p_St_Bms->nivel_bateria == PROBLEM ) 
    {
        return PROBLEM;
    }
}

/**
 * @brief Función de estado del módulo DCDC 
 * 
 * A partir de los estados de las variables codificadas guardados en la estructura
 * St_Dcdc del bus_data, retorna el estado general del módulo DCDC.
 * 
 * @return var_state_t Estado del módulo DCDC
 */
static var_state_t dcdc_current_status(void)
{
    /* condicion OK */
    if ( p_St_Dcdc->t_max == OK && p_St_Dcdc->voltaje_bateria == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( p_St_Dcdc->t_max == REGULAR || p_St_Dcdc->voltaje_bateria == REGULAR ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( p_St_Dcdc->t_max == PROBLEM || p_St_Dcdc->voltaje_bateria == PROBLEM ) 
    {
        return PROBLEM;
    }
}

/**
 * @brief Función de estado del módulo inversor 
 * 
 * A partir de los estados de las variables codificadas guardados en la estructura
 * St_Inversor del bus_data, retorna el estado general del módulo inversor.
 * 
 * @return var_state_t Estado del módulo inversor
 */
static var_state_t inversor_current_status(void)
{
    /* condicion OK */
    if ( p_St_Inversor->velocidad == OK && p_St_Inversor->V == OK 
            && p_St_Inversor->I == OK && p_St_Inversor->temp_max == OK 
            && p_St_Inversor->temp_motor == OK && p_St_Inversor->potencia == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( p_St_Inversor->velocidad == REGULAR 
            || p_St_Inversor->temp_max == REGULAR
            || p_St_Inversor->temp_motor == REGULAR
            || (p_St_Inversor->V == REGULAR && p_St_Inversor->I == REGULAR && p_St_Inversor->potencia == REGULAR) ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( p_St_Inversor->velocidad == PROBLEM || p_St_Inversor->V == PROBLEM 
            || p_St_Inversor->I == PROBLEM || p_St_Inversor->temp_max == PROBLEM 
            || p_St_Inversor->temp_motor == PROBLEM || p_St_Inversor->potencia == PROBLEM ) 
    {
        return PROBLEM;
    }
}

/**
 * @brief Condición para evento de AUTOKILL
 * 
 * @return true 
 * @return false 
 */
static bool EV_AUTOKILL(void)
{
    return (bms_current_status() == PROBLEM 
            && dcdc_current_status() == PROBLEM 
            && inversor_current_status() == PROBLEM 
            );
}

/**
 * @brief Envío de falla a bus de datos (bus_data)
 * 
 * @param to_send       Falla a enviar
 * @param p_bus_data    Puntero a estructura bus_data
 */
static void FAILURES_SM_Send_Failure(failure_t to_send, typedef_bus1_t *p_bus_data)
{
    p_bus_data->failure = to_send;
}