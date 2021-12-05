/**
 * @file def_buses.h
 * @author Juan
 * @brief Declaraciones buses de arquitectura de firmware
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DEF_BUSES_H_
#define _DEF_BUSES_H_

#include <stdint.h>
#include <stdbool.h>

#include "receive_data.h"
#include "decode_data.h"
#include "variable_monitoring.h"
#include "driving_modes.h"
#include "failures.h"
#include "rampa_pedal.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/

/* CAN ID */

/* ID Transmit */
#define ID_ESTADO_MANEJO 			0x010
#define ID_ESTADO_FALLA				0x011
#define ID_NIVEL_VELOCIDAD			0x012
#define ID_NIVEL_VOLTAJE			0x013
#define ID_CONTROL_OK				0x014

/* ID Reception */
#define ID_PEDAL					0x002
#define ID_DEAD_MAN					0x003
#define ID_BUTTONS_CHANGE_STATE		0x004
#define ID_PERIPHERALS_OK			0x005

#define ID_VOLTAJE_BMS				0x020	// 0-210 -> 0-4.2
#define	ID_CORRIENTE_BMS			0x021	// 0-255 -> 0-60
#define ID_VOLTAJE_MIN_CELDA_BMS 	0x022	
#define ID_POTENCIA_BMS				0x023	// 0-255 -> 0-2550
#define ID_T_MAX_BMS				0x024
#define	ID_NIVEL_BATERIA_BMS		0x025	// 0-200 -> 0-100
#define ID_BMS_OK					0x026

#define ID_VOLTAJE_BATERIA_DCDC		0x030
#define ID_VOLTAJE_SALIDA_DCDC		0x031
#define ID_T_MAX_DCDC				0x032
#define ID_DCDC_OK					0x033
#define ID_POTENCIA_DCDC		    0x034


#define ID_VELOCIDAD_INV			0x040	// 0-240 -> 0-60
#define ID_V_INV					0x041
#define ID_I_INV					0x042
#define ID_TEMP_MAX_INV				0x043
#define ID_TEMP_MOTOR_INV			0x044
#define ID_POTENCIA_INV				0x045
#define ID_INVERSOR_OK				0x046

/*******************************************************************************
 * Types declarations
 ******************************************************************************/

/**
 * @brief Bus 1: Bus de datos
 * 
 * - Parsing de datos (Decodificación data <- CAN)
 * - Rampa pedal
 * - Maquina modo de manejo
 * - Maquina de fallas
 * - Monitoreo de variables
 * - Generación de indicadores
 */
typedef struct bus1
{
    /* Variables máquinas modo de manejo y fallas */
    driving_mode_t          driving_mode;
    failure_t               failure;

    /* Estructuras con variables decodificadas */
    rx_peripherals_vars_t   Rx_Peripherals;
    rx_bms_vars_t           Rx_Bms;
    rx_dcdc_vars_t          Rx_Dcdc;
    rx_inversor_vars_t      Rx_Inversor;

    /* Estructuras con estados de las variables decodificadas */
    st_bms_vars_t           St_Bms;
    st_dcdc_vars_t          St_Dcdc;
    st_inversor_vars_t      St_Inversor;

    /* Otras variables ... */

} typedef_bus1_t;

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

/** @brief Tamaño de mensaje asíncrono */
#define LENGTH_ASYNC_MSG				5

/**
 * @brief Bus 2: Bus de transmisión de datos CAN
 * 
 * - Transmisión datos CAN (Envío data asíncrono -> CAN)
 * - Envío nivel velocidad inversor
 * - Envío Auto kill
 * - Envío modo manejo
 * - Harvester
 * 
 */
typedef struct bus2
{

    uint8_t  autokill;          /**< Salida CAN  0x001 */              
	uint8_t  estado_manejo; 	/**< Salida CAN  0x010 */
	uint8_t  estado_falla; 		/**< Salida CAN  0x011 */
	uint8_t  nivel_velocidad;	/**< Salida CAN  0x012 */
	uint8_t  nivel_voltaje;		/**< Salida CAN  0x013 */
	uint8_t  control_ok;		/**< Salida CAN  0x014 */

	struct 
	{
		uint32_t can_adress;
		uint8_t	 value;	
	} async[LENGTH_ASYNC_MSG];
} typedef_bus2_t;


/**
 * @brief Bus 3: Bus de recepción de datos CAN
 * 
 * - Recepción datos CAN
 * - Parsing de datos (CAN -> Decodificación data)
 * - Harvester
 * 
 */
typedef struct bus3
{
	uint8_t  pedal;						/**< CAN 0x002 */
	uint8_t  dead_man;					/**< CAN 0x003 */
	uint8_t  buttons_change_state;		/**< CAN 0x004 */
	uint8_t  peripherals_ok;			/**< CAN 0x005 */

	uint8_t  voltaje_bms;				/**< CAN 0x020 */
	uint8_t  corriente_bms;				/**< CAN 0x021 */
	uint8_t  voltaje_min_celda_bms;		/**< CAN 0x022 */
	uint8_t  potencia_bms;				/**< CAN 0x023 */
	uint8_t  t_max_bms;					/**< CAN 0x024 */
	uint8_t  nivel_bateria_bms;			/**< CAN 0x025 */
	uint8_t  bms_ok;					/**< CAN 0x026 */
	
	uint8_t  voltaje_bateria_dcdc;		/**< CAN 0x030 */
	uint8_t  voltaje_salida_dcdc;		/**< CAN 0x031 */
	uint8_t  t_max_dcdc;				/**< CAN 0x032 */
	uint8_t  dcdc_ok;					/**< CAN 0x033 */
	uint8_t  potencia_dcdc;		        /**< CAN 0x034 */

	uint8_t  velocidad_inv;				/**< CAN 0x040 */
	uint8_t  V_inv;						/**< CAN 0x041 */
	uint8_t  I_inv;						/**< CAN 0x042 */
	uint8_t  temp_max_inv;				/**< CAN 0x043 */
	uint8_t  temp_motor_inv;			/**< CAN 0x044 */
	uint8_t  potencia_inv;				/**< CAN 0x045 */
	uint8_t  inversor_ok;				/**< CAN 0x046 */
} typedef_bus3_t;

/*******************************************************************************
 * Global variables declarations
 ******************************************************************************/

extern typedef_bus1_t bus_data;       /* puede ser manipulada por otros archivos */
extern typedef_bus2_t bus_can_output; /* puede ser manipulada por otros archivos */
extern typedef_bus3_t bus_can_input;  /* puede ser manipulada por otros archivos */

#endif /* _DEF_BUSES_H_ */