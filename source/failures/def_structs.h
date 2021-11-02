/*
 * File:   def_structs.h
 *
 */

#ifndef _DEF_STRUCTS_H_
#define _DEF_STRUCTS_H_

#include "buses/def_buses.h"

/* */
typedef enum {
    OK,
    REGULAR,
    PROBLEM
} Var_State;


/* estructura BMS con estado de variables del bms */
struct bms {
    Var_State voltaje;
    Var_State corriente;
    Var_State voltaje_min_celda;
    Var_State potencia;
    Var_State t_max;
    Var_State nivel_bateria;

    Var_State struct_status;

} BMS;

/* estructura DCDC con estado de variables del dcdc */
struct dcdc {
    Var_State voltaje_bateria;
    Var_State t_max;

    Var_State struct_status;

} DCDC;

/* estructura Inversor con estado de variables del inversor */
struct inversor {
    Var_State velocidad;
    Var_State V;
    Var_State I;
    Var_State temp_max;
    Var_State temp_motor;
    Var_State potencia;

    Var_State struct_status;

} Inversor;

/* funciones para determinar y asignar el estado actual de la estructura 
segun como estan las variables */
uint8_t bms_current_status(void);
uint8_t dcdc_current_status(void);
uint8_t inversor_current_status(void);

/* funcion para incorporar los valores de las variables que 
vienen de monitoreo de variables a las estructuras BMS, DCDC, Inversor */
void fill_structs(void);

void fill_bms_struct(struct bms *p_BMS);
void fill_dcdc_struct(struct dcdc *p_DCDC);
void fill_inversor_struct(struct inversor *p_Inversor);

#endif  /* _DEF_STRUCTS_H_ */




