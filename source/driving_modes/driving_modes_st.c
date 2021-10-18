/*
 * File:   driving_modes_st.c
 *
 */

#include "driving_modes_st.h"
#include "../failures/failures_st.h" 

/* variable de estados inicializada en INIT */ 
uint8_t driving_modes_state = kINIT;

uint8_t driving_modes_st_leer(void) {
	return driving_modes_state;
}

/* maquina de estados */
void driving_modes_state_machine(void) {
    switch (driving_modes_state) {
    case kINIT:
        /* */
        if (perifericos_ok & inversor_ok & DCDC_ok & BMS_ok & time_out) {
            driving_modes_state = kNORMAL;
        }
        break;
    case kECO:
        
        if (EV_boton_normal & (estado_fallas == OK | estado_fallas == CAUTION1)) {
            driving_modes_state = kNORMAL;
        }
        if (EV_boton_sport & estado_fallas == OK) {
            driving_modes_state = kSPORT;
        }
        break;
    case kNORMAL:
        if (EV_boton_eco | estado_fallas == CAUTION2) {
            driving_modes_state = kECO;
        }
        if (EV_boton_sport & estado_fallas == OK) {
            driving_modes_state = kSPORT;
        }
        break;
    case kSPORT:
        if (EV_boton_eco | estado_fallas == CAUTION2) {
            driving_modes_state = kECO;
        }
        if (EV_boton_normal | estado_fallas == CAUTION1) {
            driving_modes_state = kSPORT;
        }
        break;
    default:
        break;
    }
}
