/*
 * File:   decode_data.c
 *
 */

#include "../buses/def_buses.h"


void Decode_Data(void){
	if( flag_decodificar == DECODIFICA ){
		decode_peripherals_info();
		decode_inversor_info();
		decode_buttons();
		map_analog();
		flag_decodificar = NO_DECODIFICA;
	}
}

/* decodifica info de perifericos */

#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_peripherals_info(void) {
	switch(bus_can_input.peripherals_ok) {
	case CAN_OK:
		bus_data.rx_peripherals_ok = OK;
		break;
	case CAN_ERROR:
		bus_data.rx_peripherals_ok = ERROR;
		break;
	}
}

/* decodifica info de inversor */

#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_inversor_info(void) {
	switch(bus_can_input.inversor_ok) {
	case CAN_OK:
		bus_data.rx_inversor_ok = OK;
		break;
	case CAN_ERROR:
		bus_data.rx_inversor_ok = ERROR;
		break;
	}
}

/* decodifica info de bms */

#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_bms_info(void) {
	switch(bus_can_input.bms_ok) {
	case CAN_OK:
		bus_data.rx_bms_ok = OK;
		break;
	case CAN_ERROR:
		bus_data.rx_bms_ok = ERROR;
		break;
	}
}

/* decodifica info de dcdc */

#define CAN_OK			0x01
#define CAN_ERROR		0x02

void decode_dcdc_info(void) {
	switch(bus_can_input.dcdc_ok) {
	case CAN_OK:
		bus_data.rx_dcdc_ok = OK;
		break;
	case CAN_ERROR:
		bus_data.rx_dcdc_ok = ERROR;
		break;
	}
}

/* decodifica pulsador */

#define CAN_BTN1		0x01
#define CAN_BTN2    	0x02
#define CAN_BTN3    	0x03 

void decode_buttons(void){
	switch(bus_can_input.buttons_change_state){
	case CAN_BTN1:
		bus_data.rx_buttons_change_state = NORMAL;
		break;
	case CAN_BTN2:
		bus_data.rx_buttons_change_state = ECO;
		break;
	case CAN_BTN3:
		bus_data.rx_buttons_change_state = SPORT;
		break;
	}
}






/* parsing de datos que vienen de CAN (bus 3) */
void map_analog(void){
	bus_data.rx_voltage = (float)bus_can_input.voltage_BMS / 60.0;	//0-240 -> 0-4
	bus_data.rx_current = (float)bus_can_input.current_BMS / 3.0; 	//0-240 -> 0-80
    
	bus_data.rx_power = (float)bus_can_input.power * 5.0;			//0-250 -> 0-1250
	bus_data.rx_battery = (float)bus_can_input.battery_level / 2.0;	//0-200 -> 0-100
	bus_data.rx_speed = (float)bus_can_input.speed / 4.0;			//0-240 -> 0-60
}

