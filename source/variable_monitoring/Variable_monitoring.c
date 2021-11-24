
#define DEFAULT_STATE  DATA_PROBLEM;
#include <stdint.h>
#include "variable_monitoring/Variable_monitoring.h"
/*
0= OK
1= PROBLEM
2= REGULAR
3=DATA PROBLEM
*/

float regular_zone = 0.05; //+-5% de zona en regular

void variable_monitoring (void){

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
voltaje_bms_state = actual_estate_function(V_MAX_BMS, V_MIN_BMS, bus_data.rx_voltaje_bms);
corriente_bms_state = actual_estate_function(I_MAX_BMS, I_MIN_BMS, bus_data.rx_corriente_bms);
potencia_bms_state = actual_estate_function(P_MAX_BMS, P_MIN_BMS,bus_data.rx_potencia_bms);
t_max_bms_state = actual_estate_function(T_MAX_BMS, T_MIN_BMS, bus_data.rx_t_max_bms);
voltaje_min_celda_bms_state = actual_estate_function(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS,bus_data.rx_voltaje_min_celda_bms);
nivel_bateria_bms_state = actual_estate_function(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, bus_data.rx_nivel_bateria_bms);


voltaje_bateria_dcdc_state = actual_estate_function(V_BAT_MAX_DCDC, V_BAT_MIN_DCDC, bus_data.rx_voltaje_bateria_dcdc);
t_max_dcdc_state = actual_estate_function(T_MAX_DCDC, T_MIN_DCDC, bus_data.rx_t_max_dcdc);


velocidad_inv_state = actual_estate_function(VEL_MAX_INV, VEL_MIN_INV, bus_data.rx_velocidad_inv);
V_inv_state = actual_estate_function(V_MAX_INV,V_MIN_INV, bus_data.rx_V_inv);
I_inv_state = actual_estate_function(I_MAX_INV, I_MIN_INV, bus_data.rx_I_inv);
temp_max_inv_state = actual_estate_function(T_MAX_INV, T_MIN_INV, bus_data.rx_temp_max_inv);
temp_motor_inv_state = actual_estate_function(T_MAX_MOTOR, T_MIN_MOTOR, bus_data.rx_temp_motor_inv);
potencia_inv_state = actual_estate_function(P_MAX_INV, P_MIN_INV, bus_data.rx_potencia_inv);

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
}


uint8_t actual_estate_function (float D_max, float D_min, float Data){

    if((Data < (D_max * (-regular_zone + 1))) & (Data > (D_min*(regular_zone + 1)))) {
                    return OK; 

        }else if((Data > (D_max * (regular_zone + 1))) | (Data < (D_min*(-regular_zone + 1)))) {
                    return PROBLEM; 

            }else if(((Data < (D_max * (regular_zone + 1))) & (Data > (D_max * (-regular_zone + 1))))  | 
                    ((Data > (D_min*(-regular_zone + 1))) & (Data < (D_min*(regular_zone + 1))))){
                    return REGULAR; 

                 }else{
                    return DATA_PROBLEM;

                    }

}