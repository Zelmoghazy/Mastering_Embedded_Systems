#include "Platform_Types.h"
#include "Macros.h"

#define SYSCTL_RCGC2_R     (*((vuint32_t*)0x400FE108))
#define GPIO_PORT_F_DIR_R  (*((vuint32_t*)0x40025400))
#define GPIO_PORT_F_DEN_R  (*((vuint32_t*)0x4002551C))
#define GPIO_PORT_F_DATA_R (*((vuint32_t*)0x400253FC))


int main()
{
    vuint32_t delay_count;

    SYSCTL_RCGC2_R = 0x20;

    for(delay_count = 0; delay_count < 200; delay_count++);
    SET(GPIO_PORT_F_DIR_R,3);
    SET(GPIO_PORT_F_DEN_R,3);
    for(;;)
    {
        SET(GPIO_PORT_F_DATA_R,3);
        for(delay_count = 0; delay_count < 200000; delay_count++);
        CLEAR(GPIO_PORT_F_DATA_R,3);
        for(delay_count = 0; delay_count < 200000; delay_count++);
    }
    return 0;    
}
