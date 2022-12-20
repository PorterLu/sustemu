#ifndef __MMIO_H__
#define __MMIO_H__
#include <common.h>

#define PAGE_SIZE 4096
#define PAGE_MASK 0x0fff

typedef void(*io_callback_t)(uint32_t, int, bool);

typedef struct {
	const char *name;
	paddr_t low;
	paddr_t high;
	void *space;
	io_callback_t callback;
} IOMap;

void add_mmio_map(const char *name, paddr_t addr, void *space, uint32_t len, io_callback_t callback);
word_t map_read(paddr_t addr, int len, IOMap *map);
void map_write(paddr_t addr, int len, word_t data, IOMap *map);
uint8_t* new_space(int size);
void init_map();
word_t mmio_read(paddr_t addr, int len);
void mmio_write(paddr_t addr, int len, word_t data);

#endif
