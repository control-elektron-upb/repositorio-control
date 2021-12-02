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

    int pedal_percent;
    float V_max_pedal = 5; //ejemplo 5 value

    pedal_percent = (pedal/V_max_pedal)*100;

    if (dead_man == PRESS) {
        velocidad_inversor = dead_man_rampa(pedal_percent);
    }
    else if (dead_man == NOPRESS) {
        switch (driving_mode) 
        {
        case ECO:
            velocidad_inversor = eco_rampa(pedal_percent);
            break;
        case NORMAL:
            velocidad_inversor = normal_rampa(pedal_percent);
            break;
        case SPORT:
            velocidad_inversor = sport_rampa(pedal_percent);
            break;
        }    
    }   
}


float normal_rampa(float pedal_percent) {

 if( (pedal_percent >= 0 ) & (pedal_percent < 20 ) ) {
    return pedal_percent * 0.5;

 }else if( (pedal_percent >= 20 ) & (pedal_percent < 40 ) ) {
    return pedal_percent - 10;

 }else if( (pedal_percent >= 40 ) & (pedal_percent < 60 ) ) {
    return (2 * pedal_percent) - 50;

 }else if( (pedal_percent >= 60 ) & (pedal_percent < 80 ) ) {
    return pedal_percent + 10;

 }else if( (pedal_percent >= 80 ) & (pedal_percent < 100 ) ) {
    return (0.5 * pedal_percent)  + 50;

 }
    //return (float) 1 / ( 1 + exp(-pedal) );
}


float eco_rampa(float pedal_percent) {

     if( (pedal_percent >= 0 ) & (pedal_percent < 20 ) ) {
    return pedal_percent * 0.25;

 }else if( (pedal_percent >= 20 ) & (pedal_percent < 40 ) ) {
    return (0.5 * pedal_percent) - 5;

 }else if( (pedal_percent >= 40 ) & (pedal_percent < 60 ) ) {
    return (0.75 * pedal_percent) - 15;

 }else if( (pedal_percent >= 60 ) & (pedal_percent < 80 ) ) {
    return (1.5 * pedal_percent) - 60;

 }else if( (pedal_percent >= 80 ) & (pedal_percent < 100 ) ) {
    return (2 * pedal_percent)  - 100;

 }
    //return (float) 1 / ( 1 + exp(-pedal) );
}


float sport_rampa(float pedal_percent) {

    if( (pedal_percent >= 0 ) & (pedal_percent < 20 ) ) {
    return pedal_percent * 1.5;

 }else if( (pedal_percent >= 20 ) & (pedal_percent < 40 ) ) {
    return (1.25 * pedal_percent) + 5;

 }else if( (pedal_percent >= 40 ) & (pedal_percent < 60 ) ) {
    return (1 * pedal_percent) + 15;

 }else if( (pedal_percent >= 60 ) & (pedal_percent < 80 ) ) {
    return (0.75 * pedal_percent) + 30;

 }else if( (pedal_percent >= 80 ) & (pedal_percent < 100 ) ) {
    return (0.5 * pedal_percent)  + 50;

 }
    //return (float) 1 / ( 1 + exp(-pedal) );
}


float dead_man_rampa(float pedal_percent) {
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