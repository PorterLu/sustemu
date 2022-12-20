#include "string.h"


uint64_t strlen(char *s){
	uint64_t len = 0;
	while(*(s+len)!=0){
		len++;
	}

	return len;
}
