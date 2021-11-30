/*
 * File:   rampa_pedal.c
 *
 */

#include "rampa_pedal.h"

uint8_t velocidad_inversor = 0;


float get_velocidad_inversor(void) {
    return velocidad_inversor;
}


void rampa_function(uint8_t driving_mode, uint8_t dead_man, float pedal) {

    if (dead_man == PRESS) {
        velocidad_inversor = dead_man_rampa(pedal);
    }
    else if (dead_man == NOPRESS) {
        switch (driving_mode) 
        {
        case ECO:
            velocidad_inversor = eco_rampa(pedal);
            break;
        case NORMAL:
            velocidad_inversor = normal_rampa(pedal);
            break;
        case SPORT:
            velocidad_inversor = sport_rampa(pedal);
            break;
        }    
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

/* funcion mapear rango a otro rango */
float mapRange(float input, float input_start, float input_end, float output_start, float output_end) {
	float slope;
    float output;

    slope = (output_end - output_start) / (input_end - input_start);
    output = output_start + slope * (input - input_start);

    return output;
}