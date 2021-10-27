/*
 * File:   failures_st.h
 *
 */

#ifndef _FAILURES_ST_H_
#define _FAILURES_ST_H_

#include "buses/def_buses.h"

/* rangos de monitoreo de variables */


/* Condiciones para CAUTION1




*/


// estados de la maquina
enum failures
{
	kOK=0,
	kCAUTION1,
	kCAUTION2,
	kAUTOKILL
};

// variables maquina de estados fallas
char estado_fallas = OK;             //variable de estados inicializada en OK
 
#endif  /* _FAILURES_ST_H_ */