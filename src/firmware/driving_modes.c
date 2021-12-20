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
 * Macros
 **********************************************************************************************************************/

/** @brief Duración del echo en ms */
#define ECHO_LENGTH         1000

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

static void DrivingModes_Send_Echo(typedef_bus2_t* bus_can_output);

static void DrivingModes_Send_ControlInfo(module_info_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output);

static void DrivingModes_Send_DrivingMode(driving_mode_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output);

static void DrivingModes_StartTimer(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal máquina de modos de manejo.
 *
 * Llama a la función máquina de estados de modos de manejo. No es static, por
 * lo que puede ser usada por otros archivos.
 * 
 * @param None
 * @retval None
 */
void DRIVING_MODES(void)
{
    DrivingModes_StateMachine();
}

/**
 * @brief Lee estado de la máquina de estados de modo de manejo.
 *
 * Lee estado de la máquina de estados de modo de manejo. No es static, por lo
 * que puede ser usada por otros archivos.
 * 
 * @param None
 * @return uint8_t Estado de la máquina de estados
 */
uint8_t DRIVING_MODES_Get_State(void)
{
    return driving_modes_state;
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Máquina de estados de modo de manejo.
 *
 * Se encarga de permitir las transiciones entre los diferentes modos de manejo
 * de acuerdo a los botones de periféricos y a la máquina de fallas. Por defecto
 * inicia en el estado kINIT, en el cual se realiza un echo y se espera a confirmación
 * de los demás módulos.
 *
 * Lee la variable buttons_change_state de la estructura de variables decodificadas
 * de periféricos, es decir, la estructura de tipo rx_peripherals_vars_t que se encuentra
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

        HAL_Delay(1000);    // espera 1s

        if (DrivingModes_WaitResponse_Echo() == IM_READY)                           // espera confirmación de los demás módulos
        {
            DrivingModes_Send_ControlInfo(kInfo_OK, &bus_data, &bus_can_output);    // envía info de control a bus de datos y a bus de salida can
            driving_modes_state = kNORMAL;                                          // pasa a estado kNORMAL
        }
        break;

    case kECO:

        /* Actualiza modo de manejo a ECO en bus de datos y bus de salida can */
        DrivingModes_Send_DrivingMode(ECO, &bus_data, &bus_can_output);

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
        /* Actualiza modo de manejo a NORMAL en bus de datos y bus de salida can */
        DrivingModes_Send_DrivingMode(NORMAL, &bus_data, &bus_can_output);

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
        /* Actualiza modo de manejo a SPORT en bus de datos y bus de salida can */
        DrivingModes_Send_DrivingMode(SPORT, &bus_data, &bus_can_output);

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
 * @brief Realiza echo y espera confirmación de los demás módulos.
 *
 * @return control_status_t Status de control
 */
static control_status_t DrivingModes_WaitResponse_Echo(void)
{
    bool time_out = false;

    control_status_t status = NOT_READY;            // control no está listo

    DrivingModes_Send_Echo_CAN(&bus_can_output);    // envía echo a bus CAN 

    DrivingModes_StartTimer();                      // comienza timer

    while (status != IM_READY)
    {

        //DrivingModes_DebugLEDs();

        /* todos los módulos OK? */
        if (bus_can_input.peripherals_ok == CAN_OK && bus_can_input.bms_ok == CAN_OK 
            && bus_can_input.dcdc_ok == CAN_OK && bus_can_input.inversor_ok == CAN_OK)
        {
            status = IM_READY;      // control está listo
        }
        /* bandera de timer activada? */
        else if (flag_timer) 
        {            
            time_out = true;        // hay timeout

            DrivingModes_Send_Echo(&bus_can_output);    // envía echo a bus CAN, de nuevo

            DrivingModes_StartTimer();                  // comienza timer, de nuevo

            time_out = false;

            flag_timer = 0;         // reinicia bandera de timer
        }        
    }

    return status;
}

/**
 * @brief Realiza echo a los demás módulos.
 *
 * Se envía por la dirección CAN 0x014 (control_ok) el valor 0x01 un segundo después
 * de encenderse la tarjeta, despues el 0x00. Esto lo recibirá cada módulo y responderán.
 *
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida CAN)
 */
static void DrivingModes_Send_Echo(typedef_bus2_t* bus_can_output)
{
    bus_can_output->control_ok = CAN_ECHO;      // carga valor 0x01 a control_ok del bus 2 (bus_can_output)
    
    CAN_DRIVER_Send(bus_can_output);            // llamada a función de envío de datos a driver CAN
    
    HAL_Delay(ECHO_LENGTH);                     // espera ECHO_LENGTH ms

    bus_can_output->control_ok = CAN_IDLE;      // carga valor 0x00 a control_ok del bus 2 (bus_can_output)

    CAN_DRIVER_Send(bus_can_output);            // llamada a función de envío de datos a driver CAN
}

/**
 * @brief Función para comenzar temporización hasta timeout.
 * 
 * Llama a función TIMER_Start() que se encarga de inciar timer en cero y comienza a contar hasta timeout. Cuando 
 * llega a timeout se genera una interrupción en la cual se activa la bandera flag_timer. Con dicha bandera será 
 * posible determinar que se cumplió el tiempo designado, es decir, se generó el timeout.
 * 
 */
static void DrivingModes_StartTimer(void)
{
    TIMER_Start();
}

/**
 * @brief Envío de status de control a bus de datos y a bus de salida can.
 *
 * @param to_send           Status de control a enviar
 * @param bus_data          Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida can)
 */
static void DrivingModes_Send_ControlInfo(module_info_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output)
{
    bus_data->control_ok = to_send;

    switch (to_send)
    {
    case kInfo_OK:
        bus_can_output->control_ok = CAN_OK;
        break;
    case kInfo_ERROR:
        bus_can_output->control_ok = CAN_ERROR;
        break;
    default:
        break;
    }
}

/**
 * @brief Envío de modo de manejo a bus de datos y a bus de salida can.
 *
 * @param to_send           Modo de manejo a enviar
 * @param bus_data          Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida can)
 */
static void DrivingModes_Send_DrivingMode(driving_mode_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output)
{
    bus_data->driving_mode = to_send;

    switch (to_send)
    {
    case OK:
        bus_can_output->estado_manejo = CAN_OK;
        break;
    case NORMAL:
        bus_can_output->estado_manejo = CAN_NORMAL;
        break;
    case SPORT:
        bus_can_output->estado_manejo = CAN_SPORT;
        break;
    default:
        break;
    }
}