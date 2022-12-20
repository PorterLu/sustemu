#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <stdint.h>

typedef struct Block{
	uint64_t index;
	uint8_t hash[32];
	uint8_t pre_hash[32];
	uint64_t time;
	uint8_t* data;
} Block;

#endif
