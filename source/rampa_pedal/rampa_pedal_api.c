/*
 * File:   rampa_pedal_api.c
 *
 */

#include "rampa_pedal_api.h"
#include "rampa_pedal.h"

uint8_t Leer_Velocidad_Inversor(void) {
    return get_velocidad_inversor();
}

void RAMPA_PEDAL_OPS(void) {
    rampa_function(bus_data.driving_mode, bus_data.rx_dead_man, bus_data.rx_pedal);
}

/* los valores que corresponden al 0 y al 100 de velocidad inversor */
#define MIN_VALUE_VEL_INVERSOR     0.0
#define MAX_VALUE_VEL_INVERSOR     60.0

/* funcion envío de modo de manejo a bus de salida can */ 
void Send_Velocidad_Inversor(void) {

    /* convertir el dato de velocidad de tipo float del bus_data y que está 
    entre un valor mínimo y máximo, a un dato de velocidad uint8_t entre 0 y 100 
    para ser publicado al bus de salida CAN */

    if (bus_data.velocidad_inversor < MIN_VALUE_VEL_INVERSOR) {
        bus_can_output.nivel_velocidad = 0;
    }
    else if(bus_data.velocidad_inversor > MAX_VALUE_VEL_INVERSOR) {
        bus_can_output.nivel_velocidad = 100;
    }
    else{
        bus_can_output.nivel_velocidad = (uint8_t) mapRange(bus_data.velocidad_inversor, MIN_VALUE_VEL_INVERSOR, MAX_VALUE_VEL_INVERSOR, 0, 100);
    }
}