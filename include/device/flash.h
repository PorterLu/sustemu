#ifndef __FLASH_H__
#define __FLASH_H__

#define FLASH_BASE_ADDR 0x30000000
long init_flash();
extern char* task_file;

#endif
