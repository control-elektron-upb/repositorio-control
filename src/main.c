/**
 * @file main.c
 * @author Subgrupo Control
 * @brief Programa principal Control Elektron
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @mainpage Arquitectura de Firmware v1.0
 *
 *  @image html arquitectura-firmware-control-v1.0.png
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include <stdio.h>

#include "buses.h"
#include "can_receive_data.h"
#include "decode_data.h"
#include "variable_monitoring.h"
#include "failures.h"
#include "driving_modes.h"
#include "rampa_pedal.h"

/***********************************************************************************************************************
 * Application entry point
 **********************************************************************************************************************/

/**
 * @brief Programa principal Control Elektron
 * 
 * @return int
 */
int main(void)
{
	
	/* Inicializaciones de hardware */

	/* Loop principal */
	while (1)
	{
		//CAN_SEND_DATA();		// En el primer ciclo envia datos por defecto de la inicialización de buses
		DRIVING_MODES();		// En el primer ciclo se queda en kINIT esperando respuesta
		//CAN_RECEIVE_DATA();
		DECODE_DATA();
		VARIABLE_MONITORING();
		FAILURES();
		RAMPA_PEDAL();
	}
	return 0;
}
