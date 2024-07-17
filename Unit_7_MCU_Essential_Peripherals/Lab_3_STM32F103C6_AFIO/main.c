#include "Platform_Types.h"
#include "Macros.h"

#define RCC_BASE    0x40021000
#define RCC_APB2ENR ((*(vuint32_t *) (RCC_BASE + 0x18)))
#define RCC_CFGR    ((*(vuint32_t *) (RCC_BASE + 0x04)))
#define RCC_CR      ((*(vuint32_t *) (RCC_BASE + 0x0)))

#define RCC_IOP_A_EN 2
#define RCC_IOP_B_EN 3

#define PORT_A_BASE 0x40010800
#define PORT_B_BASE 0x40010C00

#pragma pack(1)
typedef struct GPIO
{
    vuint32_t CRL; 
    vuint32_t CRH; 
    vuint32_t IDR; 
    vuint32_t ODR; 
    vuint32_t BSRR; 
    vuint32_t BRR; 
    vuint32_t LCKR; 
}GPIO;

#define GPIO_A ((GPIO *) (PORT_A_BASE))
#define GPIO_B ((GPIO *) (PORT_B_BASE))

typedef union Reg_t {
    vuint32_t all_fields;
    struct{
        vuint32_t pin0 :1;
        vuint32_t pin1 :1;
        vuint32_t pin2 :1;
        vuint32_t pin3 :1;
        vuint32_t pin4 :1;
        vuint32_t pin5 :1;
        vuint32_t pin6 :1;
        vuint32_t pin7 :1;
        vuint32_t pin8 :1;
        vuint32_t pin9 :1;
        vuint32_t pin10:1;
        vuint32_t pin11:1;
        vuint32_t pin12:1;
        vuint32_t pin13:1;
        vuint32_t pin14:1;
        vuint32_t pin15:1;
        vuint32_t pin16:1;
        vuint32_t pin17:1;
        vuint32_t pin18:1;
        vuint32_t pin19:1;
        vuint32_t pin20:1;
        vuint32_t pin21:1;
        vuint32_t pin22:1;
        vuint32_t pin23:1;
        vuint32_t pin24:1;
        vuint32_t pin25:1;
        vuint32_t pin26:1;
        vuint32_t pin27:1;
        vuint32_t pin28:1;
        vuint32_t pin29:1;
        vuint32_t pin30:1;
        vuint32_t pin31:1;
    }pin;
}Reg_t;

volatile Reg_t* R_ODR_A = (volatile Reg_t*)(PORT_A_BASE + 0x0C);
volatile Reg_t* R_ODR_B = (volatile Reg_t*)(PORT_B_BASE + 0x0C);

volatile Reg_t* R_IDR_A = (volatile Reg_t*)(PORT_A_BASE + 0x08);
volatile Reg_t* R_IDR_B = (volatile Reg_t*)(PORT_B_BASE + 0x08);


// PA11 -> input floating
// PA12 -> Alternative function push pull
void GPIO_init() 
{
    // Enable GPIO_A Clock
    SET(RCC_APB2ENR,RCC_IOP_A_EN);

    // Enable GPIO_B Clock
    SET(RCC_APB2ENR,RCC_IOP_B_EN);
    
    // PA1 input HighZ
    CLEAR_RANGE(GPIO_A->CRL,4,7);
    SET(GPIO_A->CRL,6);

    // PB1 Output push pull mode
    CLEAR_RANGE(GPIO_B->CRL,4,7);
    SET(GPIO_B->CRL,4);

    // PA13 input HighZ
    CLEAR_RANGE(GPIO_A->CRH,20,23);
    SET(GPIO_A->CRH,22);

    // PB13 Output Push pull mode
    CLEAR_RANGE(GPIO_B->CRH,20,23);
    SET(GPIO_B->CRH,20);
}

int main(void)
{
    GPIO_init();

    for (;;)
    {
        // PA1 -> External PUR (Default = 1)
        if(!R_IDR_A->pin.pin1)
        {
            R_ODR_B->pin.pin1 ^= 1;
            while(!R_IDR_A->pin.pin1); // Single Press
        }

        // PA133 -> External PDR (Default = 0)
        if(R_IDR_A->pin.pin13)
        {
            R_ODR_B->pin.pin13 ^= 1; // Multi Pressing
            for(int i = 0; i < 1000; i++);
        }
    }
    return 0;
}

void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief CAN MSP Initialization
* This function configures the hardware resources used in this example
* @param hcan: CAN handle pointer
* @retval None
*/
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hcan->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }

}
