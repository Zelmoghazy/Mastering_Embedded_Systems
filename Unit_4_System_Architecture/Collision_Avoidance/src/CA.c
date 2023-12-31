#include "CA.h"

/* Private Vars */
static int CA_speed;
static int CA_distance;
static int CA_threshold = 50;

enum CA_STATE CA_state_id;

void (*CA_state_ptr)(void);

void CA_print_state(char *func)
{
    printf("%s State :\n",func);
    printf("Distance = %d Speed = %d\n",CA_distance,CA_speed);
}

STATE_DEFINE(CA_Event_Check)
{
    CA_state_id = CA_Event_Check;
    US_get_distance(&CA_distance);
    /* Event Check */
    if(CA_distance <= CA_threshold){
        CA_state_ptr = STATE(CA_Waiting);
        CA_state_ptr();
    }else{
        CA_state_ptr = STATE(CA_Driving);
        CA_state_ptr();
    }
}

STATE_DEFINE(CA_Waiting)
{
    /* State Name */
    CA_state_id = CA_Waiting;
    CA_print_state(EXPAND_QUOTE(STATE(CA_Waiting)));

    /* State Action */
    CA_speed = 0;
    DC_set_speed(CA_speed);

    CA_state_ptr = STATE(CA_Event_Check);
}

STATE_DEFINE(CA_Driving)
{
    /* State Name */
    CA_state_id = CA_Driving;
    CA_print_state(EXPAND_QUOTE(STATE(CA_Driving)));

    /* State Action */
    CA_speed = 30;
    DC_set_speed(CA_speed);

    CA_state_ptr = STATE(CA_Event_Check);
}
