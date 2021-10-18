/*
 * File:   failures_st.h
 *
 */

#ifndef _SM_FAILURES_H_
#define _SM_FAILURES_H_
#include <stdint.h>
#include <stdbool.h>

/* rangos de monitoreo de variables */
#define 

/* Condiciones para CAUTION1




*/


// estados de la maquina
enum failures
{
	OK=0,
	CAUTION1,
	CAUTION2,
	AUTOKILL
};

// variables maquina de estados fallas
char estado_fallas = OK;             //variable de estados inicializada en OK
 
#endif  /* _SM_FAILURES_H_ */