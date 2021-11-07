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

uint8_t Leer_Estado_Failures(void) {
    return failures_st_leer();
}

void FAILURES_OPS(void) {
    failures_state_machine();
}

#define CAN_OK			0x00 
#define CAN_CAUTION_1	0x01
#define CAN_CAUTION_2	0x02
#define CAN_AUTOKILL	0x03

/* funcion envío de falla a bus de salida can */ 
void Send_Failure(void) {
    switch (bus_data.failures_state)
    {
    case kOK:
        bus_can_output.estado_falla = CAN_OK;
        break;
    case kCAUTION1:
        bus_can_output.estado_falla = CAN_CAUTION_1;
        break;
    case kCAUTION2:
        bus_can_output.estado_falla = CAN_CAUTION_2;
        break;
    case kAUTOKILL:
        bus_can_output.estado_falla = CAN_AUTOKILL;
        break;
    }
}
