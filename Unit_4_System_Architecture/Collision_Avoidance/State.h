#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* State function Generator */

#define STATE_DEFINE(statefun) void ST_##statefun()
#define STATE(statefun) ST_##statefun
#define QUOTE(seq) "\""#seq"\""
#define EXPAND_QUOTE(s) QUOTE(s)


#endif /* STATE_H_ */
