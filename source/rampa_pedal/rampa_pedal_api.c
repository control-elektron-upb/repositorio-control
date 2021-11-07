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