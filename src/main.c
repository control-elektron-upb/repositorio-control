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

#include "board/peripherals.h"
#include "firmware/buses.h"
#include "firmware/can.h"
#include "firmware/decode_data.h"
#include "firmware/variable_monitoring.h"
#include "firmware/failures.h"
#include "firmware/driving_modes.h"
#include "firmware/rampa_pedal.h"

/***********************************************************************************************************************
 * Application entry point
 **********************************************************************************************************************/

/**
 * @brief Programa principal Control Elektron
 * 
 * El código se encuentra implementado en un microcontrolador STM32F446VET6 presente en la tarjeta
 * de Control del vehículo eléctrico Vulcano del equipo Elektron Motorsports de la UPB.
 * 
 * @return int
 */
int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();
	
	/* Initialize all configured peripherals */
	Board_Peripherals_Init();	//GPIO, CAN, ...

	/* Infinite loop */
	while (1)
	{
		//CAN_SEND_DATA();		// En el primer ciclo envia datos por defecto de la inicializaci�n de buses
		DRIVING_MODES();		// En el primer ciclo se queda en kINIT esperando respuesta
		//CAN_RECEIVE_DATA();
		DECODE_DATA();
		VARIABLE_MONITORING();
		FAILURES();
		RAMPA_PEDAL();
	}

	return 0;
}
