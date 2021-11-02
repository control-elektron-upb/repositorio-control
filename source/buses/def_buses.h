
#ifndef _DEF_BUSES_H_
#define _DEF_BUSES_H_

#include <stdint.h>
#include <stdbool.h>

/* CAN ID*/

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
#define ID_T_MAX_DCDC				0x032
#define ID_DCDC_OK					0x033

#define ID_VELOCIDAD_INV			0x040	// 0-240 -> 0-60
#define ID_V_INV					0x041
#define ID_I_INV					0x042
#define ID_TEMP_MAX_INV				0x043
#define ID_TEMP_MOTOR_INV			0x044
#define ID_POTENCIA_INV				0x045
#define ID_INVERSOR_OK				0x046


/*
BUS 1:
-Parsing de datos (Decodificación data <- CAN)
-Rampa pedal
-Maquina de modo manejo
-Maquina de falla
-Monitoreo de variables
-Generación de indicadores
*/

typedef struct bus1
{
	/* variables de estados de maquinas */
	uint8_t driving_modes_state;
	uint8_t failures_state;

	/* datos decodificados */
	enum dead_man_states rx_dead_man;
	enum buttons_states rx_buttons_change_state;
	enum info rx_peripherals_ok;		
	enum info rx_inversor_ok;
	enum info rx_bms_ok;
	enum info rx_dcdc_ok;
	float rx_pedal;
	float rx_voltaje_bms;
	float rx_corriente_bms;
	float rx_voltaje_min_celda_bms;
	float rx_potencia_bms;
	float rx_t_max_bms;
	float rx_nivel_bateria_bms;
	float rx_voltaje_bateria_dcdc;
	float rx_t_max_dcdc;
	float rx_velocidad_inv;
	float rx_V_inv;
	float rx_I_inv;
	float rx_temp_max_inv;
	float rx_temp_motor_inv;
	float rx_potencia_inv;

	/* estado de las variables */
	uint8_t voltaje_bms_state;
	uint8_t corriente_bms_state;						
	uint8_t voltaje_min_celda_bms_state;				
	uint8_t potencia_bms_state;						
	uint8_t t_max_bms_state;							
	uint8_t nivel_bateria_bms_state;					
	uint8_t voltaje_bateria_dcdc_state;				
	uint8_t t_max_dcdc_state;							
	uint8_t velocidad_inv_state;						
	uint8_t V_inv_state;								
	uint8_t I_inv_state;								
	uint8_t temp_max_inv_state;						
	uint8_t temp_motor_inv_state;					
	uint8_t potencia_inv_state;	


} typedef_bus1;

enum buttons_states
{
	ECO,
	NORMAL,
	SPORT
};

enum info
{
	OK,
	ERROR
};

enum dead_man_states
{
	PRESS,
	NOPRESS
};

/*
BUS 2:
-Transmisión datos CAN (Envío data asíncrono -> CAN)
-Envío nivel velocidad inversor
-Envío Auto kill
-Envío modo manejo
-Harvester
*/

#define LENGTH_ASYNC_MSG				5
typedef struct bus2
{
	uint8_t  estado_manejo; 			//salida can
	uint8_t  estado_falla; 				//salida can
	uint8_t  nivel_velocidad;			//salida can
	uint8_t  nivel_voltaje;				//salida can
	uint8_t  control_ok;				//salida can

	struct 
	{
		uint32_t can_adress;
		uint8_t	 value;	
	} async[LENGTH_ASYNC_MSG];
} typedef_bus2;

enum driving_modes
{
	ECO,
	NORMAL,
	SPORT
};

enum failures
{
	OK,
	CAUTION1,
	CAUTION2,
	AUTOKILL
};

/*
BUS 3:
-Recepcion datos CAN
*/

typedef struct bus3
{
	uint8_t  pedal;						//can 0x002
	uint8_t  dead_man;					//can 0x003	
	uint8_t  buttons_change_state;		//can 0x004
	uint8_t  peripherals_ok;			//can 0x005

	uint8_t  voltaje_bms;				//can 0x020
	uint8_t  corriente_bms;				//can 0x021
	uint8_t  voltaje_min_celda_bms;		//can 0x022
	uint8_t  potencia_bms;				//can 0x023
	uint8_t  t_max_bms;					//can 0x024
	uint8_t  nivel_bateria_bms;			//can 0x025
	uint8_t  bms_ok;					//can 0x026
	
	uint8_t  voltaje_bateria_dcdc;		//can 0x030
	uint8_t  t_max_dcdc;				//can 0x032
	uint8_t  dcdc_ok;					//can 0x033

	uint8_t  velocidad_inv;				//can 0x040
	uint8_t  V_inv;						//can 0x041
	uint8_t  I_inv;						//can 0x042
	uint8_t  temp_max_inv;				//can 0x043
	uint8_t  temp_motor_inv;			//can 0x044
	uint8_t  potencia_inv;				//can 0x045
	uint8_t  inversor_ok;				//can 0x046
} typedef_bus3;


extern typedef_bus1 bus_data;
extern typedef_bus2 bus_data_output;
extern typedef_bus3 bus_can_input;
#endif