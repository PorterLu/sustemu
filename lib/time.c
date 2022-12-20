#include "time.h"

uint64_t get_time(){
	uint64_t time = *((volatile uint32_t*)(CONFIG_TIMER_MMIO+4));	
	time = (time << 32) | *((volatile uint32_t*)(CONFIG_TIMER_MMIO));
}
