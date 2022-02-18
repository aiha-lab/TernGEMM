#include <immintrin.h>
#include <malloc.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <cstring>


#include "../common_2x64.h"
#include "../kernel.h"


inline void loop_b4_2x64(const int8_t *lhs0,const int8_t *lhs1, const int8_t *rhs, int32_t *dst,
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
    "je Rest%= \n\t"

    "Loop16%=: \n\t"

    "vpbroadcastb 0x00(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x00(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x01(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x40(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x60(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x01(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x40(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x60(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x02(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x80(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0xa0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x02(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x80(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0xa0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x03(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0xc0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0xe0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x03(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0xc0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0xe0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x04(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x100(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x120(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x04(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x100(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x120(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x05(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x140(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x160(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x05(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x140(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x160(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x06(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x180(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x1a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x06(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x180(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x1a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x07(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x1c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x1e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x07(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x1c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x1e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x08(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x200(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x220(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x08(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x200(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x220(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x09(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x240(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x260(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x09(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x240(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x260(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x0a(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x280(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x2a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0a(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x280(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x2a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x0b(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x2c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x2e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0b(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x2c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x2e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x0c(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x300(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x320(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0c(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x300(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x320(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x0d(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x340(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x360(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0d(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x340(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x360(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "vpbroadcastb 0x0e(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x380(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x3a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0e(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x380(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x3a0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"


    "vpbroadcastb 0x0f(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x3c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x3e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x0f(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x3c0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x3e0(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"


    "vpmovsxbw %%xmm3, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm3, %%ymm3 \n\t"
    "vpmovsxbw %%xmm3, %%ymm3 \n\t"
    "vpaddw %%ymm2, %%ymm4, %%ymm4 \n\t"
    "vpaddw %%ymm3, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"

    "vpmovsxbw %%xmm6, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm6, %%ymm6 \n\t"
    "vpmovsxbw %%xmm6, %%ymm6 \n\t"
    "vpaddw %%ymm2, %%ymm7, %%ymm7 \n\t"
    "vpaddw %%ymm6, %%ymm8, %%ymm8 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"

    "vpmovsxbw %%xmm9, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm9, %%ymm9 \n\t"
    "vpmovsxbw %%xmm9, %%ymm9 \n\t"
    "vpaddw %%ymm2, %%ymm10, %%ymm10 \n\t"
    "vpaddw %%ymm9, %%ymm11, %%ymm11 \n\t"
    "vpxor %%ymm9, %%ymm9, %%ymm9 \n\t"

    "vpmovsxbw %%xmm12, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm12, %%ymm12 \n\t"
    "vpmovsxbw %%xmm12, %%ymm12 \n\t"
    "vpaddw %%ymm2, %%ymm13, %%ymm13 \n\t"
    "vpaddw %%ymm12, %%ymm14, %%ymm14 \n\t"
    "vpxor %%ymm12, %%ymm12, %%ymm12 \n\t"

    "addq $0x10, %[lhs0] \n\t"
    "addq $0x10, %[lhs1] \n\t"
    "addq $0x400, %[rhs] \n\t"

    "decq %%r12 \n\t"
    "jnz Loop16%= \n\t"

    "Rest%=: \n\t"


    "vpbroadcastb 0x00(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x00(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"


    "decq %%r14 \n\t"
    "jz Fin%= \n\t"
    // muladd 8x32bit 16 or depth times
    "LoopU%=: \n\t"

    "addq $0x01, %[lhs0] \n\t"
    "addq $0x01, %[lhs1] \n\t"
    "addq $0x40, %[rhs] \n\t"

    "vpbroadcastb 0x00(%[lhs0]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm3, %%ymm3 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm6, %%ymm6 \n\t"
    "vpbroadcastb 0x00(%[lhs1]), %%ymm0 \n\t"
    "vpcmpgtb %%ymm0, %%ymm15, %%ymm1 \n\t"
    "vpcmpeqb %%ymm0, %%ymm15, %%ymm0 \n\t"
    "vpxor 0x00(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm9, %%ymm9 \n\t"
    "vpxor 0x20(%[rhs]), %%ymm1, %%ymm2 \n\t"
    "vpsubb %%ymm1, %%ymm2, %%ymm2 \n\t"
    "vpandn %%ymm2, %%ymm0, %%ymm2 \n\t"
    "vpaddb %%ymm2, %%ymm12, %%ymm12 \n\t"

    "decq %%r14 \n\t"
    "jnz LoopU%= \n\t"

    "Fin%=: \n\t"
    //convert 8bit to 16bit & addw

    "vpmovsxbw %%xmm3, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm3, %%ymm3 \n\t"
    "vpmovsxbw %%xmm3, %%ymm3 \n\t"
    "vpaddw %%ymm2, %%ymm4, %%ymm4 \n\t"
    "vpaddw %%ymm3, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"

    "vpmovsxbw %%xmm6, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm6, %%ymm6 \n\t"
    "vpmovsxbw %%xmm6, %%ymm6 \n\t"
    "vpaddw %%ymm2, %%ymm7, %%ymm7 \n\t"
    "vpaddw %%ymm6, %%ymm8, %%ymm8 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"

    "vpmovsxbw %%xmm9, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm9, %%ymm9 \n\t"
    "vpmovsxbw %%xmm9, %%ymm9 \n\t"
    "vpaddw %%ymm2, %%ymm10, %%ymm10 \n\t"
    "vpaddw %%ymm9, %%ymm11, %%ymm11 \n\t"
    "vpxor %%ymm9, %%ymm9, %%ymm9 \n\t"

    "vpmovsxbw %%xmm12, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm12, %%ymm12 \n\t"
    "vpmovsxbw %%xmm12, %%ymm12 \n\t"
    "vpaddw %%ymm2, %%ymm13, %%ymm13 \n\t"
    "vpaddw %%ymm12, %%ymm14, %%ymm14 \n\t"
    "vpxor %%ymm12, %%ymm12, %%ymm12 \n\t"


    //convert 16bit to 32bit after all depth mul done
    "vpmovsxwd %%xmm4, %%ymm0 \n\t"
    "vpermq $0xee, %%ymm4, %%ymm4 \n\t"
    "vpmovsxwd %%xmm4, %%ymm1 \n\t"
    "vpmovsxwd %%xmm5, %%ymm2 \n\t"
    "vpermq $0xee, %%ymm5, %%ymm5 \n\t"
    "vpmovsxwd %%xmm5, %%ymm3 \n\t"

    "vpmovsxwd %%xmm7, %%ymm4 \n\t"
    "vpermq $0xee, %%ymm7, %%ymm7 \n\t"
    "vpmovsxwd %%xmm7, %%ymm5 \n\t"
    "vpmovsxwd %%xmm8, %%ymm6 \n\t"
    "vpermq $0xee, %%ymm8, %%ymm8 \n\t"
    "vpmovsxwd %%xmm8, %%ymm7 \n\t"

    "vpmovsxwd %%xmm10, %%ymm8 \n\t"
    "vpermq $0xee, %%ymm10, %%ymm10 \n\t"
    "vpmovsxwd %%xmm10, %%ymm9 \n\t"
    "vpmovsxwd %%xmm11, %%ymm10 \n\t"
    "vpermq $0xee, %%ymm11, %%ymm11 \n\t"
    "vpmovsxwd %%xmm11, %%ymm11 \n\t"

    "vpmovsxwd %%xmm13, %%ymm12 \n\t"
    "vpermq $0xee, %%ymm13, %%ymm13 \n\t"
    "vpmovsxwd %%xmm13, %%ymm13 \n\t"
    "vpmovsxwd %%xmm14, %%ymm15 \n\t"
    "vpermq $0xee, %%ymm14, %%ymm14 \n\t"
    "vpmovsxwd %%xmm14, %%ymm14 \n\t"

    "vmovdqu %%ymm0, 0x00(%[dst]) \n\t"
    "vmovdqu %%ymm1, 0x20(%[dst]) \n\t"
    "vmovdqu %%ymm2, 0x40(%[dst]) \n\t"
    "vmovdqu %%ymm3, 0x60(%[dst]) \n\t"

    "vmovdqu %%ymm4, 0x80(%[dst]) \n\t"
    "vmovdqu %%ymm5, 0xa0(%[dst]) \n\t"
    "vmovdqu %%ymm6, 0xc0(%[dst]) \n\t"
    "vmovdqu %%ymm7, 0xe0(%[dst]) \n\t"

    "vmovdqu %%ymm8, 0x100(%[dst]) \n\t"
    "vmovdqu %%ymm9, 0x120(%[dst]) \n\t"
    "vmovdqu %%ymm10, 0x140(%[dst]) \n\t"
    "vmovdqu %%ymm11, 0x160(%[dst]) \n\t"

    "vmovdqu %%ymm12, 0x180(%[dst]) \n\t"
    "vmovdqu %%ymm13, 0x1a0(%[dst]) \n\t"
    "vmovdqu %%ymm15, 0x1c0(%[dst]) \n\t"
    "vmovdqu %%ymm14, 0x1e0(%[dst]) \n\t"

    : // outputs
    [lhs0] "+r"(lhs0),[lhs1] "+r"(lhs1), [rhs] "+r"(rhs), [dst] "+r"(dst)
    : // inputs
    [depth1] "r"(d1), [depth2] "r"(d2)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12", "%r14");

}


void gemm_xor_avx_small_b4_2x64(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                                int height, int depth, int width,
                                int32_t *rhs_offset, int32_t *dst_offset,
                                int32_t *scale, int32_t *shift) {

    int64_t depth1 = (int64_t) (depth - 1) / 16;
    int64_t depth2 = (int64_t) (depth - 1) % 16 + 1;

    auto rhs_m = (int8_t*) _mm_malloc(depth * 128 * sizeof(int8_t), 256);
    auto dst_temp = (int32_t*) _mm_malloc(128 * sizeof(int32_t), 256);
    int j = 0;

    for (int i = 0; i < (width - 1) / 64; i++) {

        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 64, rhs + (a * width + 64 * i), 64 * sizeof(int8_t));
        }
        for (; j <= height - 2; j += 2) {
            loop_b4_2x64(lhs + depth * j,
                         lhs + depth * (j + 1),
                         rhs_m,
                         dst_temp, depth1, depth2);

            scale_shift_2x8(dst_temp,
                            dst + width * j + 64 * i,
                            dst + width * (j + 1) + 64 * i,
                            rhs_offset, dst_offset, scale, shift);
        }
        if (j < height) {
            j = height - 2;
            loop_b4_2x64(lhs + depth * j,
                         lhs + depth * (j + 1),
                         rhs_m,
                         dst_temp, depth1, depth2);

            scale_shift_2x8(dst_temp,
                            dst + width * j + 64 * i,
                            dst + width * (j + 1) + 64 * i,
                            rhs_offset, dst_offset, scale, shift);
        }
        j=0;
    }

    for (int a = 0; a < depth; a++) {
        memcpy(rhs_m + a * 64, rhs + (a * width + width - 64), 64 * sizeof(int8_t));
    }
    for (; j <= height - 2; j += 2) {
        loop_b4_2x64(lhs + depth * j,
                     lhs + depth * (j + 1),
                     rhs_m,
                     dst_temp, depth1, depth2);

        if (width >= 64) {
            scale_shift_2x8(dst_temp,
                            dst + width * j + width - 64,
                            dst + width * (j + 1) + width - 64,
                            rhs_offset, dst_offset, scale, shift);
        } else {
            scale_shift_2x8(dst_temp,
                            dst + width * j,
                            dst + width * (j + 1),
                            rhs_offset, dst_offset, scale, shift);
        }
    }
    if (j < height) {
        j = height - 2;
        loop_b4_2x64(lhs + depth * j,
                     lhs + depth * (j + 1),
                     rhs_m,
                     dst_temp, depth1, depth2);

        if (width >= 64) {
            scale_shift_2x8(dst_temp,
                            dst + width * j + width - 64,
                            dst + width * (j + 1) + width - 64,
                            rhs_offset, dst_offset, scale, shift);
        } else {
            scale_shift_2x8(dst_temp,
                            dst + width * j,
                            dst + width * (j + 1),
                            rhs_offset, dst_offset, scale, shift);
        }
    }

}

void gemm_xor_avx_b4_2x64(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                          int height, int depth, int width,
                          int32_t *rhs_offset, int32_t *dst_offset,
                          int32_t *scale, int32_t *shift) {

        gemm_xor_avx_small_b4_2x64(lhs, rhs, dst,
                                 height, depth, width, rhs_offset, dst_offset, scale, shift);

}

