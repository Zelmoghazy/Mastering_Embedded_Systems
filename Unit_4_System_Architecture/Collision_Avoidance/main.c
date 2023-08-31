#include "CA.h"


void setup()
{
    /** Initialize :
            * Drivers
            * IRQ
            * HAL (Sensors , Motors)
            * Block
     */
    /* Set States Pointers */
    CA_state_ptr = STATE(CA_Waiting);
}

void loop()
{
    for(;;)
    {
        CA_state_ptr();
        getchar();
    }   
}

int main(void)
{
    setup();
    loop();
    return 0;
}