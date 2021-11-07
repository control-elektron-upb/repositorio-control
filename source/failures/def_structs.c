/*
 * File:   def_structs.c
 *
 */

#include "def_structs.h"


/* funcion para incorporar los valores de las variables que 
vienen de monitoreo de variables (y que estan publicadas en el bus 1) 
a las estructuras BMS, DCDC, Inversor */
void fill_structs(void) 
{
    fill_bms_struct(&BMS);  
    fill_dcdc_struct(&DCDC);
    fill_inversor_struct(&Inversor);
}


void fill_bms_struct(struct bms *p_BMS) 
{
    p_BMS->voltaje = bus_data.voltaje_bms_state;
    p_BMS->corriente = bus_data.corriente_bms_state;
	p_BMS->voltaje_min_celda = bus_data.voltaje_min_celda_bms_state;
    p_BMS->potencia = bus_data.potencia_bms_state;	
	p_BMS->t_max = bus_data.t_max_bms_state;
    p_BMS->nivel_bateria = bus_data.nivel_bateria_bms_state;

    p_BMS->struct_status = bms_current_status();
}


void fill_dcdc_struct(struct dcdc *p_DCDC) 
{
    p_DCDC->voltaje_bateria = bus_data.voltaje_bateria_dcdc_state;
    p_DCDC->t_max = bus_data.voltaje_bateria_dcdc_state;

    p_DCDC->struct_status = dcdc_current_status();
}


void fill_inversor_struct(struct inversor *p_Inversor) 
{
    p_Inversor->velocidad = bus_data.velocidad_inv_state;
    p_Inversor->V = bus_data.V_inv_state;
    p_Inversor->I = bus_data.I_inv_state;
    p_Inversor->temp_max = bus_data.temp_max_inv_state;
    p_Inversor->temp_motor = bus_data.temp_motor_inv_state;
    p_Inversor->potencia = bus_data.potencia_inv_state;

    p_Inversor->struct_status = inversor_current_status();
}


/* leer las variables de la estructura BMS y determinar que 
valor de struct_status deberia asignarse */
uint8_t bms_current_status(void) {

    /* condicion OK */
    if ( BMS.voltaje == OK && BMS.corriente == OK 
            && BMS.voltaje_min_celda == OK && BMS.potencia == OK 
            && BMS.t_max == OK && BMS.nivel_bateria == OK ) 
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
    else if ( BMS.voltaje == PROBLEM || BMS.corriente == PROBLEM 
            || BMS.voltaje_min_celda == PROBLEM || BMS.potencia == PROBLEM 
            || BMS.t_max == PROBLEM || BMS.nivel_bateria == PROBLEM ) 
    {
        return PROBLEM;
    }
}

/* leer las variables de la estructura DCDC y determinar que 
valor de struct_status deberia asignarse */
uint8_t dcdc_current_status(void) {

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
}

/* leer las variables de la estructura Inversor y determinar que 
valor de struct_status deberia asignarse */
uint8_t inversor_current_status(void) {

    /* condicion OK */
    if ( Inversor.velocidad == OK && Inversor.V == OK 
            && Inversor.I == OK && Inversor.temp_max == OK 
            && Inversor.temp_motor == OK && Inversor.potencia == OK ) 
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
    else if ( Inversor.velocidad == PROBLEM || Inversor.V == PROBLEM 
            || Inversor.I == PROBLEM || Inversor.temp_max == PROBLEM 
            || Inversor.temp_motor == PROBLEM || Inversor.potencia == PROBLEM ) 
    {
        return PROBLEM;
    }
}
