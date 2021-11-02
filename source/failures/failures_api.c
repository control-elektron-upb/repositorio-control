/*
 * File:   failures_api.c
 *
 */

#include "failures_api.h"
#include "failures_st.h"

uint8_t Leer_estado_failures(void) {
    return failures_st_leer();
}

void FAILURES_OPS(void) {
    failures_state_machine();
}