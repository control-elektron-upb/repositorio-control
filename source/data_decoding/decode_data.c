/*
 * File:   decode_data.c
 *
 */

#include "../buses/def_buses.h"


void Decode_Data(void){
	if( flag_decodificar == DECODIFICA ){
		map_analog();
		flag_decodificar = NO_DECODIFICA;
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

