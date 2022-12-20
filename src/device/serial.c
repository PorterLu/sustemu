#include <mmio.h>
#include <stdio.h>
#include <serial.h>

static uint8_t *serial_base = NULL;

void serial_io_handler(uint32_t offset, int len, bool is_write){
	switch(offset){
		case 0:
			if(is_write) putc(serial_base[0], stderr);
	}
}

void init_serial(){
	serial_base = new_space(8);

	add_mmio_map("serial", CONFIG_SERIAL_MMIO, serial_base, 8, serial_io_handler);
}
