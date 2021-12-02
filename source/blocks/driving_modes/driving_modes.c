/**
 * @file driving_modes.c
 * @author Juan
 * @brief Implementación máquina modos de manejo
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "driving_modes.h"

/*******************************************************************************
 * Private variables definitions
 ******************************************************************************/

/** @brief Estado de la máquina de estados */
static uint8_t Driving_Modes_state;

/** @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t *p_Rx_Peripherals = &bus_data.Rx_Peripherals;

/** @brief Puntero a estructura de tipo rx_bms_vars_t que contiene los valores de las variables decodificadas del BMS */
static rx_bms_vars_t *p_Rx_Bms = &bus_data.Rx_Bms;

/** @brief Puntero a estructura de tipo rx_dcdc_vars_t que contiene los valores de las variables decodificadas del DCDC */
static rx_dcdc_vars_t *p_Rx_Dcdc = &bus_data.Rx_Dcdc;

/** @brief Puntero a estructura de tipo rx_inversor_vars_t que contiene los valores de las variables decodificadas del inversor */
static rx_inversor_vars_t *p_Rx_Inversor = &bus_data.Rx_Inversor;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/

static void DRIVING_MODES_SM_Send_Driving_Mode(driving_mode_t to_send, typedef_bus1_t *p_bus_data);

static bool DRIVING_MODES_SM_Echo_Wait_Response(void);

static void DRIVING_MODES_SM_Echo_Send(void);

/*******************************************************************************
 * Public functions implementation
 ******************************************************************************/

void DRIVING_MODES_SM_Init(const uint8_t START_STATE)
{
    Driving_Modes_state = START_STATE;
}

void DRIVING_MODES_SM(void)
{
    switch (Driving_Modes_state)
    {
    case kINIT:
        /* Espera confirmación de los demás módulos */
        if (DRIVING_MODES_SM_Echo_Wait_Response())
            Driving_Modes_state = kNORMAL;
        break;

    case kECO:
        /* Actualiza modo de manejo a ECO en bus_data */
        DRIVING_MODES_SM_Send_Driving_Mode(ECO, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == NORMAL && (bus_data.failure == OK || bus_data.failure == CAUTION1))
        {
            Driving_Modes_state = kNORMAL;
        }
        else if (p_Rx_Peripherals->buttons_change_state == SPORT && bus_data.failure == OK)
        {
            Driving_Modes_state = kSPORT;
        }
        break;

    case kNORMAL:
        /* Actualiza modo de manejo a NORMAL en bus_data */
        DRIVING_MODES_SM_Send_Driving_Mode(NORMAL, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == ECO || bus_data.failure == CAUTION2)
        {
            Driving_Modes_state = kECO;
        }
        else if (p_Rx_Peripherals->buttons_change_state == SPORT && bus_data.failure == OK)
        {
            Driving_Modes_state = kSPORT;
        }
        break;

    case kSPORT:
        /* Actualiza modo de manejo a SPORT en bus_data */
        DRIVING_MODES_SM_Send_Driving_Mode(SPORT, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == ECO || bus_data.failure == CAUTION2)
        {
            Driving_Modes_state = kECO;
        }
        else if (p_Rx_Peripherals->buttons_change_state == NORMAL || bus_data.failure == CAUTION1)
        {
            Driving_Modes_state = kSPORT;
        }
        break;

    default:
        break;
    }
}

/*******************************************************************************
 * Private functions implementation
 ******************************************************************************/

/**
 * @brief Envío de modo de manejo al bus de datos (bus_data)
 * 
 * @param to_send       Modo de manejo a enviar
 * @param p_bus_data    Puntero a estructura bus_data
 */
static void DRIVING_MODES_SM_Send_Driving_Mode(driving_mode_t to_send, typedef_bus1_t *p_bus_data)
{
    p_bus_data->driving_mode = to_send;
}
/**
 * @brief Realiza echo, espera confirmación respuesta de los demás módulos
 * 
 * @return true 
 * @return false 
 */
static bool DRIVING_MODES_SM_Echo_Wait_Response()
{
    DRIVING_MODES_SM_Echo_Send();
    while (1)
    {
        /* Si todos los módulos OK ... */
        if (p_Rx_Peripherals->peripherals_ok == OK && p_Rx_Bms->bms_ok == OK && p_Rx_Dcdc->dcdc_ok == OK && p_Rx_Inversor->inversor_ok == OK
            /*&& time_out*/)
            break;
    }
    return IM_READY;
}

/**
 * @brief Realiza echo a los demás módulos
 * 
 * Se envía por la dirección CAN 0x014 (control_ok) el valor 0x01 un segundo después 
 * de encenderse, despues el 0x00. Esto lo recibirá cada módulo y responderán.
 * 
 */
static void DRIVING_MODES_SM_Echo_Send(void)
{
    asm("nop");
}