/**
 * @file failures.c
 * @author Juan
 * @brief Implementación máquinas de fallas
 * @version 0.1
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "failures.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Estado de la máquina de estados */
static uint8_t failures_state = kCAUTION1;

/** @brief Puntero a estructura de tipo st_bms_vars_t que contiene los estados de las variables del BMS */
static st_bms_vars_t* p_St_Bms = &bus_data.St_Bms;

/** @brief Puntero a estructura de tipo st_dcdc_vars_t que contiene los estados de las variables del DCDC */
static st_dcdc_vars_t* p_St_Dcdc = &bus_data.St_Dcdc;

/** @brief Puntero a estructura de tipo st_inversor_vars_t que contiene los estados de las variables del inversor */
static st_inversor_vars_t* p_St_Inversor = &bus_data.St_Inversor;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void Failures_StateMachine(void);

static void Failures_Get_ModulesStatus(void);

static void Failures_Send_Failure(failure_t to_send, typedef_bus1_t* p_bus_data);

static void Failures_Send_Failure_CAN(failure_t to_send, typedef_bus2_t* p_bus_can_output);

static void Failures_Send_Autokill_CAN(typedef_bus2_t* p_bus_can_output);

static bool Failures_Autokill_Event(void);

static var_state_t bms_current_status(void);

static var_state_t dcdc_current_status(void);

static var_state_t inversor_current_status(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de fallas.
 *
 * Determina estado general de cada uno de los modulos segun el estado de las
 * variables decodificadas. 
 * 
 * Llama a la función máquina de estados de fallas.
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param None
 * @retval None
 */
void FAILURES(void)
{
    Failures_Get_ModulesStatus();
    Failures_StateMachine();
}

/**
 * @brief Lee estado de la máquina de estados de fallas.
 *
 * Lee estado de la máquina de estados de fallas. No es static, por lo que puede ser
 * usada por otros archivos.
 *
 * @param None
 * @return uint8_t Estado de la máquina de estados
 */
uint8_t FAILURES_GetState(void)
{
    return failures_state;
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

 /**
  * @brief Función máquina de estado de fallas
  *
  * Se encarga de realizar transiciones entre diferentes fallas de acuerdo al estado
  * de las variables del vehículo, con ello establece el tope de modo de manejo. Más
  * especificamente, la máquina de fallas verifica el estado general de los módulos BMS,
  * DCDC e inversor y conforme a ello realiza las transiciones entre las diferentes fallas
  * posibles: OK, CAUTION1, CAUTION2, y AUTOKILL.
  *
  * Lee la variable bms_status, dcdc_status e inversor_status de las estructuras de estado de
  * las variables decodificadas St_Bms, St_Dcdc, y St_Inversor.
  *
  * Escribe en la variable failure del bus_data.
  *
  */
static void Failures_StateMachine(void)
{
    switch (failures_state)
    {
    case kOK:

        /* Actualiza falla a OK en bus_data */
        Failures_Send_Failure(OK, &bus_data);

        if (Failures_Autokill_Event()) {
            failures_state = kAUTOKILL;
        }
        else if (p_St_Bms->bms_status == kVarState_PROBLEM
            || p_St_Dcdc->dcdc_status == kVarState_PROBLEM
            || p_St_Inversor->inversor_status == kVarState_PROBLEM)
        {
            failures_state = kCAUTION2;
        }
        else if (p_St_Bms->bms_status == kVarState_REGULAR
            || p_St_Dcdc->dcdc_status == kVarState_REGULAR
            || p_St_Inversor->inversor_status == kVarState_REGULAR)
        {
            failures_state = kCAUTION1;
        }
        break;

    case kCAUTION1:

        /* Actualiza falla a CAUTION1 en bus_data */
        Failures_Send_Failure(CAUTION1, &bus_data);

        if (Failures_Autokill_Event()) {
            failures_state = kAUTOKILL;
        }
        else if (p_St_Bms->bms_status == kVarState_PROBLEM
            || p_St_Dcdc->dcdc_status == kVarState_PROBLEM
            || p_St_Inversor->inversor_status == kVarState_PROBLEM)
        {
            failures_state = kCAUTION2;
        }
        else if (p_St_Bms->bms_status == kVarState_OK
            && p_St_Dcdc->dcdc_status == kVarState_OK
            && p_St_Inversor->inversor_status == kVarState_OK)
        {
            failures_state = kOK;
        }
        break;

    case kCAUTION2:

        /* Actualiza falla a CAUTION2 en bus_data */
        Failures_Send_Failure(CAUTION2, &bus_data);

        if (Failures_Autokill_Event()) {
            failures_state = kAUTOKILL;
        }
        else if ((p_St_Bms->bms_status == kVarState_REGULAR || p_St_Bms->bms_status == kVarState_OK)
            && (p_St_Dcdc->dcdc_status == kVarState_REGULAR || p_St_Dcdc->dcdc_status == kVarState_OK)
            && (p_St_Inversor->inversor_status == kVarState_REGULAR || p_St_Inversor->inversor_status == kVarState_OK))
        {
            failures_state = kCAUTION1;
        }
        break;

    case kAUTOKILL:

        /* Actualiza falla a AUTOKILL en bus_data */
        Failures_Send_Failure(AUTOKILL, &bus_data);
        /* Luego actualiza variable autokill en bus de salida can y enviar mensaje de maxima prioridad CAN (¿cómo? ¿interrupciones?) */
        Failures_Send_Autokill_CAN(&bus_can_output);
        break;

    default:
        break;
    }
}

/**
 * @brief Función estado general de los modulos
 *
 * A partir de los estados de las variables codificadas guardados en la estructuras
 * St_Bms, St_Dcdc, St_Inversor, que se encuentran en el bus_data, retorna el estado
 * general de los modulos de BMS, DCDC, e inversor.
 *
 */
static void Failures_Get_ModulesStatus(void)
{
    bms_current_status();
    dcdc_current_status();
    inversor_current_status();
}

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
    /* condición OK */
    if (p_St_Bms->voltaje == kVarState_OK && p_St_Bms->corriente == kVarState_OK
        && p_St_Bms->voltaje_min_celda == kVarState_OK && p_St_Bms->potencia == kVarState_OK
        && p_St_Bms->t_max == kVarState_OK && p_St_Bms->nivel_bateria == kVarState_OK)
    {
        return kVarState_OK;
    }

    /* condición REGULAR */
    else if (p_St_Bms->nivel_bateria == kVarState_REGULAR
        || p_St_Bms->t_max == kVarState_REGULAR
        || p_St_Bms->voltaje_min_celda == kVarState_REGULAR
        || (p_St_Bms->voltaje == kVarState_REGULAR && p_St_Bms->corriente == kVarState_REGULAR && p_St_Bms->potencia == kVarState_REGULAR))
    {
        return kVarState_REGULAR;
    }

    /* condición PROBLEM */
    else if (p_St_Bms->voltaje == kVarState_PROBLEM || p_St_Bms->corriente == kVarState_PROBLEM
        || p_St_Bms->voltaje_min_celda == kVarState_PROBLEM || p_St_Bms->potencia == kVarState_PROBLEM
        || p_St_Bms->t_max == kVarState_PROBLEM || p_St_Bms->nivel_bateria == kVarState_PROBLEM)
    {
        return kVarState_PROBLEM;
    }

    /* condición DATA PROBLEM */
    else
    {
        return kVarState_DATA_PROBLEM;
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
    /* condición OK */
    if (p_St_Dcdc->t_max == kVarState_OK && p_St_Dcdc->voltaje_bateria == kVarState_OK)
    {
        return kVarState_OK;
    }

    /* condición REGULAR */
    else if (p_St_Dcdc->t_max == kVarState_REGULAR || p_St_Dcdc->voltaje_bateria == kVarState_REGULAR)
    {
        return kVarState_REGULAR;
    }

    /* condición PROBLEM */
    else if (p_St_Dcdc->t_max == kVarState_PROBLEM || p_St_Dcdc->voltaje_bateria == kVarState_PROBLEM)
    {
        return kVarState_PROBLEM;
    }
    
    /* condición DATA PROBLEM */
    else
    {
        return kVarState_DATA_PROBLEM;
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
    /* condición OK */
    if (p_St_Inversor->velocidad == kVarState_OK && p_St_Inversor->V == kVarState_OK
        && p_St_Inversor->I == kVarState_OK && p_St_Inversor->temp_max == kVarState_OK
        && p_St_Inversor->temp_motor == kVarState_OK && p_St_Inversor->potencia == kVarState_OK)
    {
        return kVarState_OK;
    }

    /* condición REGULAR */
    else if (p_St_Inversor->velocidad == kVarState_REGULAR
        || p_St_Inversor->temp_max == kVarState_REGULAR
        || p_St_Inversor->temp_motor == kVarState_REGULAR
        || (p_St_Inversor->V == kVarState_REGULAR && p_St_Inversor->I == kVarState_REGULAR && p_St_Inversor->potencia == kVarState_REGULAR))
    {
        return kVarState_REGULAR;
    }

    /* condición PROBLEM */
    else if (p_St_Inversor->velocidad == kVarState_PROBLEM || p_St_Inversor->V == kVarState_PROBLEM
        || p_St_Inversor->I == kVarState_PROBLEM || p_St_Inversor->temp_max == kVarState_PROBLEM
        || p_St_Inversor->temp_motor == kVarState_PROBLEM || p_St_Inversor->potencia == kVarState_PROBLEM)
    {
        return kVarState_PROBLEM;
    }

    /* condición DATA PROBLEM */
    else
    {
        return kVarState_DATA_PROBLEM;
    }

}

/**
 * @brief Condición para evento de AUTOKILL
 *
 * @return true Se cumple condición autokill
 * @return false No se cumple condición autokill
 */
static bool Failures_Autokill_Event(void)
{
    bool is_autokill = false;

    /* Todos los módulos en PROBLEM */
    is_autokill = (p_St_Bms->bms_status == kVarState_PROBLEM
        && p_St_Dcdc->dcdc_status == kVarState_PROBLEM
        && p_St_Inversor->inversor_status == kVarState_PROBLEM);

    return is_autokill;
}

/**
 * @brief Envío de falla a bus de datos
 *
 * @param to_send               Falla a enviar
 * @param p_bus_can_output      Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 */
static void Failures_Send_Failure(failure_t to_send, typedef_bus1_t* p_bus_data)
{
    p_bus_data->failure = to_send;
}

/**
 * @brief Envío de falla a bus de salida CAN
 *
 * @param to_send               Falla a enviar
 * @param p_bus_can_output      Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void Failures_Send_Failure_CAN(failure_t to_send, typedef_bus2_t* p_bus_can_output)
{
    p_bus_can_output->estado_falla = to_send;
}

/**
 * @brief Envío de evento autokill a bus de salida CAN
 *
 * @param p_bus_can_output      Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void Failures_Send_Autokill_CAN(typedef_bus2_t* p_bus_can_output)
{
    p_bus_can_output->autokill = 0x01;
}
