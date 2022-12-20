#ifndef __VMEM_H__
#define __VMEM_H__

#include <stdint.h>
#include <pmem.h>
#include <common.h>

typedef uint64_t vaddr_t; 

word_t vaddr_ifetch(vaddr_t addr, int len);
word_t vaddr_read(vaddr_t addr, int len);
void vaddr_write(vaddr_t addr, int len, word_t data);


#endif