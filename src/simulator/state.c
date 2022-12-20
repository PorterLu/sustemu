#include <state.h>
#include <stdint.h>
#include <utils.h>
#include <stdio.h>

nemu_state state;
static bool is_bad = false;
static vaddr_t halt_pc = 0x80000000; 

void set_bad(){
	is_bad = true;
}

bool status(){
	return  is_bad;
}

void set_halt_pc(vaddr_t pc){
	halt_pc = pc;
}

vaddr_t get_halt_pc(){
	return halt_pc;
}

void INV(vaddr_t addr){
	printf(ANSI_FMT("   _____  _    _   _____  _______  ______  __  __  _    _\n\
  / ____|| |  | | / ____||__   __||  ____||  \\/  || |  | |\n\
 | (___  | |  | || (___     | |   | |__   | \\  / || |  | |\n\
  \\___ \\ | |  | | \\___ \\    | |   |  __|  | |\\/| || |  | |\n\
  ____) || |__| | ____) |   | |   | |____ | |  | || |__| |\n\
 |_____/  \\____/ |_____/    |_|   |______||_|  |_| \\____/\n\n", ANSI_FG_RED));

	printf(ANSI_FMT("error at 0x%lx. ", ANSI_FG_RED), addr);
	set_bad();
	state = NEMU_ABORT;
}
