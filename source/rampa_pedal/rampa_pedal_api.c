/*
 * File:   rampa_pedal_api.c
 *
 */

#include "rampa_pedal/rampa_pedal_api.h"
#include "rampa_pedal/rampa_pedal.h"

uint8_t Leer_velocidad_inversor(void) {
    return get_velocidad_inversor();
}

void RAMPA_PEDAL_OPS(void) {
    rampa_function(bus_data.driving_mode, bus_data.dead_man, bus_data.rx_pedal);
}


#define MIN_VALUE_VELOCIDAD     0.0
#define MIN_VALUE_VELOCIDAD     60.0

/* convertir el dato de velocidad que es un float y está entre un valor 
mínimo y máximo, a un dato de velocidad uint8_t entre 0 y 100. */

void Send_Velocidad_Inversor(void) {
    bus_can_output.nivel_velocidad = 
}