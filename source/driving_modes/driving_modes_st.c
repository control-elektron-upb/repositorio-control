/*
 * File:   driving_modes_st.c
 *
 */

#include "driving_modes_st.h"

/* variable estado maquina inicializada en kINIT */ 
uint8_t driving_modes_state = kINIT;

/* variable modo de manejo */ 
uint8_t driving_mode;

/* funcion leer modo de manejo actual */
uint8_t driving_modes_st_leer(void) {
    return driving_mode;
}

/* maquina de estados */
void driving_modes_state_machine(void) {
    
    /* variable evento pulsador */
    EV_button = bus_data.rx_buttons_change_state;

    switch (driving_modes_state) 
    {
    case kINIT:
        if (bus_data.rx_peripherals_ok && bus_data.rx_inversor_ok && bus_data.rx_bms_ok && bus_data.rx_dcdc_ok && time_out) {
            driving_modes_state = kNORMAL;
        }
        break;
    case kECO:
        if (EV_button == NORMAL && (bus_data.failure == OK || bus_data.failure == CAUTION1)) {
            driving_modes_state = kNORMAL;
        }
        else if (EV_button == SPORT && bus_data.failure == OK) {
            driving_modes_state = kSPORT;
        }
        driving_mode = ECO;
        break;
    case kNORMAL:
        if (EV_button == ECO || bus_data.failure == CAUTION2) {
            driving_modes_state = kECO;
        }
        else if (EV_button == SPORT && bus_data.failure == OK) {
            driving_modes_state = kSPORT;
        }
        driving_mode = NORMAL;
        break;
    case kSPORT:
        if (EV_button == ECO || bus_data.failure == CAUTION2) {
            driving_modes_state = kECO;
        }
        else if (EV_button == NORMAL || bus_data.failure == CAUTION1) {
            driving_modes_state = kSPORT;
        }
        driving_mode = SPORT;
        break;
    }

    /* variable modo de manejo driving_mode a bus 1 (bus_data) */ 
    bus_data.driving_mode = driving_mode;
}