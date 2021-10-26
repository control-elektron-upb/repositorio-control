

/*
 * File:   variable_monitoring.h
 *
 */

#ifndef _VARIABLES_MONITORING_H_
#define _VARIABLE_MONITORING_H_

#include <stdint.h>

#include "buses/def_buses.h"
#include "buses/def_buses.c"



//valores minimos y maximos de cada parte
int V_MAX_BMS = 0;
int V_MIN_BMS = 0;
int I_MAX_BMS = 0;
int I_MIN_BMS = 0;
int P_MAX_BMS = 0;
int P_MIN_BMS = 0;
int T_MAX_BMS = 0;
int NIV_BAT_MIN_BMS = 0;
int V_BAT_MAX_DCDC = 0;
int V_BAT_MIN_DCDC = 0;
int T_MAX_DCDC = 0 ;
int VEL_MAX_MOTOR = 0;
int T_MAX_MOTOR = 0;
int V_MAX_INV = 0;
int V_MIN_INV = 0;
int I_MAX_INV = 0;
int I_MIN_INV = 0;
int T_MAX_INV = 0;
int P_MAX_INV = 0;
int P_MIN_INV = 0;


//estados posibles de cada parte
enum {
    OK,
    REGULAR,
    PROBLEM,
    DATA_PROBLEM
};


#endif _VARIABLES_MONITORING_H_