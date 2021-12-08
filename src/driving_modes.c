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

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "driving_modes.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Estado de la máquina de estados */
static uint8_t driving_modes_state = kINIT;

/** @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t* p_Rx_Peripherals = &bus_data.Rx_Peripherals;

/** @brief Puntero a estructura de tipo rx_bms_vars_t que contiene los valores de las variables decodificadas del BMS */
static rx_bms_vars_t* p_Rx_Bms = &bus_data.Rx_Bms;

/** @brief Puntero a estructura de tipo rx_dcdc_vars_t que contiene los valores de las variables decodificadas del DCDC */
static rx_dcdc_vars_t* p_Rx_Dcdc = &bus_data.Rx_Dcdc;

/** @brief Puntero a estructura de tipo rx_inversor_vars_t que contiene los valores de las variables decodificadas del inversor */
static rx_inversor_vars_t* p_Rx_Inversor = &bus_data.Rx_Inversor;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void DrivingModes_StateMachine(void);

static control_status_t DrivingModes_WaitResponse_Echo(void);

static void DrivingModes_Send_Echo(typedef_bus2_t* p_bus_can_output);

static void DrivingModes_Send_DrivingMode(driving_mode_t to_send, typedef_bus1_t* p_bus_data);

static void DrivingModes_Send_ControlInfo(control_status_t to_send, typedef_bus1_t* p_bus_data);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

void DRIVING_MODES(void)
{
    DrivingModes_StateMachine();
}

uint8_t get_DrivingModes_State(void)
{
    return driving_modes_state;
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

 /**
  * @brief Máquina de estados de modo de manejo
  *
  * Se encarga de permitir las transiciones entre los diferentes modos de manejo
  * de acuerdo a los botones de periféricos y a la máquina de fallas. Por defecto
  * inicia en el estado kINIT, en el cual se realiza un echo y se espera a confirmación
  * de los demás módulos.
  *
  * Lee la variable buttons_change_state de la estructura de variables decodificadas
  * de periféricos, es decir, la estructura de tipo rx_peripherals_t que se encuentra
  * en el bus_data.
  *
  * Escribe en la variable driving_mode del bus_data.
  * 
  */
static void DrivingModes_StateMachine(void)
{
    switch (driving_modes_state)
    {
    case kINIT:
        /* Espera confirmación de los demás módulos */
        if (DrivingModes_WaitResponse_Echo() == IM_READY)
            driving_modes_state = kNORMAL;
        break;

    case kECO:
        /* Actualiza modo de manejo a ECO en bus_data */
        DrivingModes_Send_DrivingMode(ECO, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == NORMAL && (bus_data.failure == OK || bus_data.failure == CAUTION1))
        {
            driving_modes_state = kNORMAL;
        }
        else if (p_Rx_Peripherals->buttons_change_state == SPORT && bus_data.failure == OK)
        {
            driving_modes_state = kSPORT;
        }
        break;

    case kNORMAL:
        /* Actualiza modo de manejo a NORMAL en bus_data */
        DrivingModes_Send_DrivingMode(NORMAL, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == ECO || bus_data.failure == CAUTION2)
        {
            driving_modes_state = kECO;
        }
        else if (p_Rx_Peripherals->buttons_change_state == SPORT && bus_data.failure == OK)
        {
            driving_modes_state = kSPORT;
        }
        break;

    case kSPORT:
        /* Actualiza modo de manejo a SPORT en bus_data */
        DrivingModes_Send_DrivingMode(SPORT, &bus_data);

        if (p_Rx_Peripherals->buttons_change_state == ECO || bus_data.failure == CAUTION2)
        {
            driving_modes_state = kECO;
        }
        else if (p_Rx_Peripherals->buttons_change_state == NORMAL || bus_data.failure == CAUTION1)
        {
            driving_modes_state = kNORMAL;
        }
        break;

    default:
        break;
    }
}

/**
 * @brief Envío de modo de manejo al bus de datos
 *
 * @param to_send       Modo de manejo a enviar
 * @param p_bus_data    Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 */
static void DrivingModes_Send_DrivingMode(driving_mode_t to_send, typedef_bus1_t* p_bus_data)
{
    p_bus_data->driving_mode = to_send;
}

/**
 * @brief Realiza echo, espera confirmación respuesta de los demás módulos
 *
 * @return control_status_t Status de control
 */
static control_status_t DrivingModes_WaitResponse_Echo(void)
{
    static bool time_out = false;

    control_status_t status = NOT_READY;

    /* Echo a los demás módulos */
    DrivingModes_Send_Echo(&bus_can_output);

    printf("Esperando respuesta...\n");
    while (status != IM_READY)
    {
        /* Recibe info de CAN */
        /* Decodifica */
        /* Lee bus_data */

        /* Si todos los módulos OK y time_out TRUE ... */
        if (p_Rx_Peripherals->peripherals_ok == kInfo_OK && p_Rx_Bms->bms_ok == kInfo_OK
            && p_Rx_Dcdc->dcdc_ok == kInfo_OK && p_Rx_Inversor->inversor_ok == kInfo_OK)
        {
            printf("Todos los módulos OK\n");
            printf("...\n");
            //DrivingModes_Start_Timeout();
            if (time_out) {
                printf("Timeout COMPLETE\n");
                time_out = false;
                status = IM_READY;
            }
        }
        /* Envío info de control a bus_data */
        DrivingModes_Send_ControlInfo(status, &bus_data);
    }
    printf("Control OK\n");
    return status;
}

/**
 * @brief Realiza echo a los demás módulos
 *
 * Se envía por la dirección CAN 0x014 (control_ok) el valor 0x01 un segundo después
 * de encenderse, despues el 0x00. Esto lo recibirá cada módulo y responderán.
 *
 * @param p_bus_can_output      Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void DrivingModes_Send_Echo(typedef_bus2_t* p_bus_can_output)
{
    printf("Control envia Echo\n");
}

/**
 * @brief Envío de status de control al bus de datos 
 *
 * @param to_send       Status de control a enviar
 * @param p_bus_data    Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 */
static void DrivingModes_Send_ControlInfo(control_status_t to_send, typedef_bus1_t* p_bus_data)
{
    switch (to_send)
    {
    case IM_READY:
        p_bus_data->control_ok = kInfo_OK;
        break;
    case NOT_READY:
        p_bus_data->control_ok = kInfo_ERROR;
    default:
        break;
    }
}
