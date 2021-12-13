/**
 * @file can_config.c
 * @author Subgrupo Control
 * @brief Código de inicialización y configuración del CAN
 * @version 0.1
 * @date 2021-12-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/

#include "can_config.h"

/***********************************************************************************************************************
 * Private variables definitions
 **********************************************************************************************************************/

CAN_HandleTypeDef hcan1;             		//CAN handle structure instance

static CAN_FilterTypeDef aFilterConfig;     //CAN filter configuration structure instance

/***********************************************************************************************************************
 * Private functions prototypes
 **********************************************************************************************************************/

static void CAN1_HandleInit(void);

static void CAN1_FilterConfig(void);

static void ErrorHandler(void);

/***********************************************************************************************************************
 * Public functions implementation
 **********************************************************************************************************************/

void CAN_Driver_Init(void) 
{
    CAN1_HandleInit();
    CAN1_FilterConfig();    
}

/***********************************************************************************************************************
 * Private functions implementation
 **********************************************************************************************************************/

/**
 * @brief CAN1 Handle Structure Instance Initialization Function.
 * 
 * @param None
 * @retval None
 */
static void CAN1_HandleInit(void)
{
    hcan1.Instance = CAN1;                      
    hcan1.Init.Prescaler = 10;
    hcan1.Init.Mode = CAN_MODE_NORMAL;
    hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
    hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
    hcan1.Init.TimeTriggeredMode = DISABLE;
    hcan1.Init.AutoBusOff = ENABLE;
    hcan1.Init.AutoWakeUp = DISABLE;
    hcan1.Init.AutoRetransmission = DISABLE;
    hcan1.Init.ReceiveFifoLocked = DISABLE;
    hcan1.Init.TransmitFifoPriority = DISABLE;
    
    if (HAL_CAN_Init(&hcan1) != HAL_OK)
    {
        Driver_CAN_ErrorHandler();
    }
}

/**
 * @brief CAN1 Filter Configuration Function.
 * 
 * @param None
 * @retval None
 */
static void CAN1_FilterConfig(void)
{
	//uint32_t filter_list [13];

	aFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	aFilterConfig.FilterBank = 0;
	aFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	aFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	aFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	aFilterConfig.FilterIdHigh = ID_ESTADO_MANEJO<<5;					 	//id1, se toman primeros 16 bits
	aFilterConfig.FilterIdLow = ID_ESTADO_FALLA<<5;							//Id2
	aFilterConfig.FilterMaskIdHigh = ID_CONTROL_OK<<5;
	aFilterConfig.FilterMaskIdLow = ID_VOLTAJE_BMS<<5;
	aFilterConfig.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &aFilterConfig);

	aFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	aFilterConfig.FilterBank = 1;
	aFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	aFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	aFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	aFilterConfig.FilterIdHigh = ID_CORRIENTE_BMS<<5;					 	//id1, se toman primeros 16 bits
	aFilterConfig.FilterIdLow = ID_POTENCIA_BMS<<5;							//Id2
	aFilterConfig.FilterMaskIdHigh = ID_NIVEL_BATERIA<<5;
	aFilterConfig.FilterMaskIdLow = ID_VELOCIDAD<<5;
	aFilterConfig.SlaveStartFilterBank = 14;

	HAL_CAN_ConfigFilter(&hcan1, &aFilterConfig);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING); // activa interrupción
	HAL_CAN_Start(&hcan1);

	//HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * 
 * @retval None
 */
static void ErrorHandler(void)
{
  //__disable_irq();
  while (1)
  {
  }
}