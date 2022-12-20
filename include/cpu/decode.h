#ifndef __CPU_DECODE_H__
#define __CPU_DECODE_H__

#include <common.h>
#include <debug.h>
#include <utils.h>

typedef struct {
	uint32_t val;
} DecodeInfo;

typedef struct Decode {
  vaddr_t pc;
  vaddr_t snpc; // static next pc
  vaddr_t dnpc; // dynamic next pc
  DecodeInfo inst;
} Decode;

// --- pattern matching mechanism ---
__attribute__((always_inline))
static inline void pattern_decode(const char *str, int len,
    uint64_t *key, uint64_t *mask , uint64_t *shift) { 
  uint64_t __key = 0, __mask = 0, __shift = 0;
#define macro(i) \
  if ((i) >= len) goto finish; \
  else { \
    char c = str[i]; \
    if (c != ' ') { \
      Assert(c == '0' || c == '1' || c == '?', \
          "invalid character '%c' in pattern string", c); \
      __key  = (__key  << 1) | (c == '1' ? 1 : 0); \
      __mask = (__mask << 1) | (c == '?' ? 0 : 1); \
      __shift = (c == '?' ? __shift + 1 : 0); \
    } \
  }
#define macro2(i)  macro(i);   macro((i) + 1)
#define macro4(i)  macro2(i);  macro2((i) + 2)
#define macro8(i)  macro4(i);  macro4((i) + 4)
#define macro16(i) macro8(i);  macro8((i) + 8)
#define macro32(i) macro16(i); macro16((i) + 16)
#define macro64(i) macro32(i); macro32((i) + 32)
  macro64(0);
  panic("pattern too long");
#undef macro
finish:
  *key = __key >> __shift;
  *mask = __mask >> __shift;
  *shift = __shift;
}

__attribute__((always_inline))
static inline void pattern_decode_hex(const char *str, int len,
	uint64_t *key, uint64_t *mask, uint64_t *shift) {
	uint64_t __key = 0, __mask = 0, __shift = 0;
	#define macro(i) \
	if ((i) >= len) goto finish; \
	else { \
		char c = str[i]; \
		if (c != ' ') { \
		Assert((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || c == '?', \
			"invalid character '%c' in pattern string", c); \
		__key  = (__key  << 4) | (c == '?' ? 0 : (c >= '0' && c <= '9') ? c - '0' : c - 'a' + 10); \
		__mask = (__mask << 4) | (c == '?' ? 0 : 0xf); \
		__shift = (c == '?' ? __shift + 4 : 0); \
		} \
	}

	macro16(0);
	panic("pattern too long");
	#undef macro
	finish:
	*key = __key >> __shift;
	*mask = __mask >> __shift;
	*shift = __shift;
}

#define SEXT(x, len) ({ struct { int64_t n : len; } __x = { .n = x }; (uint64_t)__x.n; })
#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_I, TYPE_U, TYPE_S, TYPE_J, TYPE_R, TYPE_B,
  TYPE_N, // none
};

#define src1R(n) do { *src1 = R(n); } while (0)
#define src2R(n) do { *src2 = R(n); } while (0)
#define destR(n) do { *dest = n; } while (0)
#define src1I(i) do { *src1 = i; } while (0)
#define src2I(i) do { *src2 = i; } while (0)
#define destI(i) do { *dest = i; } while (0)

// --- pattern matching wrappers for decode ---
#define INSTPAT(pattern, ...) do { \
  uint64_t key, mask, shift; \
  pattern_decode(pattern, STRLEN(pattern), &key, &mask, &shift); \
  if (((INSTPAT_INST(s) ) & mask) >> shift == key) { \
    INSTPAT_MATCH(s, ##__VA_ARGS__); \
    goto *(__instpat_end); \
  } \
} while (0)

static inline word_t immI(uint32_t i) { return SEXT(BITS(i, 31, 20), 12); }                            //BITS取i的对应位，通过SEXT进行符号位扩展
static inline word_t immU(uint32_t i) { return SEXT(BITS(i, 31, 12), 20) << 12; }                      //与上面不同的是，扩展的立即数为20位
static inline word_t immS(uint32_t i) { return (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); }     //拼接成12位立即数，只用高位进行符号位扩展
static inline word_t immJ(uint32_t i) { return (SEXT(BITS(i, 31, 31), 1)<< 20) | (BITS(i, 19, 12) << 12) | (BITS(i, 20, 20) << 11)|(BITS(i, 30, 21) << 1);}
static inline word_t immB(uint32_t i) { return (SEXT(BITS(i, 31, 31),1) <<12)|(BITS(i, 7, 7) << 11)|(BITS(i, 30, 25) << 5)|(BITS(i,11,8) << 1);}

#define INSTPAT_START(name) { const void ** __instpat_end = &&concat(__instpat_end_, name);
#define INSTPAT_END(name)   concat(__instpat_end_, name): ; }
extern Decode s;
void init_decode_info();
void decode_operand(Decode *s, word_t *dest, word_t *src1, word_t *src2, int type);
#endif
