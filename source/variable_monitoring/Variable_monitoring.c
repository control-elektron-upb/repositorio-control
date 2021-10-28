#include <stdint.h>
#include "variable_monitoring/Variable_monitoring.h"
/*
0= OK
1= PROBLEM
2= REGULAR
3=DATA PROBLEM
*/
uint8_t DEFAULT_STATE = DATA_PROBLEM;

uint8_t voltaje_bms_state = DATA_PROBLEM;
uint8_t corriente_bms_state = DATA_PROBLEM;									
uint8_t potencia_bms_state = DATA_PROBLEM;	
uint8_t t_max_bms_state = DATA_PROBLEM;	
uint8_t voltaje_min_celda_bms_state = DATA_PROBLEM;											
uint8_t nivel_bateria_bms_state = DATA_PROBLEM;		

uint8_t voltaje_bateria_dcdc_state = DATA_PROBLEM;				
uint8_t t_max_dcdc_state = DATA_PROBLEM;

uint8_t velocidad_inv_state = DATA_PROBLEM;	
uint8_t temp_motor_inv_state = DATA_PROBLEM;					
uint8_t V_inv_state = DATA_PROBLEM;								
uint8_t I_inv_state = DATA_PROBLEM;	
uint8_t temp_inv_state = DATA_PROBLEM;							
uint8_t temp_max_inv_state = DATA_PROBLEM;							
uint8_t potencia_inv_state = DATA_PROBLEM;	

int regular_zone = 0.05; //+-5% de zona en regular




void variable_monitoring (void){


/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
voltaje_bms_state = actual_estate_function(V_MAX_BMS, V_MIN_BMS, bus_data.rx_voltaje_bms, regular_zone, voltaje_bms_state);
corriente_bms_state = actual_estate_function(I_MAX_BMS, I_MIN_BMS, bus_data.rx_corriente_bms, regular_zone, corriente_bms_state);
potencia_bms_state = actual_estate_function(P_MAX_BMS, P_MIN_BMS,bus_data.rx_potencia_bms,regular_zone,potencia_bms_state);
t_max_bms_state = actual_estate_function(T_MAX_BMS, T_MIN_BMS, bus_data.rx_t_max_bms, regular_zone, t_max_bms_state);
voltaje_min_celda_bms_state = actual_estate_function(V_CELDA_MAX_BMS, V_CELDA_MIN_BMS,bus_data.rx_voltaje_min_celda_bms, regular_zone, voltaje_min_celda_bms_state);
nivel_bateria_bms_state = actual_estate_function(NIV_BAT_MAX_BMS, NIV_BAT_MIN_BMS, bus_data.rx_nivel_bateria_bms, regular_zone, nivel_bateria_bms_state);


voltaje_bateria_dcdc_state = actual_estate_function(V_BAT_MAX_DCDC, V_BAT_MIN_DCDC, bus_data.rx_voltaje_bateria_dcdc, regular_zone, voltaje_bateria_dcdc_state);
t_max_dcdc_state = actual_estate_function(T_MAX_DCDC, T_MIN_DCDC, bus_data.rx_t_max_dcdc, regular_zone, t_max_dcdc_state);


velocidad_inv_state = actual_estate_function(VEL_MAX_INV, VEL_MIN_INV, bus_data.rx_velocidad_inv, regular_zone, velocidad_inv_state);
temp_inv_state = actual_estate_function(T_MAX_INV, T_MIN_INV,bus_data.rx_temp_inv, regular_zone, temp_inv_state);
V_inv_state = actual_estate_function(V_MAX_INV,V_MIN_INV, bus_data.rx_V_inv, regular_zone, V_inv_state);
I_inv_state = actual_estate_function(I_MAX_INV, I_MIN_INV, bus_data.rx_I_inv, regular_zone, I_inv_state);
temp_max_inv_state = actual_estate_function(T_MAX_INV, T_MIN_INV, bus_data.rx_temp_inv, regular_zone, temp_max_inv_state);
temp_motor_inv_state = actual_estate_function(T_MAX_MOTOR, T_MIN_MOTOR, bus_data.rx_temp_motor_inv, regular_zone, temp_motor_inv_state);
potencia_inv_state = actual_estate_function(P_MAX_INV, P_MIN_INV, bus_data.rx_potencia_inv, regular_zone, potencia_inv_state);

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/*
switch (voltaje_bms_state){
    //un caso para cuando el bms aun no este encendido y no se consuma cpu haciendo comprobaciones

case OK:  constant-expression 
     code 
    if((bus_data.rx_voltaje_bms > (V_MAX_BMS * (regular_zone + 1))) | (bus_data.rx_voltaje_bms < (V_MIN_BMS*(-regular_zone + 1)))) {
        voltaje_bms_state = PROBLEM; 

    }else if(((bus_data.rx_voltaje_bms < (V_MAX_BMS * (regular_zone + 1))) & (bus_data.rx_voltaje_bms > (V_MAX_BMS * (-regular_zone + 1))))  | 
      ((bus_data.rx_voltaje_bms > (V_MIN_BMS*(-regular_zone + 1))) & (bus_data.rx_voltaje_bms < (V_MIN_BMS*(regular_zone + 1))))){
        voltaje_bms_state = REGULAR; 

    }else{
        voltaje_bms_state =  DATA_PROBLEM;

    }
 
    break;
case PROBLEM:

    if((bus_data.rx_voltaje_bms < (V_MAX_BMS * (-regular_zone + 1))) & (bus_data.rx_voltaje_bms > (V_MIN_BMS*(regular_zone + 1)))) {
        voltaje_bms_state = OK; 

    }else if(((bus_data.rx_voltaje_bms < (V_MAX_BMS * (regular_zone + 1))) & (bus_data.rx_voltaje_bms > (V_MAX_BMS * (-regular_zone + 1))))  | 
      ((bus_data.rx_voltaje_bms > (V_MIN_BMS*(-regular_zone + 1))) & (bus_data.rx_voltaje_bms < (V_MIN_BMS*(regular_zone + 1))))){
        voltaje_bms_state = REGULAR; 

    }else{
        voltaje_bms_state =  DATA_PROBLEM;

    }
    break;

default:
    break;
}
*/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}
uint8_t resultado;

uint8_t actual_estate_function (int D_max, int D_min, int Data, int reg_percent, char actual_estate){

           // lo hago con int?? con char?? con uint??, como doy como resultado los valores del enum ??


        if (actual_estate == OK){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;

        }else if(actual_estate == REGULAR){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;

  
        }else if(actual_estate == PROBLEM){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;


        }else if(actual_estate == DATA_PROBLEM){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;
            
        }else{
            return DATA_PROBLEM;
        }



}
char comparaciones (int D_max, int D_min, int Data, int reg_percent){

            if((Data < (D_max * (-reg_percent + 1))) & (Data > (D_min*(reg_percent + 1)))) {
                return OK; 

            }else if((Data > (D_max * (reg_percent + 1))) | (Data < (D_min*(-reg_percent + 1)))) {
                return REGULAR; 

            }else if(((Data < (D_max * (reg_percent + 1))) & (Data > (D_max * (-reg_percent + 1))))  | 
            ((Data > (D_min*(-reg_percent + 1))) & (Data < (D_min*(reg_percent + 1))))){
                return PROBLEM; 

            }else{
                return DATA_PROBLEM;

            }

}