/*
 * File:   driving_modes_st.h
 *
 */

#ifndef _DRIVING_MODES_ST_H_
#define _DRIVING_MODES_ST_H_

#include <stdint.h>

#include "buses/def_buses.h"

/* estados de la maquina */
enum 
{
    kINIT = 0,
    kECO,
    kNORMAL,
    kSPORT
};

/* variable evento pulsador */
uint8_t EV_button;

void driving_modes_state_machine(void);
uint8_t driving_modes_st_leer(void);

#endif  /* _DRIVING_MODES_ST_H_ */