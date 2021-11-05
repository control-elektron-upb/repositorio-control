/*
 * File:   rampa_pedal.h
 *
 */

#ifndef _RAMPA_PEDAL_H_
#define _RAMPA_PEDAL_H_

#include <math.h>
#include "buses/def_buses.h"


void rampa_function(uint8_t driving_mode, uint8_t dead_man, float pedal);
uint8_t driving_modes_st_leer(void);

#endif  /* _RAMPA_PEDAL_H_ */