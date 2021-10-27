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
    /* leer las variables de la estructura BMS y determinar que valor de struct_status deberia asignarse */

    /* condicion OK */
    if ( BMS.voltaje == OK && BMS.corriente == OK && BMS.voltaje_min_celda == OK && BMS.potencia == OK && BMS.t_max == OK && BMS.nivel_bateria == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( BMS.nivel_bateria == REGULAR 
            || BMS.t_max == REGULAR
            || BMS.voltaje_min_celda == REGULAR
            || (BMS.voltaje == REGULAR && BMS.corriente == REGULAR && BMS.potencia == REGULAR) ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( BMS.voltaje == PROBLEM || BMS.corriente == PROBLEM || BMS.voltaje_min_celda == PROBLEM || BMS.potencia == PROBLEM || BMS.t_max == PROBLEM || BMS.nivel_bateria == PROBLEM ) 
    {
        return PROBLEM;
    }

}


uint8_t dcdc_current_status(void) {
    /* leer las variables de la estructura DCDC y determinar que valor de struct_status deberia
    asignarse */

    /* condicion OK */
    if ( DCDC.t_max == OK && DCDC.voltaje_batería == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( DCDC.t_max == REGULAR || DCDC.voltaje_batería = REGULAR ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( DCDC.t_max == PROBLEM || DCDC.voltaje_batería = PROBLEM ) 
    {
        return PROBLEM;
    }

    return OK;
}

uint8_t inversor_current_status(void) {
    /* leer las variables de la estructura Inversor y determinar que valor de struct_status deberia
    asignarse */

    /* condicion OK */
    if ( Inversor.velocidad == OK && Inversor.V == OK && Inversor.I == OK && Inversor.temp_max == OK && Inversor.temp_motor == OK && Inversor.potencia == OK ) 
    {
        return OK;
    }

    /* condicion REGULAR */
    else if ( Inversor.velocidad == REGULAR 
            || Inversor.temp_max == REGULAR
            || Inversor.temp_motor == REGULAR
            || (Inversor.V == REGULAR && Inversor.I == REGULAR && Inversor.potencia == REGULAR) ) 
    {
        return REGULAR;
    }

    /* condicion PROBLEM */
    else if ( Inversor.velocidad == PROBLEM || Inversor.V == PROBLEM || Inversor.I == PROBLEM || Inversor.temp_max == PROBLEM || Inversor.temp_motor == PROBLEM || Inversor.potencia == PROBLEM ) 
    {
        return PROBLEM;
    }

    return OK;
}

void init_structs(void) {
    /* inicializar las variables que se encuentran dentro de las estructuras de BMS, 
    DCDC, Inversor, poniendo los valores de las variables que vienen de monitoreo 
    de variables */
}

int main () {
    
    BMS.struct_status = bms_current_status();
    DCDC.struct_status = dcdc_current_status();
    Inversor.struct_status = inversor_current_status();
    
}




