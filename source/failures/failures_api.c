/*
 * File:   failures_api.c
 *
 */

#include "failures_api.h"
#include "failures_st.h"
#include "def_structs.h"

void Llenar_Structs(void) {
    fill_structs();
}

uint8_t Leer_estado_failures(void) {
    return failures_st_leer();
}

void FAILURES_OPS(void) {
    failures_state_machine();
}