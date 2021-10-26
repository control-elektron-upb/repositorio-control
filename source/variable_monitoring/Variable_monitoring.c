#include <stdint.h>
#include "variable_monitoring/Variable_monitoring.h"


/* 

S1: mal > max bien min > mal  
S2: bien > max bien min > mal 
S3: mal > max bien min > bien


*/
uint8_t voltaje_bms_state;
uint8_t corriente_bms_state;						
uint8_t voltaje_min_celda_bms_state;				
uint8_t potencia_bms_state;						
uint8_t t_max_bms_state;							
uint8_t nivel_bateria_bms_state;					
uint8_t voltaje_bateria_dcdc_state;				
uint8_t t_max_dcdc_state;							
uint8_t velocidad_inv_state;						
uint8_t temp_inv_state;							
uint8_t V_inv_state;								
uint8_t I_inv_state;								
uint8_t temp_max_inv_state;						
uint8_t temp_motor_inv_state;					
uint8_t potencia_inv_state;	

int regular_zone = 0.05; //+-5% de zona en regular

void variable_monitoring (void){



/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
switch (voltaje_bms_state){
    //un caso para cuando el bms aun no este encendido y no se consuma cpu haciendo comprobaciones

case OK: /* constant-expression */
    /* code */
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
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
switch (corriente_bms_state){

case OK: /* constant-expression */
    /* code */
    if((bus_data.rx_corriente_bms > (I_MAX_BMS * (regular_zone + 1))) | (bus_data.rx_corriente_bms < (I_MIN_BMS*(-regular_zone + 1)))) {
        corriente_bms_state = PROBLEM; 

    }else if(((bus_data.rx_corriente_bms < (I_MAX_BMS * (regular_zone + 1))) & (bus_data.rx_corriente_bms > (I_MAX_BMS * (-regular_zone + 1))))  | 
      ((bus_data.rx_corriente_bms > (I_MIN_BMS*(-regular_zone + 1))) & (bus_data.rx_corriente_bms < (I_MIN_BMS*(regular_zone + 1))))){
        corriente_bms_state = REGULAR; 

    }else{
        corriente_bms_state =  DATA_PROBLEM;

    }
 
    break;
case PROBLEM:

    if((bus_data.rx_corriente_bms < (I_MAX_BMS * (-regular_zone + 1))) & (bus_data.rx_corriente_bms > (I_MIN_BMS*(regular_zone + 1)))) {
        corriente_bms_state = OK; 

    }else if(((bus_data.rx_corriente_bms < (I_MAX_BMS * (regular_zone + 1))) & (bus_data.rx_corriente_bms > (I_MAX_BMS * (-regular_zone + 1))))  | 
      ((bus_data.rx_corriente_bms > (I_MIN_BMS*(-regular_zone + 1))) & (bus_data.rx_corriente_bms < (I_MIN_BMS*(regular_zone + 1))))){
        corriente_bms_state = REGULAR; 

    }else{
        corriente_bms_state =  DATA_PROBLEM;

    }
    break;

default:
    break;
}
}