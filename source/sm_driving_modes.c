/*
 * File:   sm_driving_modes.c
 *
 */

#include "sm_driving_modes.h"
#include "sm_failures.h"

void state_machine(void){

    switch (estado)
    {
    case INIT:
        if (perifericos_ok & inversor_ok & DCDC_ok & BMS_ok & time_out)
        {
            estado = NORMAL;
        }
        
        break;
    
    case ECO:
        if (EV_boton_normal & (estado_fallas == OK | estado_fallas == CAUTION1))
        {
            estado = NORMAL;
        }
        if (EV_boton_sport & estado_fallas == OK)
        {
            estado = SPORT;
        }
        break;

    case NORMAL:
        if (EV_boton_eco | estado_fallas == CAUTION2)
        {
            estado = ECO;
        }
        if (EV_boton_sport & estado_fallas == OK)
        {
            estado = SPORT;
        }

        break;

    case SPORT:
        if (EV_boton_eco | estado_fallas == CAUTION2)
        {
            estado = ECO;
        }
        if (EV_boton_normal | estado_fallas == CAUTION1)
        {
            estado = SPORT;
        }
        break;

    default:
        break;
    }

}