
#include <stdint.h>

#include "variable_monitoring.h"

#define DEFAULT_STATE  DATA_PROBLEM


/*
0= OK
1= PROBLEM
2= REGULAR
3=DATA PROBLEM
*/



void variable_monitoring (void)
{
    Bms_States-> 
}





uint8_t voltaje_bms_state = DEFAULT_STATE;
uint8_t corriente_bms_state = DEFAULT_STATE;									
uint8_t potencia_bms_state = DEFAULT_STATE;	
uint8_t t_max_bms_state = DEFAULT_STATE;	
uint8_t voltaje_min_celda_bms_state = DEFAULT_STATE;											
uint8_t nivel_bateria_bms_state = DEFAULT_STATE;		

uint8_t voltaje_bateria_dcdc_state = DEFAULT_STATE;				
uint8_t t_max_dcdc_state = DEFAULT_STATE;

uint8_t velocidad_inv_state = DEFAULT_STATE;	
uint8_t temp_motor_inv_state = DEFAULT_STATE;					
uint8_t V_inv_state = DEFAULT_STATE;								
uint8_t I_inv_state = DEFAULT_STATE;								
uint8_t temp_max_inv_state = DEFAULT_STATE;							
uint8_t potencia_inv_state = DEFAULT_STATE;	

float regular_zone = 0.05; //+-5% de zona en regular




void variable_monitorig (void)
{
    voltaje_bms_state = actual_estate_function(V_MAX_BMS, V_MIN_BMS, bus_data.rx_voltaje_bms, regular_zone, voltaje_bms_state);
}

var_state current_var_state(float D_max, float D_min, float Data, float reg_percent, var_state current_state)
{
        var_state resultado;

        if (current_state == OK){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;

        }else if(current_state == REGULAR){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;

  
        }else if(current_state == PROBLEM){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;


        }else if(current_state == DATA_PROBLEM){

            resultado = comparaciones(D_max,  D_min, Data, reg_percent); 
            return resultado;
            
        }else{
            return DATA_PROBLEM;
        }
}
var_state comparaciones (float D_max, float D_min, float Data, float reg_percent){

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