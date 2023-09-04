#include "DC.h"

/* Private Vars */
static int DC_speed;

enum DC_STATE DC_state_id;

void (*DC_state_ptr)(void);

void DC_init(void)
{
    printf("DC_init...\n");
}

void DC_set_speed(int speed)
{
    DC_speed = speed;
    DC_state_ptr = STATE(DC_Busy);
    printf("CA -> Speed = %d -> DC \n",DC_speed);
}

void DC_print_state(char *func)
{
    printf("%s State :\n",func);
    printf("Speed = %d\n",DC_speed);
}

STATE_DEFINE(DC_Idle)
{
    /* State Name */
    DC_state_id = DC_Idle;
    DC_print_state(EXPAND_QUOTE(STATE(DC_Idle)));
}

STATE_DEFINE(DC_Busy)
{
    /* State Name */
    DC_state_id = DC_Busy;
    DC_print_state(EXPAND_QUOTE(STATE(DC_Busy)));
    DC_state_ptr = STATE(DC_Idle);
}
