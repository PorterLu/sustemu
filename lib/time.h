#ifndef __TIME_H__
#define __TIME_H__

#include <stdint.h>
#define CONFIG_TIMER_MMIO 0xa0000048
uint64_t get_time();

#endif
