#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdint.h>
#include <autoconf.h>
/**************基本类型*********************
 *  下面是对于几个基本类型的封装，他们的定义如下：*
 * 	paddr_t 	用于表示物理地址			 *
 *  word_t		RV64中的一个word			*
 *  vaddr_t 	用于表示虚拟地址			 *
 *****************************************/
typedef uint64_t paddr_t;
typedef uint64_t word_t;
typedef uint64_t vaddr_t;
#define bool int 
#define true 1
#define false 0

#endif
