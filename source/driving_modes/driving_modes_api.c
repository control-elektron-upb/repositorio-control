/*
 * File:   driving_modes_api.c
 *
 */

#include "driving_modes_api.h"
#include "driving_modes_st.h"

uint8_t Leer_estado_driving_modes(void) {
    return driving_modes_st_leer();
}

void DRIVING_MODES_OPS(void) {
    driving_modes_state_machine();
}