#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__
#include <stdint.h>
typedef struct transaction {
	uint8_t *sender;
	uint8_t *receiver;
	uint64_t ammount;
	uint8_t *signature;
	uint8_t *message;
	struct transaction* next;
} transaction;

extern transaction* head;
extern transaction* pointer;
#endif
