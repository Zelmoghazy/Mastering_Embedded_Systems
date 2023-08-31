#ifndef CA_H_
#define CA_H_

#include "State.h"
/* States */

enum CA_STATE {
    CA_Waiting,
    CA_Driving
};

extern enum CA_STATE CA_state_id;

STATE_DEFINE(CA_Waiting);

STATE_DEFINE(CA_Driving);

/* State Pointer */
extern void (*CA_state_ptr)(void);

int CA_get_random_distance(int start, int end);

#endif /* CA_H_ */
