/**
 * @file rampa_pedal.c
 * @author Subgrupo Control
 * @brief Implementación rampa pedal
 * @version 0.1
 * @date 2021-12-03
 *
 * @copyright Copyright (c) 2021
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "rampa_pedal.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

/** @brief Velocidad calculada de la rampa pedal */
static uint8_t velocidad_inversor = 0;

/** @brief Puntero a estructura de tipo rx_peripherals_vars_t que contiene los valores de las variables decodificadas de periféricos */
static rx_peripherals_vars_t* p_Rx_Peripherals = &bus_data.Rx_Peripherals;

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void RampaPedal_Send_Velocidad(uint8_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output);

static uint8_t rampa_eco(rx_var_t pedal);

static uint8_t rampa_normal(rx_var_t pedal);

static uint8_t rampa_sport(rx_var_t pedal);

static uint8_t rampa_deadman(rx_var_t pedal);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función principal de bloque rampa pedal.
 *
 * Se encarga de transformar el valor de pedal registrado de periféricos a un valor de 
 * velocidad que será empleado por inversor. Para cada modo de manejo se tiene una 
 * función de transferencia diferente para determinar el valor de velocidad asociado al 
 * valor de pedal registrado desde periféricos.
 *
 * Lee la variable pedal de la estructura de variables decodificadas de periféricos,
 * es decir, la estructura de tipo rx_peripherals_vars_t que se encuentra en el bus_data.
 *
 * Escribe en la variable velocidad del bus_data.
 * 
 * Escribe en la variable nivel_velocidad del bus_can_output.
 * 
 * No es static, por lo que puede ser usada por otros archivos.
 *
 * @param   None
 * @retval  None
 */
void RAMPA_PEDAL(void)
{
    if (p_Rx_Peripherals->dead_man == kDeadMan_PRESS)
    {
        velocidad_inversor = rampa_deadman(p_Rx_Peripherals->pedal);
    }
    else if (p_Rx_Peripherals->dead_man == kDeadMan_NOPRESS)
    {
        switch (bus_data.driving_mode)
        {
        case ECO:
            velocidad_inversor = rampa_eco(p_Rx_Peripherals->pedal);
            break;
        case NORMAL:
            velocidad_inversor = rampa_normal(p_Rx_Peripherals->pedal);
            break;
        case SPORT:
            velocidad_inversor = rampa_sport(p_Rx_Peripherals->pedal);
            break;
        default:
            break;
        }
    }

    /* Actualiza velocidad inversor en bus_data */
    RampaPedal_Send_Velocidad(velocidad_inversor, &bus_data, &bus_can_output);
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief Rampa pedal para modo ECO
 *
 * @param pedal     Pedal de periféricos
 * @return uint8_t  Velocidad [0:100]
 */
static uint8_t rampa_eco(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 0.25;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = (0.5 * pedal) - 5;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (0.75 * pedal) - 15;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = (1.5 * pedal) - 60;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (2 * pedal) - 100;
    }

    return (uint8_t)round(velocidad);
}

/**
 * @brief Rampa pedal para modo NORMAL
 *
 * @param pedal     Pedal de periféricos
 * @return uint8_t  Velocidad [0:100]
 */
static uint8_t rampa_normal(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 0.5;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = pedal - 10;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (2 * pedal) - 50;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = pedal + 10;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (0.5 * pedal) + 50;
    }

    return (uint8_t)round(velocidad);
}

/**
 * @brief Rampa pedal para modo SPORT
 *
 * @param pedal     Pedal de periféricos
 * @return uint8_t  Velocidad [0:100]
 */
static uint8_t rampa_sport(rx_var_t pedal) {

    float velocidad = 0;

    if (pedal >= 0 && pedal < 20)
    {
        velocidad = pedal * 1.5;
    }
    else if (pedal >= 20 && pedal < 40)
    {
        velocidad = (1.25 * pedal) + 5;
    }
    else if (pedal >= 40 && pedal < 60)
    {
        velocidad = (1 * pedal) + 15;
    }
    else if (pedal >= 60 && pedal < 80)
    {
        velocidad = (0.75 * pedal) + 30;
    }
    else if (pedal >= 80 && pedal < 100)
    {
        velocidad = (0.5 * pedal) + 50;
    }

    return (uint8_t)round(velocidad);
}

/**
 * @brief Rampa pedal en caso de hombre muerto presionado.
 *
 * @param pedal     Pedal de periféricos
 * @return uint8_t  Velocidad [0:100]
 */
static uint8_t rampa_deadman(rx_var_t pedal) {
    return 0;
}

/**
 * @brief Envío de velocidad a bus de datos y a bus de salida can.
 *
 * @param to_send           Velocidad a enviar
 * @param bus_data          Puntero a estructura de tipo typedef_bus1_t (bus de datos)
 * @param bus_can_output    Puntero a estructura de tipo typedef_bus2_t (bus de salida can)
 */
static void RampaPedal_Send_Velocidad(uint8_t to_send, typedef_bus1_t* bus_data, typedef_bus2_t* bus_can_output)
{
    bus_data->velocidad_inversor = to_send;

    bus_can_output->nivel_velocidad = to_send;
}
