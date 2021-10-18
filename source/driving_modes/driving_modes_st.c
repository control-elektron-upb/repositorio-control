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
    
    /* variable evento pulsador */
    EV_button = bus_data.rx_buttons_change_state;

    /* variable de estado driving_modes_state a bus 1 (bus_data) */ 
    bus_data.driving_modes_state = driving_modes_state;

    switch (driving_modes_state) {
    case kINIT:
        if (bus_data.rx_peripherals_ok & bus_data.rx_inversor_ok & bus_data.rx_bms_ok & bus_data.rx_dcdc_ok & time_out) {
            driving_modes_state = kNORMAL;
        }
        break;
    case kECO:
        if (EV_button == NORMAL & (bus_data.failures_state == OK | bus_data.failures_state == CAUTION1)) {
            driving_modes_state = kNORMAL;
        }
        if (EV_button == SPORT & bus_data.failures_state == OK) {
            driving_modes_state = kSPORT;
        }
        break;
    case kNORMAL:
        if (EV_button == ECO | bus_data.failures_state == CAUTION2) {
            driving_modes_state = kECO;
        }
        if (EV_button == SPORT & bus_data.failures_state == OK) {
            driving_modes_state = kSPORT;
        }
        break;
    case kSPORT:
        if (EV_button == ECO | bus_data.failures_state == CAUTION2) {
            driving_modes_state = kECO;
        }
        if (EV_button == NORMAL | bus_data.failures_state == CAUTION1) {
            driving_modes_state = kSPORT;
        }
        break;
    default:
        break;
    }
}
