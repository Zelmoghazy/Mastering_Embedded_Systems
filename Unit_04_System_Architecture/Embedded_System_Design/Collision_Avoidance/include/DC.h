#ifndef DC_H_
#define DC_H_

#include "State.h"
/* States */

enum DC_STATE {
    DC_Idle,
    DC_Busy
};

extern enum DC_STATE DC_state_id;
/* State Pointer */
extern void (*DC_state_ptr)(void);

STATE_DEFINE(DC_Idle);

STATE_DEFINE(DC_Busy);

void DC_init(void);
void DC_set_speed(int speed);
void DC_print_state(char *func);


#endif /* DC_H_ */
