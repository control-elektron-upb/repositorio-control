/**
 * @file variable_monitoring.h
 * @author Andrés
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

/** @brief Valor máximo voltaje BMS */
#define V_MAX_BMS 0

/** @brief Valor mínimo voltaje BMS */
#define V_MIN_BMS 0

/** @brief Valor máximo corriente BMS */
#define I_MAX_BMS 0

/** @brief Valor mínimo corriente BMS */
#define I_MIN_BMS 0

/** @brief Valor máximo potencia BMS */
#define P_MAX_BMS 0

/** @brief Valor mínimo potencia BMS */
#define P_MIN_BMS 0

/** @brief Valor máximo temperatura BMS */
#define T_MAX_BMS 0

/** @brief Valor mínimo temperatura BMS */
#define T_MIN_BMS 0

/** @brief Valor máximo voltaje celda BMS */
#define V_CELDA_MAX_BMS 0

/** @brief Valor mínimo voltaje celda BMS */
#define V_CELDA_MIN_BMS 0

/** @brief Valor máximo nivel batería BMS */
#define NIV_BAT_MAX_BMS 0

/** @brief Valor mínimo nivel batería BMS */
#define NIV_BAT_MIN_BMS 0

/* ------------------------- DCDC ------------------------- */

/** @brief Valor máximo voltaje batería DCDC */
#define V_BAT_MAX_DCDC 0

/** @brief Valor mínimo voltaje batería DCDC */
#define V_BAT_MIN_DCDC 0

/** @brief Valor máximo voltaje salida DCDC */
#define V_OUT_MAX_DCDC 0

/** @brief Valor mínimo voltaje salida DCDC */
#define V_OUT_MIN_DCDC 0

/** @brief Valor máximo temperatura DCDC */
#define T_MAX_DCDC 0

/** @brief Valor mínimo temperatura DCDC */
#define T_MIN_DCDC 0

/** @brief Valor máximo potencia DCDC */
#define P_MAX_DCDC 0

/** @brief Valor mínimo potencia DCDC */
#define P_MIN_DCDC 0

/* ----------------------- INVERSOR ----------------------- */

/** @brief Valor máximo velocidad inversor */
#define VEL_MAX_INV 0

/** @brief Valor mínimo velocidad inversor */
#define VEL_MIN_INV 0

/** @brief Valor máximo temperatura motor */
#define T_MAX_MOTOR 0

/** @brief Valor mínimo temperatura motor */
#define T_MIN_MOTOR 0

/** @brief Valor máximo voltaje inversor */
#define V_MAX_INV 0

/** @brief Valor mínimo voltaje inversor */
#define V_MIN_INV 0

/** @brief Valor máximo corriente inversor */
#define I_MAX_INV 0

/** @brief Valor mínimo corriente inversor */
#define I_MIN_INV 0

/** @brief Valor máximo temperatura inversor */
#define T_MAX_INV 0

/** @brief Valor mínimo temperatura inversor */
#define T_MIN_INV 0

/** @brief Valor máximo potencia inversor */
#define P_MAX_INV 0

/** @brief Valor mínimo potencia inversor */
#define P_MIN_INV 0

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

/**
 * @brief Función principal de monitoreo de variables.
 *
 * Determina los estados de las variables decodificadas del BMS, DCDC, e inversor y
 * los guarda en el bus_data en estructuras de tipo st_bms_vars_t, st_dcdc_vars_t, 
 * y st_inversor_vars_t. Estas estructuras son St_Bms, St_Dcdc, y St_Inversor.
 * No es static, por lo que puede ser usada por otros archivos.
 * 
 * @param None
 * @retval None
 */
void VARIABLE_MONITORING(void);

#endif /* _VARIABLE_MONITORING_H_ */
