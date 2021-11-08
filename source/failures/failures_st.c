/*
 * File:   failures_st.c
 *
 */

#include "failures_st.h"

/* variable de estados inicializada en kCAUTION1 */
uint8_t failures_state = kCAUTION1;

/* variable falla */ 
uint8_t failure;

/* funcion leer falla actual */
uint8_t failures_st_leer(void) {
    return failure;
}

/* maquina de estados */
void failures_state_machine(void) {

    switch (failures_state) 
    {
    case kOK:
        if (EV_autokill) {
            failures_state = kAUTOKILL;
        }
        else if ( BMS.struct_status == PROBLEM 
                || DCDC.struct_status == PROBLEM
                || Inversor.struct_status == PROBLEM )
        {
            failures_state = kCAUTION2;
        }
        else if ( BMS.struct_status == REGULAR 
                || DCDC.struct_status == REGULAR 
                || Inversor.struct_status == REGULAR )
        {
            failures_state = kCAUTION1;
        }
        failure = OK;
        break;
    case kCAUTION1:
        if (EV_autokill) {
            failures_state = kAUTOKILL;
        }
        else if ( BMS.struct_status == PROBLEM 
                || DCDC.struct_status == PROBLEM
                || Inversor.struct_status == PROBLEM )
        {
            failures_state = kCAUTION2;
        }
        else if ( BMS.struct_status == OK 
                && DCDC.struct_status == OK 
                && Inversor.struct_status == OK )
        {
            failures_state = kOK;
        }
        failure = CAUTION1;
        break;
    case kCAUTION2:
        if (EV_autokill) {
            failures_state = kAUTOKILL;
        }
        else if ( (BMS.struct_status == REGULAR || BMS.struct_status == OK)
                && (DCDC.struct_status == REGULAR || DCDC.struct_status == OK)
                && (Inversor.struct_status == REGULAR || Inversor.struct_status == OK) )
        {
            failures_state = kCAUTION1;
        }
        failure = CAUTION2;
        break;
    case kAUTOKILL:
        /* enviar mensaje de maxima prioridad CAN? */
        failure = AUTOKILL;
        break;
    }

    /* variable failure a bus 1 (bus_data) */ 
    bus_data.failure = failure;
}







