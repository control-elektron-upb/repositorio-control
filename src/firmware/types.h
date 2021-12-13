/**
 * @file types.h
 * @author Juan
 * @brief Declaraciones tipos de datos generales del programa de Control
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _TYPES_H_
#define _TYPES_H_

/***********************************************************************************************************************
 * Types declarations
 **********************************************************************************************************************/

/**
 * @brief Tipo de dato driving_mode_t para modos de manejo 
 *
 */
typedef enum
{
    ECO,    /**< Modo de manejo ECO */
    NORMAL, /**< Modo de manejo NORMAL */
    SPORT   /**< Modo de manejo SPORT */
} driving_mode_t;

/**
 * @brief Tipo de dato failure_t para fallas
 *
 */
typedef enum
{
    OK,       /**< Falla OK */
    CAUTION1, /**< Falla CAUTION1 */
    CAUTION2, /**< Falla CAUTION1 */
    AUTOKILL  /**< Falla AUTOKILL */
} failure_t;

/** @brief Tipo de dato rx_var_t para variable "analogica" decodificada */
typedef float rx_var_t;

/**
 * @brief Tipo de dato module_info_t para variable info de cada módulo:
 * periféricos, BMS, DCDC, inversor.
 *
 */
typedef enum
{
    kInfo_OK,   /**< Modulo OK */
    kInfo_ERROR /**< Modulo ERROR */
} module_info_t;

/**
 * @brief Tipo de dato buttons_state_t para variable botones de periféricos
 *
 */
typedef enum
{
    kButton_ECO,    /**< Botón de modo ECO */
    kButton_NORMAL, /**< Botón de modo NORMAL */
    kButton_SPORT,  /**< Botón de modo SPORT */
    kButton_NONE    /**< Ningún Botón de modo */
} buttons_state_t;

/**
 * @brief Tipo de dato dead_man_state_t para variable dead_man de periféricos
 *
 */
typedef enum
{
    kDeadMan_PRESS,  /**< Hombre muerto presionado */
    kDeadMan_NOPRESS /**< Hombre muerto no presionado */
} dead_man_state_t;

/**
 * @brief Tipo de dato estructura rx_peripherals_vars_t para variables decodificadas de periféricos
 *
 */
typedef struct
{
    rx_var_t pedal;
    dead_man_state_t dead_man;
    buttons_state_t buttons_change_state;

    module_info_t peripherals_ok;

} rx_peripherals_vars_t;

/**
 * @brief Tipo de dato estructura rx_bms_vars_t para variables decodificadas del BMS
 *
 */
typedef struct
{
    rx_var_t voltaje;
    rx_var_t corriente;
    rx_var_t voltaje_min_celda;
    rx_var_t potencia;
    rx_var_t t_max;
    rx_var_t nivel_bateria;

    module_info_t bms_ok;

} rx_bms_vars_t;

/**
 * @brief Tipo de dato estructura rx_dcdc_vars_t para variables decodificadas del DCDC
 *
 */
typedef struct
{
    rx_var_t voltaje_bateria;
    rx_var_t voltaje_salida;
    rx_var_t t_max;
    rx_var_t potencia;

    module_info_t dcdc_ok;

} rx_dcdc_vars_t;

/**
 * @brief Tipo de dato estructura rx_inversor_vars_t para variables decodificadas del inversor
 *
 */
typedef struct
{
    rx_var_t velocidad;
    rx_var_t V;
    rx_var_t I;
    rx_var_t temp_max;
    rx_var_t temp_motor;
    rx_var_t potencia;

    module_info_t inversor_ok;

} rx_inversor_vars_t;

/** @brief Tipo de dato var_state_t para estado de variable */
typedef enum
{
    kVarState_DATA_PROBLEM = 0, /**< Problema con el dato */
    kVarState_OK,               /**< Estado de variable OK */
    kVarState_REGULAR,          /**< Estado de variable REGULAR */
    kVarState_PROBLEM,          /**< Estado de variable PROBLEM */
} var_state_t;

/**
 * @brief Tipo de dato estructura st_bms_vars_t para estado de las variables del BMS
 *
 */
typedef struct
{
    var_state_t voltaje;
    var_state_t corriente;
    var_state_t voltaje_min_celda;
    var_state_t potencia;
    var_state_t t_max;
    var_state_t nivel_bateria;

    var_state_t bms_status;         /**< Estado general del módulo BMS */

} st_bms_vars_t;

/**
 * @brief Tipo de dato estructura st_dcdc_vars_t para estado de las variables del DCDC
 *
 */
typedef struct
{
    var_state_t voltaje_bateria;
    var_state_t voltaje_salida;
    var_state_t t_max;
    var_state_t potencia;

    var_state_t dcdc_status;        /**< Estado general del módulo DCDC */

} st_dcdc_vars_t;

/**
 * @brief Tipo de dato estructura st_inversor_vars_t para estado de las variables del inversor
 *
 */
typedef struct
{
    var_state_t velocidad;
    var_state_t V;
    var_state_t I;
    var_state_t temp_max;
    var_state_t temp_motor;
    var_state_t potencia;

    var_state_t inversor_status;    /**< Estado general del módulo inversor */

} st_inversor_vars_t;

#endif /* _TYPES_H_ */
