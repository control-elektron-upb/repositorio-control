#ifndef _DEF_BUSES_H_
#define _DEF_BUSES_H_
#include <stdint.h>
#include <stdbool.h>

/* CAN ID*/

/* ID Transmit */
#define ID_PEDAL					0x002
#define ID_DEAD_MAN					0x003
#define ID_BUTTONS_CHANGE_STATE		0x004
#define ID_PERIPHERALS_OK			0x005

/* ID Reception */
#define ID_ESTADO_MANEJO	0x010
#define ID_ESTADO_FALLA		0x011
#define ID_CONTROL_OK		0x014
#define ID_VOLTAJE_BMS		0x020	// 0-210 -> 0-4.2
#define	ID_CORRIENTE_BMS	0x021	// 0-255 -> 0-60
#define ID_POTENCIA_BMS		0x023	// 0-255 -> 0-2550
#define	ID_NIVEL_BATERIA	0x025	// 0-200 -> 0-100
#define ID_VELOCIDAD		0x040	// 0-240 -> 0-60
/*
BUS 1:
-Procesamiento de entrada
-Máquina de estados del hombre muerto
-Envío data asincrono [función]
*/
#define LENGTH_ASYNC_MSG			5
typedef struct bus1
{
	uint8_t  pedal; 		//salida can
	uint8_t  dead_man; 	//salida can
	uint8_t  buttons_change_state;//salida can
	uint8_t  peripherals_ok;	//salida can

	struct 
	{
		uint32_t can_adress;
		uint8_t	 value;	
	} async[LENGTH_ASYNC_MSG];
} typedef_bus1;

/*
BUS 2:
-Máquina de estados del hombre muerto
-Decodificación data <- CAN
-Debouncer
-Notificaciones-acciones control
-Intérprete de entradas
*/

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

enum control_info
{
	IDLE,
	ECHO
};

typedef struct bus2
{
	bool pb1_dead_man;			//lectura ¿como se leen?
	bool pb2_dead_man;			//lectura
	bool pb3_eco_mode;			//lectura
	bool pb4_normal_mode;		//lectura
	bool pb5_sport_mode;		//lectura
	bool pb6_standby;			//lectura
	uint8_t  rx_pedal;			//lectura ¿por que se recibe el pedal?
	bool display_on;
	bool  out1_led_eco;
	bool  out2_led_normal;
	bool  out3_led_sport;
	uint8_t  status_dead_man; //estado actual HM
	uint8_t  out3_buzzer;	
	enum driving_modes rx_driving_mode;//decodificado
	enum failures rx_failures;	//decodificado
	enum control_info rx_control_ok;	//decodificado
	float rx_voltage;	//decodificado 0-240 -> 0-4
	float rx_current;	//decodificado 0-240 -> 0-80
	float rx_power;		//decodificado 0-250 -> 0-1250
	float rx_battery;	//decodificado 0-200 -> 0-100
	float rx_speed;		//decodificado 0-240 -> 0-60
} typedef_bus2;

typedef struct bus3
{
	uint8_t  status_driving;	//can
	uint8_t  status_failures;	//can	
	uint8_t  control_ok;		//can
	uint8_t  voltage_BMS;		//can
	uint8_t  current_BMS;		//can
	uint8_t  power;				//can
	uint8_t  battery_level;		//can
	uint8_t  speed;				//can
} typedef_bus3;

extern typedef_bus1 bus_can_output;
extern typedef_bus2 bus_data;
extern typedef_bus3 bus_can_input;
#endif