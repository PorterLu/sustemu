make -C ./secure test
make -C ./test test
./build/sustemu -l log.txt -e ./test/test.elf -t ./test/test.bin ./secure/test.bin
