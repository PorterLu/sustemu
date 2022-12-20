.section entry, "ax"
.globl _start
.type _start, @function

.extern _trm_init

_start:
  mv s0, zero
  la sp, _stack_pointer
  jal _trm_init
