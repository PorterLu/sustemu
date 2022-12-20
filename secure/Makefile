.PHONY: test clean

SOURCES=$(shell find ./ -name "*.c")
SOURCES+=$(shell find ./ -name "*.S")
OBJECTS=$(SOURCES: %.c=%.o)
LIBS_PATH=../lib
LIBS=lib.a
FLAGS= -nostdlib -fno-builtin -fno-stack-protector -static -ffreestanding -fno-pic -march=rv64g -mcmodel=medany -I../lib
test: $(OBJECTS) $(LIBS)
	riscv64-unknown-elf-gcc  $(FLAGS) $^ -T ./linker.ld  -o test.elf
	riscv64-unknown-elf-objcopy -O binary -S test.elf test.bin
#../build/sustemu -l log.txt -e test.elf test.bin

$(LIBS):
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/start.S -c -o ./start.o
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/trm.c -c -o ./trm.o
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/console.c -c -o ./console.o
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/time.c -c -o ./time.o
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/string.c -c -o ./string.o
	riscv64-unknown-elf-gcc $(FLAGS) ../lib/stdio.c -c -o ./stdio.o
	ar rcs lib.a start.o trm.o console.o time.o stdio.o string.o

%.o: %.c
	riscv64-unknown-elf-gcc $(FLAGS) $< -c -I$(LIBS_PATH) -o $@

clean:
	-rm *.o -rf
	-rm *.a -rf
	-rm *.elf
	-rm *.bin
	-rm *.txt
