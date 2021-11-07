/*
 * File:   failures_st.h
 *
 */

#ifndef _FAILURES_ST_H_
#define _FAILURES_ST_H_

#include "buses/def_buses.h"
#include "def_structs.h"

/* estados de la maquina */
enum
{
	kOK=0,
	kCAUTION1,
	kCAUTION2,
	kAUTOKILL
};

/* funciones */
void failures_state_machine(void);
uint8_t failures_st_leer(void);

#endif  /* _FAILURES_ST_H_ */