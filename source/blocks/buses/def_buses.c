/**
 * @file def_buses.c
 * @author Juan
 * @brief Implementación buses de arquitectura de firmware
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "def_buses.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/

/**
 * @brief Valor por defecto para variables decodificadas
 * 
 */
#define DEFAULT_VALUE 0

/**
 * @brief Valor por defecto para estado de las variables decodificadas
 * 
 */
#define DEFAULT_STATE DATA_PROBLEM

/*******************************************************************************
 * Variables definitions
 ******************************************************************************/

/**
 * @brief Instancia bus_data del tipo de datos typedef_bus1_t
 * 
 * Inicialización de instancia bus_data del tipo de datos typedef_bus1_t. Todos los
 * miembros de la estructura bus_data quedan inicializados con el valor 0, a excepción
 * de las estructuras de variables codificadas (Rx_Bms, Rx_Dcdc, Rx_Inversor) y las
 * estructuras de estado de las variables (St_Bms, St_Dcdc, St_Inversor), las cuales
 * quedan inicializadas con los valores de DEFAULT_VALUE y DEFAULT_STATE, respectivamente.
 * 
 */
typedef_bus1_t bus_data = {
    .Rx_Peripherals = {DEFAULT_VALUE},
    .Rx_Peripherals = {DEFAULT_STATE},

    .Rx_Bms = {DEFAULT_VALUE},
    .St_Bms = {DEFAULT_STATE},

    .Rx_Dcdc = {DEFAULT_VALUE},
    .St_Dcdc = {DEFAULT_STATE},
    
    .Rx_Inversor = {DEFAULT_VALUE},
    .St_Inversor = {DEFAULT_STATE}
};

/**
 * @brief Instancia bus_can_output del tipo de datos typedef_bus2_t
 * 
 * Inicialización de instancia bus_can_output del tipo de datos typedef_bus2_t. Todos los
 * miembros de la estructura bus_can_output quedan inicializados con el valor 0.
 * 
 */
typedef_bus2_t bus_can_output = {0};

/**
 * @brief Instancia bus_can_input del tipo de datos typedef_bus3_t
 * 
 * Inicialización de instancia bus_can_input del tipo de datos typedef_bus3_t. Todos los
 * miembros de la estructura bus_can_input quedan inicializados con el valor 0.
 * 
 */
typedef_bus3_t bus_can_input = {0};
