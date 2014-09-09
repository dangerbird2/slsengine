#ifndef __SLS_TYPE_CLOCK_H__
#define __SLS_TYPE_CLOCK_H__

#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

typedef struct _slsClock slsClock;

struct slsClock {
	uint64_t first_time;
	uint64_t last_time;
	bool is_paused;
};

slsClock *slsClock_init(slsClock *self);
void slsClock_start(slsClock *self);
void slsClock_step(slsClock *self);

double slsClock_timeSinceStart(slsClock *self);
double slsClock_timeSinceStep(slsClock *self);

static inline double sls_diffclock(uint64_t timeA, uint64_t timeB)
{
	return (timeB - timeA) / (double) CLOCKS_PER_SEC;
}


#endif