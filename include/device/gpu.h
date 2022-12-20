#ifndef __GPU_H__
#define __GPU_H__

#define CONFIG_FB_ADDR 0xa1000000
#define CONFIG_VGA_CTL_MMIO 0xa0000100
void init_vga() ;
void vga_update_screen();
#endif