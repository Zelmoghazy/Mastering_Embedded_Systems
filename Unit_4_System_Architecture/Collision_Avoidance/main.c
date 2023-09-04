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
    srand(time(NULL));
    US_init();
    DC_init();

    /* Set States Pointers */
    CA_state_ptr = STATE(CA_Event_Check);
    US_state_ptr = STATE(US_Busy);
    DC_state_ptr = STATE(DC_Idle);
}

void loop()
{
    for(;;)
    {
        US_state_ptr();
        CA_state_ptr();
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