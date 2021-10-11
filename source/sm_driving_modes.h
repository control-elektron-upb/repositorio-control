/*
 * File:   sm_driving_modes.c
 *
 */

#ifndef _DEF_BUSES_H_
#define _DEF_BUSES_H_
#include <stdint.h>
#include <stdbool.h>


// estados de la maquina
enum driving_modes 
{
    INIT = 0,
    ECO,
    NORMAL,
    SPORT
};

// variables maquina de estados
char estado = INIT;             //variable de estados inicializada en INIT

int EV_boton_eco = 0;
int EV_boton_normal = 0;
int EV_boton_sport = 0;
 
#endif  /* _DEF_BUSES_H_ */