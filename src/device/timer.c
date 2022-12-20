#include <timer.h>
#include <mmio.h>
#include <time.h>
#include <sys/time.h>

static uint32_t *rtc_port_base = NULL;

static struct timeval boot_time;
static struct timeval now;

uint64_t get_time(){
	gettimeofday(&now, NULL);
	long seconds = now.tv_sec - boot_time.tv_sec;
	long useconds = now.tv_usec - boot_time.tv_usec;
	return seconds * 1000000 + useconds + 500;
}

static void rtc_io_handler(uint32_t offset, int len, bool is_write){
	uint64_t time_now = get_time();
	rtc_port_base[0] = time_now;		//get_time();
	rtc_port_base[1] = time_now >> 32;	//get_time() >> 32;
}

void init_timer(){
	gettimeofday(&boot_time, NULL);
	rtc_port_base = (uint32_t *) new_space(8);
	add_mmio_map("rtc", CONFIG_TIMER_MMIO, rtc_port_base, 8, rtc_io_handler);
}
