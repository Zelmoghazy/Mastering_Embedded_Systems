#include "CA.h"
#include "US.h"
#include "DC.h"


void setup()
{
    /** Initialize :
            * Drivers
            * IRQ
            * HAL (Sensors , Motors)
            * Block
     */
    /* Set States Pointers */
    srand(time(NULL));
    US_init();
    DC_init();

    CA_state_ptr = STATE(CA_Waiting);
    US_state_ptr = STATE(US_Busy);
    DC_state_ptr = STATE(DC_Idle);
}

void loop()
{
    for(;;)
    {
        CA_state_ptr();
        US_state_ptr();
        DC_state_ptr();

        getchar();
    }   
}

int main(void)
{
    setup();
    loop();
    return 0;
}