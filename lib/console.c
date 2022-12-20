#include "console.h"
void putchar(char c){
	*((volatile char*)CONFIG_SERIAL_MMIO) = c;
}

void putstr(char* str){
	int i = 0;
	while(*(str+i)){
		*((volatile char*)CONFIG_SERIAL_MMIO) = *(str+i);
		i++;
	}
}
