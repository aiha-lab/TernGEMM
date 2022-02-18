#ifndef GEMMLOWP_XOR_COMMON_2x64_H
#define GEMMLOWP_XOR_COMMON_2x64_H


#include <immintrin.h>
#include <malloc.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <cstring>

inline void dst_init_2x64(int32_t *dst) {

    asm volatile(
    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"

    "vmovdqu %%ymm0, 0x00(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x20(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x40(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x60(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x80(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0xa0(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0xc0(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0xe0(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x100(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x120(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x140(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x160(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x180(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x1a0(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x1c0(%[dst]) \n\t"
    "vmovdqu %%ymm0, 0x1e0(%[dst]) \n\t"
    : // outputs
    [dst] "+r"(dst)
    : // inputs
    : // clobbers
    "cc", "memory", "%ymm0");
}

inline void dst_add_2x64(int32_t *dst, int32_t *dst_temp) {

    asm volatile(
    "vmovdqu 0x00(%[dst_temp]), %%ymm0 \n\t"
    "vmovdqu 0x20(%[dst_temp]), %%ymm1 \n\t"
    "vmovdqu 0x40(%[dst_temp]), %%ymm2 \n\t"
    "vmovdqu 0x60(%[dst_temp]), %%ymm3 \n\t"
    "vmovdqu 0x80(%[dst_temp]), %%ymm4 \n\t"
    "vmovdqu 0xa0(%[dst_temp]), %%ymm5 \n\t"
    "vmovdqu 0xc0(%[dst_temp]), %%ymm6 \n\t"
    "vmovdqu 0xe0(%[dst_temp]), %%ymm7 \n\t"
    "vmovdqu 0x100(%[dst_temp]), %%ymm8 \n\t"
    "vmovdqu 0x120(%[dst_temp]), %%ymm9 \n\t"
    "vmovdqu 0x140(%[dst_temp]), %%ymm10 \n\t"
    "vmovdqu 0x160(%[dst_temp]), %%ymm11 \n\t"
    "vmovdqu 0x180(%[dst_temp]), %%ymm12 \n\t"
    "vmovdqu 0x1a0(%[dst_temp]), %%ymm13 \n\t"
    "vmovdqu 0x1c0(%[dst_temp]), %%ymm14 \n\t"
    "vmovdqu 0x1e0(%[dst_temp]), %%ymm15 \n\t"

    "vpaddd 0x00(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpaddd 0x20(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpaddd 0x40(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpaddd 0x60(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpaddd 0x80(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpaddd 0xa0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpaddd 0xc0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpaddd 0xe0(%[dst]), %%ymm7, %%ymm7 \n\t"
    "vpaddd 0x100(%[dst]), %%ymm8, %%ymm8 \n\t"
    "vpaddd 0x120(%[dst]), %%ymm9, %%ymm9 \n\t"
    "vpaddd 0x140(%[dst]), %%ymm10, %%ymm10 \n\t"
    "vpaddd 0x160(%[dst]), %%ymm11, %%ymm11 \n\t"
    "vpaddd 0x180(%[dst]), %%ymm12, %%ymm12 \n\t"
    "vpaddd 0x1a0(%[dst]), %%ymm13, %%ymm13 \n\t"
    "vpaddd 0x1c0(%[dst]), %%ymm14, %%ymm14 \n\t"
    "vpaddd 0x1e0(%[dst]), %%ymm15, %%ymm15 \n\t"

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
    "vmovdqu %%ymm14, 0x1c0(%[dst]) \n\t"
    "vmovdqu %%ymm15, 0x1e0(%[dst]) \n\t"
    : // outputs
    [dst] "+r"(dst), [dst_temp] "+r"(dst_temp)
    : // inputs
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15");

}

#endif //GEMMLOWP_XOR_COMMON_2x64_H
