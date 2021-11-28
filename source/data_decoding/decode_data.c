/**
 * @file decode_data.c
 * @author Juan
 * @brief Decodificación de datos provenientes de CAN
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "decode_data.h"

/**
 * @brief Decodifica todos los datos que vienen de CAN
 * 
 */
void Decode_Data(void){
	if( flag_decodificar == DECODIFICA ){
		decode_peripherals();
		decode_bms();
		decode_dcdc();
		decode_inversor();
		flag_decodificar = NO_DECODIFICA;
	}
}


/**
 * @brief Decodifica las variables que se reciben de periféricos por CAN y 
 * guarda los datos en la instancia Rx_Peripherals del tipo de datos 
 * rx_peripherals_vars_t y que se encuentra en el bus_data.
 * 
 */
void decode_peripherals(void)
{
	bus_data.Rx_Peripherals.pedal = (rx_var_t) bus_can_input.pedal / 60.0;

	decode_dead_man_info();
	decode_buttons();
	decode_peripherals_info();
}

/**
 * @brief Decodifica las variables que se reciben de bms por CAN y 
 * guarda los datos en la instancia Rx_Bms del tipo de datos 
 * rx_bms_vars_t y que se encuentra en el bus_data.
 * 
 */
void decode_bms(void)
{
	bus_data.Rx_bms.voltaje = 				(rx_var_t) bus_can_input.voltaje_bms;
	bus_data.Rx_bms.corriente = 			(rx_var_t) bus_can_input.corriente_bms;
	bus_data.Rx_bms.voltaje_min_celda = 	(rx_var_t) bus_can_input.voltaje_min_celda_bms;
	bus_data.Rx_bms.potencia = 				(rx_var_t) bus_can_input.potencia_bms;
	bus_data.Rx_bms.t_max = 				(rx_var_t) bus_can_input.t_max_bms;
	bus_data.Rx_bms.nivel_bateria = 		(rx_var_t) bus_can_input.nivel_bateria_bms;

	decode_bms_info();
}

	
/**
 * @brief Decodifica las variables que se reciben de dcdc por CAN y 
 * guarda los datos en la instancia Rx_Dcdc del tipo de datos 
 * rx_dcdc_vars_t y que se encuentra en el bus_data.
 * 
 */
void decode_dcdc(void)
{
	bus_data.Rx_dcdc.voltaje_bateria = (rx_var_t) bus_can_input.voltaje_bateria_dcdc;
	bus_data.Rx_dcdc.t_max = (rx_var_t) bus_can_input.t_max_dcdc;

	decode_dcdc_info();

}


/**
 * @brief Decodifica las variables que se reciben de inversor por CAN y 
 * guarda los datos en la instancia Rx_Inversor del tipo de datos 
 * rx_inversor_vars_t y que se encuentra en el bus_data.
 * 
 */
void decode_inversor(void)
{
	bus_data.Rx_inversor.velocidad = 		(rx_var_t) bus_can_input.velocidad_inv;
	bus_data.Rx_inversor.V = 				(rx_var_t) bus_can_input.V_inv;
	bus_data.Rx_inversor.I = 				(rx_var_t) bus_can_input.I_inv;
	bus_data.Rx_inversor.temp_max = 		(rx_var_t) bus_can_input.temp_max_inv;
	bus_data.Rx_inversor.temp_motor = 		(rx_var_t) bus_can_input.temp_motor_inv;
	bus_data.Rx_inversor.potencia = 		(rx_var_t) bus_can_input.potencia_inv;

	decode_inversor_info();

}


/**
 * @brief Decodifica info de perifericos
 * 
 */
#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_peripherals_info(void) {
	switch(bus_can_input.peripherals_ok) {
	case CAN_OK:
		bus_data.Rx_Peripherals.module_info = OK;
		break;
	case CAN_ERROR:
		bus_data.Rx_Peripherals.module_info = ERROR;
		break;
	}
}

/**
 * @brief Decodifica info de inversor
 * 
 */
#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_inversor_info(void) {
	switch(bus_can_input.inversor_ok) {
	case CAN_OK:
		bus_data.Rx_Inversor.module_info = OK;
		break;
	case CAN_ERROR:
		bus_data.Rx_Inversor.module_info = ERROR;
		break;
	}
}

/**
 * @brief Decodifica info de bms
 * 
 */
#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_bms_info(void) {
	switch(bus_can_input.bms_ok) {
	case CAN_OK:
		bus_data.Rx_Bms.module_info = OK;
		break;
	case CAN_ERROR:
		bus_data.Rx_Bms.module_info = ERROR;
		break;
	}
}

/**
 * @brief Decodifica info de dcdc
 * 
 */
#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_dcdc_info(void) {
	switch(bus_can_input.dcdc_ok) {
	case CAN_OK:
		bus_data.Rx_Dcdc.module_info = OK;
		break;
	case CAN_ERROR:
		bus_data.Rx_Dcdc.module_info = ERROR;
		break;
	}
}

/**
 * @brief Decodifica botones de periféricos
 * 
 */
#define CAN_BTN1		0x01
#define CAN_BTN2    	0x02
#define CAN_BTN3    	0x03 

void decode_buttons(void){
	switch(bus_can_input.buttons_change_state){
	case CAN_BTN1:
		bus_data.Rx_Peripherals.buttons_change_state = NORMAL;
		break;
	case CAN_BTN2:
		bus_data.Rx_Peripherals.buttons_change_state = ECO;
		break;
	case CAN_BTN3:
		bus_data.Rx_Peripherals.buttons_change_state = SPORT;
		break;
	}
}

/**
 * @brief Decodifica info de hombre muerto de periféricos
 * 
 */
#define CAN_PRESS		0x01
#define CAN_NOPRESS 	0x02

void decode_dead_man_info(void) {
	switch(bus_can_input.dead_man) {
	case CAN_PRESS:
		bus_data.Rx_Peripherals.dead_man = PRESS;
		break;
	case CAN_NOPRESS:
		bus_data.Rx_Peripherals.dead_man = NOPRESS;
		break;
	}
}



