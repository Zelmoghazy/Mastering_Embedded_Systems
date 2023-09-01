#include "US.h"

/* Private Vars */
static int US_distance;

enum US_STATE US_state_id;

void (*US_state_ptr)(void);


void US_init(void)
{
    printf("US_init ..\n");
}

void US_print_state(char *func)
{
    printf("%s State :\n",func);
    printf("Distance = %d\n",US_distance);
}

STATE_DEFINE(US_Busy)
{
    /* State Name */
    US_state_id = US_Busy;
    /* State Action */
    US_distance = US_random_distance(45,55);
    US_print_state(EXPAND_QUOTE(STATE(US_Busy)));
    US_state_ptr = STATE(US_Busy);
}

int US_random_distance(int start, int end)
{
    if (end + 1 - start != 0){
        int r = rand() % (end + 1 - start) + start;
        return r;
    }else{
        return -1;
    }
}

void US_get_distance(int *distance)
{
    printf("US -> Distance = %d -> CA \n",US_distance);
    *distance = US_distance;
}
