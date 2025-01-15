#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* State function Generator */

#define STATE_DEFINE(statefun) void ST_##statefun()
#define STATE(statefun) ST_##statefun
#define QUOTE_MARK(seq) "\""#seq"\""
#define QUOTE(seq) #seq
#define EXPAND_QUOTE(s) QUOTE(s)


void US_get_distance(int *distance);
void DC_set_speed(int speed);

#endif /* STATE_H_ */
