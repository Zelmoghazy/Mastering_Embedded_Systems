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

STATE_DEFINE(CA_Waiting)
{
    /* State Name */
    CA_state_id = CA_Waiting;

    /* State Action */
    CA_speed = 0;

    CA_distance = CA_get_random_distance(45,55);
    /* Event Check */
    if(CA_distance <= CA_threshold){
        CA_state_ptr = STATE(CA_Waiting);
    }else{
        CA_state_ptr = STATE(CA_Driving);
    }
    CA_print_state(EXPAND_QUOTE(STATE(CA_Waiting)));
}

STATE_DEFINE(CA_Driving)
{
    /* State Name */
    CA_state_id = CA_Driving;

    /* State Action */
    CA_speed = 30;

    CA_distance = CA_get_random_distance(45,55);
    /* Event Check */
    if(CA_distance <= CA_threshold){
        CA_state_ptr = STATE(CA_Waiting);
    }else{
        CA_state_ptr = STATE(CA_Driving);
    }
    CA_print_state(EXPAND_QUOTE(STATE(CA_Driving)));
}


int CA_get_random_distance(int start, int end)
{
    if (end + 1 - start != 0){
        srand(time(NULL));
        int r = rand() % (end + 1 - start) + start;
        return r;
    }else{
        return -1;
    }
}
