/*
 * File:   failures_st.c
 *
 */

#include "failures_st.h"

enum variable_state {
    OK,
    REGULAR,
    PROBLEM
};
typedef enum variable_state Var_State;

struct bms {
    Var_State voltaje;
    Var_State corriente;
    Var_State voltaje_min_celda;
    Var_State potencia;
    Var_State t_max;
    Var_State nivel_bateria;

    Var_State struct_status;

} BMS;

struct dcdc {
    Var_State voltaje_batería;
    Var_State t_max;

    Var_State struct_status;

} DCDC;

struct inversor {
    Var_State velocidad;
    Var_State V;
    Var_State I;
    Var_State temp_max;
    Var_State temp_motor;
    Var_State potencia;

    Var_State struct_status;

} Inversor;


uint8_t bms_current_status(void) {
    /* leer las variables de la estructura BMS y determinar que valor de struct_status deberia
    asignarse */

    /* condicion OK */
    if (BMS.voltaje == OK & BMS.corriente == OK ){
        return OK;
    }

    /* condicion REGULAR */

    /* condicion PROBLEM */
    
}

uint8_t dcdc_current_status(void) {
    /* leer las variables de la estructura DCDC y determinar que valor de struct_status deberia
    asignarse */
    return OK;
}

uint8_t inversor_current_status(void) {
    /* leer las variables de la estructura Inversor y determinar que valor de struct_status deberia
    asignarse */
    return OK;
}

void init_structs(void) {
    /* inicializar las variables que se encuentran dentro de las estructuras de bms, 
    dcdcd, inversor, poniendo los valores de las variables que vienen de monitoreo 
    de variables */
}

int main () {
    
    BMS.struct_status = bms_current_status();
    DCDC.struct_status = dcdc_current_status();
    Inversor.struct_status = inversor_current_status();
    
}




