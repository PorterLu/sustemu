#ifndef __TIMER_H__
#define __TIMER_H__
#include <common.h>

#define CONFIG_TIMER_MMIO 0xa0000048

void init_timer();
uint64_t get_time();

#endif
