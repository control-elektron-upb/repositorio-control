/**
 * @file variable_monitoring.h
 * @author Andr�s
 * @brief Declaraciones monitoreo de variables decodificadas
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _VARIABLE_MONITORING_H_
#define _VARIABLE_MONITORING_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "buses.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/** @brief Porcentaje para zona regular (+/- 5% por defecto) */
#define REGULAR_ZONE 0.05

/* ------------------------- BMS ------------------------- */

/** @brief Valor m�ximo voltaje BMS */
#define V_MAX_BMS 0

/** @brief Valor m�nimo voltaje BMS */
#define V_MIN_BMS 0

/** @brief Valor m�ximo corriente BMS */
#define I_MAX_BMS 0

/** @brief Valor m�nimo corriente BMS */
#define I_MIN_BMS 0

/** @brief Valor m�ximo potencia BMS */
#define P_MAX_BMS 0

/** @brief Valor m�nimo potencia BMS */
#define P_MIN_BMS 0

/** @brief Valor m�ximo temperatura BMS */
#define T_MAX_BMS 0

/** @brief Valor m�nimo temperatura BMS */
#define T_MIN_BMS 0

/** @brief Valor m�ximo voltaje celda BMS */
#define V_CELDA_MAX_BMS 0

/** @brief Valor m�nimo voltaje celda BMS */
#define V_CELDA_MIN_BMS 0

/** @brief Valor m�ximo nivel bater�a BMS */
#define NIV_BAT_MAX_BMS 0

/** @brief Valor m�nimo nivel bater�a BMS */
#define NIV_BAT_MIN_BMS 0

/* ------------------------- DCDC ------------------------- */

/** @brief Valor m�ximo voltaje bater�a DCDC */
#define V_BAT_MAX_DCDC 0

/** @brief Valor m�nimo voltaje bater�a DCDC */
#define V_BAT_MIN_DCDC 0

/** @brief Valor m�ximo voltaje salida DCDC */
#define V_OUT_MAX_DCDC 0

/** @brief Valor m�nimo voltaje salida DCDC */
#define V_OUT_MIN_DCDC 0

/** @brief Valor m�ximo temperatura DCDC */
#define T_MAX_DCDC 0

/** @brief Valor m�nimo temperatura DCDC */
#define T_MIN_DCDC 0

/** @brief Valor m�ximo potencia DCDC */
#define P_MAX_DCDC 0

/** @brief Valor m�nimo potencia DCDC */
#define P_MIN_DCDC 0

/* ----------------------- INVERSOR ----------------------- */

/** @brief Valor m�ximo velocidad inversor */
#define VEL_MAX_INV 0

/** @brief Valor m�nimo velocidad inversor */
#define VEL_MIN_INV 0

/** @brief Valor m�ximo temperatura motor */
#define T_MAX_MOTOR 0

/** @brief Valor m�nimo temperatura motor */
#define T_MIN_MOTOR 0

/** @brief Valor m�ximo voltaje inversor */
#define V_MAX_INV 0

/** @brief Valor m�nimo voltaje inversor */
#define V_MIN_INV 0

/** @brief Valor m�ximo corriente inversor */
#define I_MAX_INV 0

/** @brief Valor m�nimo corriente inversor */
#define I_MIN_INV 0

/** @brief Valor m�ximo temperatura inversor */
#define T_MAX_INV 0

/** @brief Valor m�nimo temperatura inversor */
#define T_MIN_INV 0

/** @brief Valor m�ximo potencia inversor */
#define P_MAX_INV 0

/** @brief Valor m�nimo potencia inversor */
#define P_MIN_INV 0

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Funci�n principal de monitoreo de variables
 *
 * Determina los estados de las variables decodificadas del BMS, DCDC e inversor y
 * los guarda en una estructura de tipo st_bms_vars_t. No es static, por lo que
 * puede ser usada por otros archivos.
 *
 */
void VARIABLE_MONITORING(void);

#endif /* _VARIABLE_MONITORING_H_ */
