/**
 * @file main.c
 * @author Juan
 * @brief 
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

#include "def_buses.h"
#include "receive_data.h"
#include "decode_data.h"
#include "variable_monitoring.h"
#include "driving_modes.h"
#include "failures.h"

/*
void irq_handler() {
    //que se active cuando:
    //if(bus_data.failure == AUTOKILL) 

    //Driver_CAN_Send(&bus_can_output);
    asm("nop");
}
*/

/**
 * @brief Programa principal Control Elektron
 * 
 */
void main(void)
{
    DRIVING_MODES_SM_Init(ECO);
    FAILURES_SM_Init(OK);

    while (1)
    {
        decode_Data(flag_decodificar);
        variable_Monitoring();
        FAILURES_SM();
        DRIVING_MODES_SM();
        //Driver_CAN_Send(&bus_can_output);
    }
}