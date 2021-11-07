

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
float V_MAX_BMS           = 0;
float V_MIN_BMS           = 0;

float I_MAX_BMS           = 0;
float I_MIN_BMS           = 0;

float P_MAX_BMS           = 0;
float P_MIN_BMS           = 0;

float T_MAX_BMS           = 0;
float T_MIN_BMS           = 0;

float V_CELDA_MAX_BMS     = 0;
float V_CELDA_MIN_BMS     = 0;    

float NIV_BAT_MAX_BMS     = 0;
float NIV_BAT_MIN_BMS     = 0;


float V_BAT_MAX_DCDC      = 0;
float V_BAT_MIN_DCDC      = 0;

float T_MAX_DCDC          = 0;
float T_MIN_DCDC          = 0;


float  VEL_MAX_INV         = 0;
float  VEL_MIN_INV         = 0;

float T_MAX_MOTOR         = 0;
float T_MIN_MOTOR         = 0;

float V_MAX_INV           = 0;
float V_MIN_INV           = 0;

float I_MAX_INV           = 0;
float I_MIN_INV           = 0;

float T_MAX_INV           = 0;
float T_MIN_INV           = 0;

float P_MAX_INV           = 0;
float P_MIN_INV           = 0;


//estados posibles de cada parte
enum {
    OK,
    REGULAR,
    PROBLEM,
    DATA_PROBLEM
};


#endif _VARIABLES_MONITORING_H_