
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
#define ID_VOLTAJE_MIN_CELDA 		0x022	
#define ID_POTENCIA_BMS				0x023	// 0-255 -> 0-2550
#define ID_T_MAX					0x024
#define	ID_NIVEL_BATERIA			0x025	// 0-200 -> 0-100
#define ID_BMS_OK					0x026
#define ID_VOLTAJE_BATERIA			0x030
#define ID_T_MAX					0x032
#define ID_DCDC_OK					0x033
#define ID_VELOCIDAD				0x040	// 0-240 -> 0-60
#define ID_V						0x041
#define ID_I						0x042
#define ID_TEMP_MAX					0x043
#define ID_TEMP_MOTOR				0x044
#define ID_POTENCIA					0x045
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
	uint8_t driving_modes_state;
	uint8_t failures_state;

	enum buttons_states rx_buttons_change_state;	//decodificado
	enum peripherals_info rx_peripherals_ok;		//decodificado
	enum inversor_info rx_inversor_ok;				//decodificado
	enum bms_info rx_bms_ok;						//decodificado
	enum dcdc_info rx_dcdc_ok;						//decodificado


} typedef_bus1;

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

enum buttons_states
{
	ECO,
	NORMAL,
	SPORT
};

enum peripherals_info
{
	OK,
	ERROR
};

enum inversor_info
{
	OK,
	ERROR
};

enum bms_info
{
	OK,
	ERROR
};

enum dcdc_info
{
	OK,
	ERROR
};

/*
BUS 2:
-Transmición datos CAN (Envío data asincrono -> CAN)
-Nivel velocidad inversor
-Auto kill
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


/*
BUS 3:
-Recepcion datos CAN
*/

typedef struct bus3
{
	uint8_t  pedal;						//can
	uint8_t  dead_man;					//can	
	uint8_t  buttons_change_state;		//can
	uint8_t  peripherals_ok;			//can
	uint8_t  voltaje_bms;				//can
	uint8_t  corriente_bms;				//can
	uint8_t  voltaje_min_celda;			//can
	uint8_t  potencia_bms;				//can
	uint8_t  t_max;						//can 0x24
	uint8_t  nivel_bateria;				//can
	uint8_t  bms_ok;					//can
	uint8_t  voltaje_bateria;			//can
	
	uint8_t  t_max;						//can 0x32
	uint8_t  dcdc_ok;					//can
	uint8_t  velocidad					//can
	uint8_t  V;							//can
	uint8_t  I;							//can
	uint8_t  temp_max;					//can
	uint8_t  temp_motor;				//can
	uint8_t  potencia;					//can
	uint8_t  inversor_ok;				//can
} typedef_bus3;


extern typedef_bus1 bus_data;
extern typedef_bus2 bus_data_output;
extern typedef_bus3 bus_can_input;
#endif