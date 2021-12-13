/**
 * @file can.c
 * @author Subgrupo Control
 * @brief Implementación código de recepción y envío de datos CAN
 * @version 0.1
 * @date 2021-11-28
 *
 * @copyright Copyright (c) 2021
 *
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "can.h"

/***********************************************************************************************************************
 * Macros
 **********************************************************************************************************************/

/*#define CAN_TX_MAILBOX0             (0x00000001U)  !< Tx Mailbox 0  */
/*#define CAN_TX_MAILBOX1             (0x00000002U)  !< Tx Mailbox 1  */
/*#define CAN_TX_MAILBOX2             (0x00000004U)  !< Tx Mailbox 2  */
#define TIME_DELTA		1

/***********************************************************************************************************************
 * Variables definitions
 **********************************************************************************************************************/

static CAN_TxHeaderTypeDef txHeader;                // CAN Tx message header structure instance

static CAN_RxHeaderTypeDef rxHeader;                // CAN Rx message header structure definition

decode_status_t flag_decodificar = NO_DECODIFICA;   // Bandera para ejecutar bloque de decodificación de datos

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

/**
 * @brief Función de envío de datos a driver CAN.
 * 
 * Realiza el envío de los datos que se encuentran en el bus de salida CAN (bus 3) al driver CAN que interactúa con el
 * tranceiver de CAN de la tarjeta.
 * 
 * @param bus_can_output Puntero a estructura bus de salida CAN
 * @retval None
 */
void CAN_Driver_Send(typedef_bus2_t *bus_can_output)
{
	uint8_t msg = 0U;
	uint32_t id = 0U;
    uint32_t mailbox;

	txHeader.DLC = 1; 				// one byte to transmit
	txHeader.IDE = CAN_ID_STD; 		// standard identifier
	txHeader.RTR = CAN_RTR_DATA;    // data frame

    /* --------------- Send autokill --------------- */

	msg = bus_can_output->autokill;
	txHeader.StdId = ID_AUTOKILL;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------- Send estado_manejo ------------- */

	msg = bus_can_output->estado_manejo;
	txHeader.StdId = ID_ESTADO_MANEJO;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------- Send estado_falla ------------- */

	msg = bus_can_output->estado_falla;
	txHeader.StdId = ID_ESTADO_FALLA;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------- Send nivel_velocidad ------------- */

	msg = bus_can_output->nivel_velocidad;
	txHeader.StdId = ID_NIVEL_VELOCIDAD;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------- Send nivel_voltaje ------------- */

	msg = bus_can_output->nivel_voltaje;
	txHeader.StdId = ID_NIVEL_VOLTAJE;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------- Send control_ok ------------- */

	msg = bus_can_output->control_ok;
	txHeader.StdId = ID_CONTROL_OK;

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);

	if(mailbox == CAN_TX_MAILBOX2)
    {										
		while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );	
	}

    HAL_Delay(TIME_DELTA);

    /* ------------ Send async messages ------------ */

    /* 10-12-2021 aún no se piensan implementar mensajes asincrónicos */

    /*
	for (uint8_t i = 0; i < LENGTH_ASYNC_MSG; i++ ){
		id = bus_can_output->async[i].can_adress;
		msg = bus_can_output->async[i].value;
		if(id != 0){
			HAL_Delay(TIME_DELTA);
			txHeader.StdId = id;
			HAL_CAN_AddTxMessage(&hcan1, &txHeader, &msg, &mailbox);
			if(mailbox == CAN_TX_MAILBOX2){
				while( HAL_CAN_IsTxMessagePending(&hcan1, CAN_TX_MAILBOX0) );
			}
		}
	}
    */
}

/**
 * @brief Función handler de interrupción de recepción de datos de driver CAN.
 * 
 * Realiza la recepción de los datos que llegan desde el driver CAN y los guarda en la estructura de bus de entrada
 * de datos CAN (bus 2). Cuando se active la interrupción, activa la bandera de decodificación para indicar que
 * se puede ejecutar el bloque de decodificación de los datos que vienen de CAN.
 * 
 * @param None
 * @retval None
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    uint8_t data;                   // where the payload of the Rx frame will be stored.

    HAL_CAN_IRQHandler(&hcan1);
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, &data);

    flag_decodificar = DECODIFICA;  // activa bandera para decodificar

    /* switch en el cual, según el standard identifier que se reciba, se guarda el dato 
    en las variables pertinentes del bus de recepción CAN (bus 3) */
    switch(rxHeader.StdId) 
    {
    
    /* ------------- Periféricos ------------- */

    case ID_PEDAL:
        bus_can_input.pedal = data;
        break;
    case ID_DEAD_MAN:
        bus_can_input.dead_man = data;
        break;
    case ID_BUTTONS_CHANGE_STATE:
        bus_can_input.buttons_change_state = data;
        break;
    case ID_PERIPHERALS_OK:
        bus_can_input.peripherals_ok = data;
        break;
    
    /* ----------------- BMS ----------------- */

    case ID_VOLTAJE_BMS:
        bus_can_input.voltaje_bms = data;
        break;
    case ID_CORRIENTE_BMS:
        bus_can_input.corriente_bms = data;
    case ID_VOLTAJE_MIN_CELDA_BMS:
        bus_can_input.voltaje_min_celda_bms = data;
    case ID_POTENCIA_BMS:
        bus_can_input.potencia_bms = data;
    case ID_T_MAX_BMS:
        bus_can_input.t_max_bms = data;
    case ID_NIVEL_BATERIA_BMS:
        bus_can_input.nivel_bateria_bms = data;
    case ID_BMS_OK:
        bus_can_input.bms_ok = data;

    /* ---------------- DCDC ----------------- */

    case ID_VOLTAJE_BATERIA_DCDC:
        bus_can_input.voltaje_bateria_dcdc = data;
        break;
    case ID_VOLTAJE_SALIDA_DCDC:
        bus_can_input.voltaje_salida_dcdc = data;
    case ID_T_MAX_DCDC:
        bus_can_input.t_max_dcdc = data;
    case ID_POTENCIA_DCDC:
        bus_can_input.potencia_dcdc = data;

    /* --------------- Inversor -------------- */
    
    case ID_VELOCIDAD_INV:
        bus_can_input.velocidad_inv = data;
        break;
    case ID_V_INV:
        bus_can_input.V_inv = data;
    case ID_I_INV:
        bus_can_input.I_inv = data;
    case ID_TEMP_MAX_INV:
        bus_can_input.temp_max_inv = data;
    case ID_TEMP_MOTOR_INV:
        bus_can_input.temp_motor_inv = data;
    case ID_POTENCIA_INV:
        bus_can_input.potencia_inv = data;
    case ID_INVERSOR_OK:
        bus_can_input.inversor_ok = data;
    }
}
