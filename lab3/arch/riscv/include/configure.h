#ifndef CONFIGURE_H
#define CONFIGURE_H

// TIME_SLICE is the interval of time interruption
#ifndef PREEMPTIVE
#define TIME_SLICE 500000
#else
#define TIME_SLICE 10000000
#endif

#endif