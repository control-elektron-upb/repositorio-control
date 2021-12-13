/**
 * @file buses.c
 * @author Juan
 * @brief Implementación buses de arquitectura de firmware de Control 
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Buses initialization
 **********************************************************************************************************************/

/* Inicialización de bus de datos (bus 1) */
typedef_bus1_t bus_data =
{
    /* Variable modo de manejo */
    .driving_mode = ECO,

    /* Variable falla */
    .failure = CAUTION1,

    /* Variable velocidad */
    .velocidad_inversor = 0U,

    /* Variable info de control */
    .control_ok = kInfo_ERROR,

    /* Estructura de periféricos */
    .Rx_Peripherals = {.buttons_change_state = kButton_NONE, .dead_man = kDeadMan_NOPRESS, .peripherals_ok = kInfo_ERROR},

    /* Estructuras de BMS */
    .Rx_Bms = {.bms_ok = kInfo_ERROR},
    .St_Bms = {kVarState_DATA_PROBLEM},

    /* Estructuras de DCDC */
    .Rx_Dcdc = {.dcdc_ok = kInfo_ERROR},
    .St_Dcdc = {kVarState_DATA_PROBLEM},

    /* Estructuras de inversor */
    .Rx_Inversor = {.inversor_ok = kInfo_ERROR},
    .St_Inversor = {kVarState_DATA_PROBLEM}
};

/* Inicialización de bus de salida CAN (bus 2) */
typedef_bus2_t bus_can_output = { 0 };

/* Inicialización de bus de recepción CAN (bus 3) */
typedef_bus3_t bus_can_input = { 0 };
