#include <img.h>
#include <vmem.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <log.h>

uint64_t img_size = 0;

/*************************IMG加载*************************
 * 默认加载的程序是一个只有addi和ebreak的程序，如果镜像文件存在  *
 * 之后会获取文件大小，之后再读入模拟的内存数组					*
*********************************************************/

static const uint32_t default_program[] = {
	0x00150513, 0x00150513, 0x00150513, 0x00150513, 
	0x00150513, 0x00150513, 0x00150513, 0x00150513,
	0x00150513, 0x00150513, 0x00150513, 0x00150513,
	0x00150513, 0x00150513, 0x00150513, 0x00100073
};


char* img_file = NULL;

void init_default_program()
{
	memcpy(guest_to_host(RESET_VECTOR), default_program, sizeof(default_program));
}

long load_img()
{
	if(img_file == NULL)
	{
		Log("No image is  given. Use the default built-in image.");
		img_size = 4096;
		return 4096;				
	}

	FILE *fp = fopen(img_file, "rb");
	Assert(fp, "Can not open '%s'", img_file);

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	img_size = size;

	Log("The image is %s, size = %ld", img_file, size);

	fseek(fp, 0, SEEK_SET);
	int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
	assert(ret == 1);

	fclose(fp);
	return size;
}
