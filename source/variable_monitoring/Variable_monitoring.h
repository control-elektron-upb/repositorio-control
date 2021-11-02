

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
uint8_t V_MAX_BMS           = 0;
uint8_t V_MIN_BMS           = 0;

uint8_t I_MAX_BMS           = 0;
uint8_t I_MIN_BMS           = 0;

uint8_t P_MAX_BMS           = 0;
uint8_t P_MIN_BMS           = 0;

uint8_t T_MAX_BMS           = 0;
uint8_t T_MIN_BMS           = 0;

uint8_t V_CELDA_MAX_BMS     = 0;
uint8_t V_CELDA_MIN_BMS     = 0;    

uint8_t NIV_BAT_MAX_BMS     = 0;
uint8_t NIV_BAT_MIN_BMS     = 0;


uint8_t V_BAT_MAX_DCDC      = 0;
uint8_t V_BAT_MIN_DCDC      = 0;

uint8_t T_MAX_DCDC          = 0;
uint8_t T_MIN_DCDC          = 0;


uint8_t VEL_MAX_INV         = 0;
uint8_t VEL_MIN_INV         = 0;

uint8_t T_MAX_MOTOR         = 0;
uint8_t T_MIN_MOTOR         = 0;

uint8_t V_MAX_INV           = 0;
uint8_t V_MIN_INV           = 0;

uint8_t I_MAX_INV           = 0;
uint8_t I_MIN_INV           = 0;

uint8_t T_MAX_INV           = 0;
uint8_t T_MIN_INV           = 0;

uint8_t P_MAX_INV           = 0;
uint8_t P_MIN_INV           = 0;


//estados posibles de cada parte
enum {
    OK,
    REGULAR,
    PROBLEM,
    DATA_PROBLEM
};


#endif _VARIABLES_MONITORING_H_