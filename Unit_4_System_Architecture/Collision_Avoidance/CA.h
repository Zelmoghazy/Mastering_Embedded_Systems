#ifndef CA_H_
#define CA_H_

#include "State.h"
/* States */

enum CA_STATE {
    CA_Waiting,
    CA_Driving,
    CA_Event_Check
};

extern enum CA_STATE CA_state_id;
/* State Pointer */
extern void (*CA_state_ptr)(void);

STATE_DEFINE(CA_Waiting);
STATE_DEFINE(CA_Driving);
STATE_DEFINE(CA_Event_Check);

#endif /* CA_H_ */
