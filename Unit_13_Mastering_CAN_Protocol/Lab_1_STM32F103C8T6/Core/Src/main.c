#include "main.h"
#include <stdint.h>

CAN_HandleTypeDef hcan;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);


void CAN_TX (uint32_t ID, uint8_t DLC, uint8_t* payload)
{
  uint8_t no_free_txMailBox = 0;
  uint32_t pTxMailbox = 0;
  CAN_TxHeaderTypeDef pHeader;

  pHeader.DLC   = DLC;
  pHeader.IDE   = CAN_ID_STD;    // Standard Id
  pHeader.RTR   = CAN_RTR_DATA;  // Data frame
  pHeader.StdId = ID;

  // Get number of free Tx mailboxes
  no_free_txMailBox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
  if(no_free_txMailBox){
    // Request Transmission of a new message
    if(HAL_CAN_AddTxMessage(&hcan,&pHeader,payload,&pTxMailbox) != HAL_OK){
      Error_Handler();
    }
    // Check if a transmission request is pending on the selected Tx Mailboxes (Polling Mechanism).
    while(HAL_CAN_IsTxMessagePending(&hcan,pTxMailbox));
    //Wait until message in TxMailbox is transmitted
  }
}

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();

  //* Start bxCan ->  running state
  if(HAL_CAN_Start(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t TX_DATA[8] = {'C','A','N',' ','N','O',':',' '};
  uint8_t FrameNo = 0;

  while (1)
  {
    TX_DATA[7] = FrameNo++;
    /* CAN_TX(ID,DLC,PAYLOAD) */
    CAN_TX(0x3FF, 8, TX_DATA);  // Transmit and wait until its done
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 1;
  hcan.Init.Mode = CAN_MODE_LOOPBACK;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
