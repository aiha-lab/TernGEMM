#include <immintrin.h>
#include <malloc.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <cstring>


#include "../common_1x96.h"
#include "../kernel.h"


inline void loop_b4_1x96(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
                         int64_t d1, int64_t d2) {
    asm volatile(
    "movq %[depth1], %%r12 \n\t"
    "movq %[depth2], %%r14 \n\t"
    //initialization
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"
    "vpxor %%ymm8, %%ymm8, %%ymm8 \n\t"
    "vpxor %%ymm9, %%ymm9, %%ymm9 \n\t"
    "vpxor %%ymm10, %%ymm10, %%ymm10 \n\t"
    "vpxor %%ymm11, %%ymm11, %%ymm11 \n\t"
    "vpxor %%ymm12, %%ymm12, %%ymm12 \n\t"
    "vpxor %%ymm13, %%ymm13, %%ymm13 \n\t"
    "vpxor %%ymm14, %%ymm14, %%ymm14 \n\t"
    "vpxor %%ymm15, %%ymm15, %%ymm15 \n\t"

    "cmp $0, %%r12 \n\t"
    "jb Rest%= \n\t"

    "Loop16%=: \n\t"

    "vpbroadcastb 0x00(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor (%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x40(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"

    "vpbroadcastb 0x01(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x60(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x80(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0xa0(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x02(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0xc0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0xe0(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x100(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x03(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x120(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x140(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x160(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x04(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x180(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x1a0(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x1c0(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x05(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x1e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x200(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x220(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x06(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x240(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x260(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x280(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x07(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x2a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x2c0(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x2e0(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x08(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x300(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x320(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x340(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x09(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x360(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x380(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x3a0(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x0a(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x3c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x3e0(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x400(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x0b(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x420(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x440(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x460(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x0c(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x480(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x4a0(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x4c0(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x0d(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x4e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x500(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x520(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpbroadcastb 0x0e(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x540(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x560(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x580(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "vpmovsxbw %%xmm3, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm3, %%ymm3 \n\t"
    "vpmovsxbw %%xmm3, %%ymm3 \n\t"
    "vpaddw %%ymm14, %%ymm4, %%ymm4 \n\t"
    "vpaddw %%ymm3, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"

    "vpmovsxbw %%xmm7, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm7, %%ymm7 \n\t"
    "vpmovsxbw %%xmm7, %%ymm7 \n\t"
    "vpaddw %%ymm14, %%ymm8, %%ymm8 \n\t"
    "vpaddw %%ymm7, %%ymm9, %%ymm9 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpmovsxbw %%xmm11, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm11, %%ymm11 \n\t"
    "vpmovsxbw %%xmm11, %%ymm11 \n\t"
    "vpaddw %%ymm14, %%ymm12, %%ymm12 \n\t"
    "vpaddw %%ymm11, %%ymm13, %%ymm13 \n\t"
    "vpxor %%ymm11, %%ymm11, %%ymm11 \n\t"

    //	"addq $0x10, %[lhs] \n\t"
    "addq $0x0f, %[lhs] \n\t"
    "addq $0x5a0, %[rhs] \n\t"

    "decq %%r12 \n\t"
    "jnz Loop16%= \n\t"

    "Rest%=: \n\t"

    "vpbroadcastb 0x00(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor (%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x40(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"


    "decq %%r14 \n\t"
    "jz Fin%= \n\t"
    // muladd 8x32bit 16 or depth times
    "LoopU%=: \n\t"

    "addq $0x01, %[lhs] \n\t"
    "addq $0x60, %[rhs] \n\t"

    "vpbroadcastb 0x00(%[lhs]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor (%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm6 \n\t"
    "vpxor 0x40(%[rhs]), %%ymm1, %%ymm10 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpsubb %%ymm1, %%ymm6, %%ymm6 \n\t"
    "vpandn %%ymm6, %%ymm0, %%ymm6 \n\t"
    "vpaddb %%ymm6, %%ymm7, %%ymm7 \n\t"
    "vpsubb %%ymm1, %%ymm10, %%ymm10 \n\t"
    "vpandn %%ymm10, %%ymm0, %%ymm10 \n\t"
    "vpaddb %%ymm10, %%ymm11, %%ymm11 \n\t"

    "decq %%r14 \n\t"
    "jnz LoopU%= \n\t"

    "Fin%=: \n\t"
    //convert 8bit to 16bit & addw
    "vpmovsxbw %%xmm3, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm3, %%ymm3 \n\t"
    "vpmovsxbw %%xmm3, %%ymm3 \n\t"
    "vpaddw %%ymm14, %%ymm4, %%ymm4 \n\t"
    "vpaddw %%ymm3, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"

    "vpmovsxbw %%xmm7, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm7, %%ymm7 \n\t"
    "vpmovsxbw %%xmm7, %%ymm7 \n\t"
    "vpaddw %%ymm14, %%ymm8, %%ymm8 \n\t"
    "vpaddw %%ymm7, %%ymm9, %%ymm9 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpmovsxbw %%xmm11, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm11, %%ymm11 \n\t"
    "vpmovsxbw %%xmm11, %%ymm11 \n\t"
    "vpaddw %%ymm14, %%ymm12, %%ymm12 \n\t"
    "vpaddw %%ymm11, %%ymm13, %%ymm13 \n\t"
    "vpxor %%ymm11, %%ymm11, %%ymm11 \n\t"

    //convert 16bit to 32bit after all depth mul done
    "vpmovsxwd %%xmm4, %%ymm3 \n\t"
    "vpermq $0xee, %%ymm4, %%ymm4 \n\t"
    "vpmovsxwd %%xmm4, %%ymm4 \n\t"
    "vpmovsxwd %%xmm5, %%ymm6 \n\t"
    "vpermq $0xee, %%ymm5, %%ymm5 \n\t"
    "vpmovsxwd %%xmm5, %%ymm5 \n\t"

    "vpmovsxwd %%xmm8, %%ymm7 \n\t"
    "vpermq $0xee, %%ymm8, %%ymm8 \n\t"
    "vpmovsxwd %%xmm8, %%ymm8 \n\t"
    "vpmovsxwd %%xmm9, %%ymm10 \n\t"
    "vpermq $0xee, %%ymm9, %%ymm9 \n\t"
    "vpmovsxwd %%xmm9, %%ymm9 \n\t"

    "vpmovsxwd %%xmm12, %%ymm11 \n\t"
    "vpermq $0xee, %%ymm12, %%ymm12 \n\t"
    "vpmovsxwd %%xmm12, %%ymm12 \n\t"
    "vpmovsxwd %%xmm13, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm13, %%ymm13 \n\t"
    "vpmovsxwd %%xmm13, %%ymm13 \n\t"

    "vmovdqu %%ymm3, 0x00(%[dst]) \n\t"
    "vmovdqu %%ymm4, 0x20(%[dst]) \n\t"
    "vmovdqu %%ymm6, 0x40(%[dst]) \n\t"
    "vmovdqu %%ymm5, 0x60(%[dst]) \n\t"

    "vmovdqu %%ymm7, 0x80(%[dst]) \n\t"
    "vmovdqu %%ymm8, 0xa0(%[dst]) \n\t"
    "vmovdqu %%ymm10, 0xc0(%[dst]) \n\t"
    "vmovdqu %%ymm9, 0xe0(%[dst]) \n\t"

    "vmovdqu %%ymm11, 0x100(%[dst]) \n\t"
    "vmovdqu %%ymm12, 0x120(%[dst]) \n\t"
    "vmovdqu %%ymm14, 0x140(%[dst]) \n\t"
    "vmovdqu %%ymm13, 0x160(%[dst]) \n\t"

    : // outputs
    [lhs] "+r"(lhs), [rhs] "+r"(rhs), [dst] "+r"(dst)
    : // inputs
    [depth1] "r"(d1), [depth2] "r"(d2)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12", "%r14");

}


void gemm_xor_avx_small_b4_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                                int height, int depth, int width,
                                int32_t* rhs_offset, int32_t* dst_offset,
                                int32_t* scale, int32_t* shift) {

    int64_t depth1 = (int64_t) (depth - 1) / 15;
    int64_t depth2 = (int64_t) (depth - 1) % 15 + 1;

    auto rhs_m = (int8_t*) _mm_malloc(depth * 96 * sizeof(int8_t), 256);
    auto dst_temp = (int32_t*) _mm_malloc(96 * sizeof(int32_t), 256);

    for (int i = 0; i < (width - 1) / 96; i++) {

        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96, rhs + (a * width + 96 * i), 96 * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            loop_b4_1x96(lhs + depth * j,
                         rhs_m,
                         dst_temp, depth1, depth2);

            scale_shift_x12(dst_temp, dst + width * j + 96 * i,
                            rhs_offset, dst_offset, scale, shift);
        }
    }

    for (int a = 0; a < depth; a++) {
        memcpy(rhs_m + a * 96, rhs + (a * width + width - 96), 96 * sizeof(int8_t));
    }
    for (int j = 0; j < height; j++) {
        loop_b4_1x96(lhs + depth * j,
                     rhs_m,
                     dst_temp, depth1, depth2);

        if (width >= 96) {
            scale_shift_x12(dst_temp, dst + width * j + width - 96,
                            rhs_offset, dst_offset, scale, shift);
        }
        else {
            scale_shift_x12(dst_temp, dst,
                            rhs_offset, dst_offset, scale, shift);
        }
    }

    _mm_free(rhs_m);
    _mm_free(dst_temp);
}

void gemm_xor_avx_b4_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift) {
        gemm_xor_avx_small_b4_1x96(lhs, rhs, dst, height, depth, width, rhs_offset, dst_offset, scale, shift);
    }



