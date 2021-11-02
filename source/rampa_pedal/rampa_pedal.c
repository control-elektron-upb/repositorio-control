/*
 * File:   rampa_pedal.c
 *
 */

#include "rampa_pedal.h"

uint8_t velocidad_inversor;

float get_velocidad_inversor(){
    return velocidad_inversor;
}

float 

void rampa_function(uint8_t bus_data.driving_mode, float bus_data.rx_pedal) {

    switch (driving_mode)
    {
    case ECO:
        velocidad_inversor = eco_rampa(pedal);
        break;
    case NORMAL:
        velocidad_inversor = normal_rampa(pedal);
    case SPORT:
        velocidad_inversor = sport_rampa(pedal);
    case DEAD_MAN:
        velocidad_inversor = dead_man_rampa(pedal);
    }
}

float eco_rampa(float pedal) {
    
    return (float) 1 / ( 1 + exp(-pedal) );
}

float normal_rampa(float pedal) {
    
    return (float) 1 / ( 1 + exp(-pedal) );
}

float sport_rampa(float pedal) {
    
    return (float) 1 / ( 1 + exp(-pedal) );
}

float dead_man_rampa(float pedal) {
    
    return 0;
}
