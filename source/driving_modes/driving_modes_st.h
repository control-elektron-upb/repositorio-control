/*
 * File:   driving_modes_st.h
 *
 */

#ifndef _DRIVING_MODES_ST_H_
#define _DRIVING_MODES_ST_H_

#include <stdint.h>


/* estados de la maquina */
enum 
{
    kINIT = 0,
    kECO,
    kNORMAL,
    kSPORT
};


/* variables maquina de estados */
int EV_boton_eco = 0;
int EV_boton_normal = 0;
int EV_boton_sport = 0;

void driving_modes_state_machine(void);
uint8_t driving_modes_st_leer(void);



#endif  /* _DRIVING_MODES_ST_H_ */