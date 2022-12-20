#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#define CONFIG_SERIAL_MMIO 0xa00003f8
void putchar(char c);
void putstr(char* str);

#endif
