/*
 * File:   driving_modes_api.c
 *
 */

#include "driving_modes_api.h"
#include "driving_modes_st.h"

uint8_t Leer_Estado_Driving_Modes(void) {
    return driving_modes_st_leer();
}

void DRIVING_MODES_OPS(void) {
    driving_modes_state_machine();
}

#define CAN_NORMAL      0x02
#define CAN_ECO         0x03
#define CAN_SPORT       0x04

/* funcion envío de velocidad de inversor a bus de salida can */ 
void Send_Driving_Mode(void) {
    switch (bus_data.driving_modes_state)
    {
    case kECO:
        bus_can_output.estado_manejo = CAN_ECO;
        break;
    case kNORMAL:
        bus_can_output.estado_manejo = CAN_NORMAL;
        break;
    case kSPORT:
        bus_can_output.estado_manejo = CAN_SPORT;
        break;
    }
}

