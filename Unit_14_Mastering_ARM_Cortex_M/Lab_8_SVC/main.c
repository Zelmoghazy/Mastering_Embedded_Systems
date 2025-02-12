#include "stm32f103xb.h"

volatile uint32_t systick_counter = 0;
volatile uint32_t res = 0;

#define LED_PIN     (1 << 12)
#define LED_PORT    GPIOB

void SysTick_Handler(void) 
{
    systick_counter++;
    if(systick_counter % 500 == 0){
        LED_PORT->ODR ^= LED_PIN;  
    }
}

void ConfigureGPIO(void) 
{
    RCC->APB2ENR    |= (1 << 3);
    LED_PORT->CRH   &= ~(0xF << 16); 
    LED_PORT->CRH   |=  (0x1 << 16); 
}

void ConfigureSysTick(void) 
{
    NVIC_SetPriority(SysTick_IRQn, 2);
    
    SysTick->LOAD = (8000000 / 1000) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk | 
                    SysTick_CTRL_ENABLE_Msk;
}

/*
    - The advantage of passing the address of the stack frame is that 
      it allows the C handler to extract any information in the stack frame,
      including the stacked registers.

    - This is essential if you want to pass parameters to a SVC service 
      and get a return value for the SVC service.
 */
void os_svc_services(int *stack_fp)
{
    // Stack frame contains:
    // r0, r1, r2, r3, r12, r14, the return address and xPSR
    // - Stacked R0   = svc_args[0] -> stack_fp
    // - Stacked R1   = svc_args[1]
    // - Stacked R2   = svc_args[2]
    // - Stacked R3   = svc_args[3]
    // - Stacked R12  = svc_args[4]
    // - Stacked LR   = svc_args[5]
    // - Stacked PC   = svc_args[6] <-
    // - Stacked xPSR = svc_args[7]

    uint8_t svc_number;

    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;

    /*
        __asm("LDR R0, [R0, #24]");     // Get stacked PC from stack frame
        __asm("LDRB R0, [R0, #-2]");    // Get first byte of the SVC instruction in R0 
     */
    svc_number = ((char *) stack_fp[6])[-2];    //Memory[(Stacked PC)-2]
    stacked_r0 = stack_fp[0];
    stacked_r1 = stack_fp[1];
    stacked_r2 = stack_fp[2];
    stacked_r3 = stack_fp[3];

    /*
        If your SVC service needs to return a value,
        you need to return the value using the stack frame. 
     */
    switch(svc_number)
    {
        case 1:
            stack_fp[0] = stacked_r0 + stacked_r1;
            break;
        case 2:
            stack_fp[0] = stacked_r0 - stacked_r1;
            break;
        case 3:
            stack_fp[0] = stacked_r0 * stacked_r1;
            break;
        default:
            break;
    }
}

/*
    - a naked function does not have compiler-generated prologue or epilogue.
      All the register saving and stack manipulation must be done by 
      the programmer using inline assembly

    - The only statements that can be safely included in naked functions 
      are asm statements that do not have operands.
      All other statements, including declarations of local variables,
      if statements, and so forth, should be avoided.
 */
__attribute ((naked)) void SVC_Handler()
{
    __asm("TST LR, #4");            // Check used SP by testing bit 2 of EXC_RETURN
    __asm("ITE EQ");    
    __asm("MRSEQ R0, MSP");         // Use MSP copied to R0
    __asm("MRSNE R0, PSP");         // Use PSP copied to R0

    /* Check number */
    // __asm("LDR R0, [R0, #24]");     // Get stacked PC from stack frame
    // __asm("LDRB R0, [R0, #-2]");    // Get first byte of the SVC instruction in R0

    __asm("B os_svc_services");     // Jump to C code
}


int os_svc_set(int a, int b, int svc_id)
{
    int res = 0;

    switch(svc_id)
    {
        case 1:
            __asm("SVC #0x01");
            break;
        case 2:
            __asm("SVC #0x02");
            break;
        case 3:
            __asm("SVC #0x03");
            break;
        default:
            break;
    }

    // Get the result from R0
    __asm("MOV %0, R0"
          : "=r" (res));

    return res;
}

int main(void) 
{
    ConfigureGPIO();
    ConfigureSysTick();
    __enable_irq();

    res = os_svc_set(3, 3, 1);  // add  -> 6
    res = os_svc_set(3, 3, 2);  // sub  -> 0
    res = os_svc_set(3, 3, 3);  // mult -> 9

    
    for(;;)
    {
        if(res)
        {
            res = 0;
        }

    }
}