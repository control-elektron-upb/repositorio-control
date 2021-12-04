/*
 * File:   rampa_pedal.h
 *
 */

#ifndef _RAMPA_PEDAL_H_
#define _RAMPA_PEDAL_H_

#include <math.h>
#include "def_buses.h"


float get_velocidad_inversor(void);

void rampa_function(uint8_t driving_mode, uint8_t dead_man, float pedal);
float eco_rampa(float pedal);
float normal_rampa(float pedal);
float sport_rampa(float pedal);
float dead_man_rampa(float pedal);

float mapRange(float input, float input_start, float input_end, float output_start, float output_end);

#endif  /* _RAMPA_PEDAL_H_ */