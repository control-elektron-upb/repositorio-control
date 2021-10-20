

/*
 * File:   variable_monitoring.h
 *
 */

#ifndef _VARIABLES_MONITORING_H_
#define _VARIABLE_MONITORING_H_

#include <stdint.h>

#include "buses/def_buses.h"



/* can Reception parsing 0-255*/


//las variables no se si son externas o como las traigo aca ¿como modificar los rx. y ponerlos aqui ?


//vbles limites de 0 a 255 (posibilidad de setear estos valores desde perisfericos ?!!?)
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


enum VOLTAJE_BMS{
    OK,
    PROBLEM

}		
enum CORRIENTE_BMS{
    OK,
    PROBLEM
}	
enum V_MIN_CELDA_BMS{//me dice el voltaje minimo o el voltaje actual de la celda
    OK,
    PROBLEM
}	
enum POTENCIA_BMS{
    OK,
    PROBLEM
}	
enum T_BMS{//t_max_bms //colocar como rango para detectar problemas en el sensor??
    OK,
    PROBLEM
}	
enum NIV_BATERIA_BMS{
    OK,
    PROBLEM
}	
/*enum OK_BMS{
    OK,
    PROBLEM
}*/	
enum V_BATERIA_DCDC{
    OK,
    PROBLEM
}	
enum T_DCDC{//tmax dcdc
    OK,
    PROBLEM
}	
/*enum OK_DCDC{
    OK,
    PROBLEM
}*/	
enum VELOCIDAD_MOTOR{
    OK,
    PROBLEM
}	
enum T_MOTOR{
    OK,
    PROBLEM
}
enum VOLTAJE_INV{
    OK,
    PROBLEM
}
enum CORRIENTE_INV{
    OK,
    PROBLEM
}
enum T_INV{//t_max_inversor
    OK,
    PROBLEM
}

enum POTENCIA_INV{
    OK,
    PROBLEM
}
/*
enum OK_INV{
    OK,
    PROBLEM
}*/

