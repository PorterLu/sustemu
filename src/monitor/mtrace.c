#include <mtrace.h>
#include <pmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static mtrace_point *head;
static mtrace_point *tail;

void add_mtrace_point(bool is_write, vaddr_t addr, int len, word_t data){
	mtrace_point *pointer = (mtrace_point*)malloc(sizeof(mtrace_point));
	pointer->is_write = is_write;
	pointer->addr = addr;
	pointer->len = len;
	if(is_write)
		pointer->data = data;
	else
		pointer->data = paddr_read(addr, len); 
	pointer->next = NULL;

	if(head == NULL)
		head = tail = pointer;
	else{
		tail->next = pointer;
		tail = pointer;
	}
}

void print_mtrace(char* type, paddr_t addr, int len){
	mtrace_point *pointer = head;
	int type_num = 2;

	if(strcmp(type, "w") == 0){
		type_num = 1;
	}else if(strcmp(type, "r") == 0){
		type_num = 0;
	}

	while(pointer){
		if((pointer->is_write == type_num) || (type_num == 2)){
			if((pointer->addr >= addr) || (pointer->addr <= addr + len)){
				if(pointer->is_write)
					printf("write ");
				else
					printf("read ");

				printf("addr:%lx len:%d data:%lx\n", pointer->addr, pointer->len, pointer->data);
			}
		}		
		pointer = pointer->next;
	}
}

void delete_mtrace(){
	mtrace_point *pointer = head;
	while(pointer){
		mtrace_point *tmp = pointer;
		tmp = tmp->next;
		free(pointer);
		pointer = tmp;
	}
}
