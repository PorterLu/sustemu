#ifndef __MTRACE_H__
#define __MTRACE_H__
#include <common.h>

struct mtrace_point{
	bool is_write;
	paddr_t addr;
	int len;
	word_t data;
	struct mtrace_point *next;
};

typedef struct mtrace_point mtrace_point;

void add_mtrace_point(bool is_write, paddr_t addr, int len, word_t data);
void print_mtrace(char* type, paddr_t addr, int len);
void delete_mtrace();

#endif