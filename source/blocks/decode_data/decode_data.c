/**
 * @file decode_data.c
 * @author Juan
 * @brief Implementación decodificación de datos provenientes de bus CAN
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "decode_data.h"

/*******************************************************************************
 * Private variables definitions
 ******************************************************************************/

/**
 * @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos
 * 
 */
static rx_peripherals_vars_t *p_Rx_Peripherals = &bus_data.Rx_Peripherals;

/**
 * @brief Puntero a estructura de tipo rx_bms_vars_t que contiene los valores de las variables decodificadas del BMS
 * 
 */
static rx_bms_vars_t *p_Rx_Bms = &bus_data.Rx_Bms;

/**
 * @brief Puntero a estructura de tipo rx_dcdc_vars_t que contiene los valores de las variables decodificadas del DCDC
 * 
 */
static rx_dcdc_vars_t *p_Rx_Dcdc = &bus_data.Rx_Dcdc;

/**
 * @brief Puntero a estructura de tipo rx_inversor_vars_t que contiene los valores de las variables decodificadas del inversor
 * 
 */
static rx_inversor_vars_t *p_Rx_Inversor = &bus_data.Rx_Inversor;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/

static void decode_peripherals(void);
static void decode_bms(void);
static void decode_dcdc(void);
static void decode_inversor(void);

static void decode_peripherals_analog(void);
static void decode_inversor_analog(void);
static void decode_bms_analog(void);
static void decode_dcdc_analog(void);

static void decode_peripherals_info(void);
static void decode_inversor_info(void);
static void decode_bms_info(void);
static void decode_dcdc_info(void);

static void decode_buttons(void);
static void decode_dead_man_info(void);

/*******************************************************************************
 * Public functions implementation
 ******************************************************************************/

/**
 * @brief Función principal de decodificación de datos de bus CAN
 * 
 * Decodifica los datos que se reciben desde el bus CAN de: periféricos, BMS,
 * DCDC, inversor. Los datos decodificados quedan guardados en estructuras
 * de tipo rx_peripherals_vars_t, rx_bms_vars_t, rx_dcdc_vars_t, y rx_inversor_vars_t, 
 * en el bus_data. Estas estructuras son Rx_Peripherals, Rx_Bms, Rx_Dcdc y Rx_Inversor. 
 * No es static, por lo que puede ser usada por otros archivos.
 * 
 * @param flag_decodificar Bandera para ejecutar bloque de decodificación
 */
void decode_Data(decode_status_t flag_decodificar)
{
    if (flag_decodificar == kDECODIFICA)
    {
        decode_peripherals();
        decode_bms();
        decode_dcdc();
        decode_inversor();
        flag_decodificar = kNO_DECODIFICA;
    }
}

/*******************************************************************************
 * Private functions implementation
 ******************************************************************************/

/**
 * @brief Decodifica los datos de periféricos
 * 
 * Decodifica las variables que se reciben de periféricos por CAN y guarda 
 * los datos en la estructura Rx_Peripherals del tipo rx_peripherals_vars_t 
 * y que se encuentra en el bus_data.
 * 
 */
static void decode_peripherals(void)
{
    decode_peripherals_analog();

    decode_dead_man_info();
    decode_buttons();
    decode_peripherals_info();
}

/**
 * @brief Decodifica los datos del BMS
 * 
 * Decodifica las variables que se reciben del BMS por CAN y guarda 
 * los datos en la estructura Rx_Bms del tipo rx_bms_vars_t y que
 * se encuentra en el bus_data.
 * 
 */
static void decode_bms(void)
{
    decode_bms_analog();

    decode_bms_info();
}

/**
 * @brief Decodifica los datos del DCDC
 * 
 * Decodifica las variables que se reciben del DCDC por CAN y guarda 
 * los datos en la estructura Rx_Dcdc del tipo rx_dcdc_vars_t y que
 * se encuentra en el bus_data.
 * 
 */
static void decode_dcdc(void)
{
    decode_dcdc_analog();

    decode_dcdc_info();
}

/**
 * @brief Decodifica los datos del inversor
 * 
 * Decodifica las variables que se reciben del inversor por CAN y guarda 
 * los datos en la estructura Rx_Inversor del tipo rx_inversor_vars_t y 
 * que se encuentra en el bus_data.
 * 
 */
static void decode_inversor(void)
{
    decode_inversor_analog();

    decode_inversor_info();
}

/**
 * @brief Decodifica las variables analógicas de periféricos
 * 
 */
static void decode_peripherals_analog(void)
{
    p_Rx_Peripherals->pedal = (rx_var_t)bus_can_input.pedal / 60.0;
}

/**
 * @brief Decodifica las variables analógicas del BMS
 * 
 */
static void decode_bms_analog(void)
{
    p_Rx_Bms->voltaje = (rx_var_t)bus_can_input.voltaje_bms;
    p_Rx_Bms->corriente = (rx_var_t)bus_can_input.corriente_bms;
    p_Rx_Bms->voltaje_min_celda = (rx_var_t)bus_can_input.voltaje_min_celda_bms;
    p_Rx_Bms->potencia = (rx_var_t)bus_can_input.potencia_bms;
    p_Rx_Bms->t_max = (rx_var_t)bus_can_input.t_max_bms;
    p_Rx_Bms->nivel_bateria = (rx_var_t)bus_can_input.nivel_bateria_bms;
}

/**
 * @brief Decodifica las variables analógicas del DCDC
 * 
 */
static void decode_dcdc_analog(void)
{
    p_Rx_Dcdc->voltaje_bateria = (rx_var_t)bus_can_input.voltaje_bateria_dcdc;
    p_Rx_Dcdc->t_max = (rx_var_t)bus_can_input.t_max_dcdc;
}

/**
 * @brief Decodifica las variables analógicas del inversor
 * 
 */
static void decode_inversor_analog(void)
{
    p_Rx_Inversor->velocidad = (rx_var_t)bus_can_input.velocidad_inv;
    p_Rx_Inversor->V = (rx_var_t)bus_can_input.V_inv;
    p_Rx_Inversor->I = (rx_var_t)bus_can_input.I_inv;
    p_Rx_Inversor->temp_max = (rx_var_t)bus_can_input.temp_max_inv;
    p_Rx_Inversor->temp_motor = (rx_var_t)bus_can_input.temp_motor_inv;
    p_Rx_Inversor->potencia = (rx_var_t)bus_can_input.potencia_inv;
}

/** @brief Valor CAN para las variables peripherals_ok, bms_ok, dcdc_ok, inversor_ok  */
#define CAN_OK 0x01
/** @brief Valor CAN para las variables peripherals_ok, bms_ok, dcdc_ok, inversor_ok  */
#define CAN_ERROR 0x02

/**
 * @brief Decodifica info de perifericos
 * 
 */
static void decode_peripherals_info(void)
{
    switch (bus_can_input.peripherals_ok)
    {
    case CAN_OK:
        p_Rx_Peripherals->peripherals_ok = OK;
        break;
    case CAN_ERROR:
        p_Rx_Peripherals->peripherals_ok = ERROR;
        break;
    }
}

/**
 * @brief Decodifica info de bms
 * 
 */
static void decode_bms_info(void)
{
    switch (bus_can_input.bms_ok)
    {
    case CAN_OK:
        p_Rx_Bms->bms_ok = OK;
        break;
    case CAN_ERROR:
        p_Rx_Bms->bms_ok = ERROR;
        break;
    }
}

/**
 * @brief Decodifica info de dcdc
 * 
 */
static void decode_dcdc_info(void)
{
    switch (bus_can_input.dcdc_ok)
    {
    case CAN_OK:
        p_Rx_Dcdc->dcdc_ok = OK;
        break;
    case CAN_ERROR:
        p_Rx_Dcdc->dcdc_ok = ERROR;
        break;
    }
}

/**
 * @brief Decodifica info de inversor
 * 
 */
static void decode_inversor_info(void)
{
    switch (bus_can_input.inversor_ok)
    {
    case CAN_OK:
        p_Rx_Inversor->inversor_ok = OK;
        break;
    case CAN_ERROR:
        p_Rx_Inversor->inversor_ok = ERROR;
        break;
    }
}

/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN1 0x01
/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN2 0x02
/** @brief Valor CAN para buttons_change_state */
#define CAN_BTN3 0x03

/**
 * @brief Decodifica botones de periféricos
 * 
 */
static void decode_buttons(void)
{
    switch (bus_can_input.buttons_change_state)
    {
    case CAN_BTN1:
        p_Rx_Peripherals->buttons_change_state = NORMAL;
        break;
    case CAN_BTN2:
        p_Rx_Peripherals->buttons_change_state = ECO;
        break;
    case CAN_BTN3:
        p_Rx_Peripherals->buttons_change_state = SPORT;
        break;
    }
}

/** @brief Valor CAN para dead_man */
#define CAN_PRESS 0x01
/** @brief Valor CAN para dead_man */
#define CAN_NOPRESS 0x02

/**
 * @brief Decodifica info de hombre muerto de periféricos
 * 
 */
static void decode_dead_man_info(void)
{
    switch (bus_can_input.dead_man)
    {
    case CAN_PRESS:
        p_Rx_Peripherals->dead_man = PRESS;
        break;
    case CAN_NOPRESS:
        p_Rx_Peripherals->dead_man = NOPRESS;
        break;
    }
}