#ifndef US_H_
#define US_H_

#include "State.h"
/* States */

enum US_STATE {
    US_Busy
};

extern enum US_STATE US_state_id;
/* State Pointer */
extern void (*US_state_ptr)(void);

STATE_DEFINE(US_Busy);

void US_init(void);
void US_print_state(char *func);
int US_random_distance(int start, int end);
void US_get_distance(int *distance);

#endif /* US_H_ */
