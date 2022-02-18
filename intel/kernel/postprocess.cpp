#include <immintrin.h>
#include <malloc.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <cstring>


void scale_shift_x12(int32_t* dst, int8_t* result,
                     int32_t* rhs_offset, int32_t* dst_offset,
                     int32_t* scale, int32_t* shift) {

    asm volatile(
    "vpbroadcastd (%[rhs_offset]), %%ymm12 \n\t"
    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"
    "vpxor %%ymm8, %%ymm8, %%ymm8 \n\t"
    "vpxor %%ymm9, %%ymm9, %%ymm9 \n\t"
    "vpxor %%ymm10, %%ymm10, %%ymm10 \n\t"
    "vpxor %%ymm11, %%ymm11, %%ymm11 \n\t"

    "vpor 0x00(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x20(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x40(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x60(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x80(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0xa0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0xc0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0xe0(%[dst]), %%ymm7, %%ymm7 \n\t"
    "vpor 0x100(%[dst]), %%ymm8, %%ymm8 \n\t"
    "vpor 0x120(%[dst]), %%ymm9, %%ymm9 \n\t"
    "vpor 0x140(%[dst]), %%ymm10, %%ymm10 \n\t"
    "vpor 0x160(%[dst]), %%ymm11, %%ymm11 \n\t"

    "vpsubd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm12, %%ymm7, %%ymm7 \n\t"
    "vpsubd %%ymm12, %%ymm8, %%ymm8 \n\t"
    "vpsubd %%ymm12, %%ymm9, %%ymm9 \n\t"
    "vpsubd %%ymm12, %%ymm10, %%ymm10 \n\t"
    "vpsubd %%ymm12, %%ymm11, %%ymm11 \n\t"

    "vpbroadcastd (%[scale]), %%ymm12 \n\t"
    "vpmulld %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm12, %%ymm7, %%ymm7 \n\t"
    "vpmulld %%ymm12, %%ymm8, %%ymm8 \n\t"
    "vpmulld %%ymm12, %%ymm9, %%ymm9 \n\t"
    "vpmulld %%ymm12, %%ymm10, %%ymm10 \n\t"
    "vpmulld %%ymm12, %%ymm11, %%ymm11 \n\t"

    "vpbroadcastd (%[shift]), %%ymm12 \n\t"
    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"
    "vpsravd %%ymm12, %%ymm8, %%ymm8 \n\t"
    "vpsravd %%ymm12, %%ymm9, %%ymm9 \n\t"
    "vpsravd %%ymm12, %%ymm10, %%ymm10 \n\t"
    "vpsravd %%ymm12, %%ymm11, %%ymm11 \n\t"

    "vpbroadcastd (%[dst_offset]), %%ymm12 \n\t"
    "vpaddd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm12, %%ymm7, %%ymm7 \n\t"
    "vpaddd %%ymm12, %%ymm8, %%ymm8 \n\t"
    "vpaddd %%ymm12, %%ymm9, %%ymm9 \n\t"
    "vpaddd %%ymm12, %%ymm10, %%ymm10 \n\t"
    "vpaddd %%ymm12, %%ymm11, %%ymm11 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpackssdw %%ymm9, %%ymm8, %%ymm8 \n\t"
    "vpackssdw %%ymm11, %%ymm10, %%ymm10 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm8, %%ymm8 \n\t"
    "vpermq $0xd8, %%ymm10, %%ymm10 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm13 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm14 \n\t"
    "vpacksswb %%ymm10, %%ymm8, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm13, %%ymm13 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm13, 0x00(%[result]) \n\t"
    "vmovdqu %%ymm14, 0x20(%[result]) \n\t"
    "vmovdqu %%ymm15, 0x40(%[result]) \n\t"

    : // outputs
    [dst] "+r"(dst), [result] "+r"(result)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");

}


void scale_shift_x16(int32_t *dst, int8_t *result,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift) {

    asm volatile(
    "vpbroadcastd (%[rhs_offset]), %%ymm10 \n\t"
    "vpbroadcastd (%[scale]), %%ymm11 \n\t"
    "vpbroadcastd (%[shift]), %%ymm12 \n\t"
    "vpbroadcastd (%[dst_offset]), %%ymm13 \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x00(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x20(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x40(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x60(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x80(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0xa0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0xc0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0xe0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x00(%[result]) \n\t"
    "vmovdqu %%ymm15, 0x20(%[result]) \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x100(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x120(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x140(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x160(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x180(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0x1a0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0x1c0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0x1e0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x40(%[result]) \n\t"
    "vmovdqu %%ymm15, 0x60(%[result]) \n\t"

    : // outputs
    [dst] "+r"(dst), [result] "+r"(result)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");

}


void scale_shift_4x4(int32_t *dst, int8_t *result0, int8_t *result1, int8_t *result2, int8_t *result3,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift) {

    asm volatile(
    "vpbroadcastd (%[rhs_offset]), %%ymm10 \n\t"
    "vpbroadcastd (%[scale]), %%ymm11 \n\t"
    "vpbroadcastd (%[shift]), %%ymm12 \n\t"
    "vpbroadcastd (%[dst_offset]), %%ymm13 \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x00(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x20(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x40(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x60(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x80(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0xa0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0xc0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0xe0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x00(%[result0]) \n\t"
    "vmovdqu %%ymm15, 0x00(%[result1]) \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x100(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x120(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x140(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x160(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x180(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0x1a0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0x1c0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0x1e0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x00(%[result2]) \n\t"
    "vmovdqu %%ymm15, 0x00(%[result3]) \n\t"

    : // outputs
    [dst] "+r"(dst), [result0] "+r"(result0), [result1] "+r"(result1), [result2] "+r"(result2), [result3] "+r"(result3)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");

}


void scale_shift_2x8(int32_t *dst, int8_t *result0, int8_t *result1,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift) {

    asm volatile(
    "vpbroadcastd (%[rhs_offset]), %%ymm10 \n\t"
    "vpbroadcastd (%[scale]), %%ymm11 \n\t"
    "vpbroadcastd (%[shift]), %%ymm12 \n\t"
    "vpbroadcastd (%[dst_offset]), %%ymm13 \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x00(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x20(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x40(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x60(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x80(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0xa0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0xc0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0xe0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x00(%[result0]) \n\t"
    "vmovdqu %%ymm15, 0x20(%[result0]) \n\t"

    "vpxor %%ymm0, %%ymm0, %%ymm0 \n\t"
    "vpxor %%ymm1, %%ymm1, %%ymm1 \n\t"
    "vpxor %%ymm2, %%ymm2, %%ymm2 \n\t"
    "vpxor %%ymm3, %%ymm3, %%ymm3 \n\t"
    "vpxor %%ymm4, %%ymm4, %%ymm4 \n\t"
    "vpxor %%ymm5, %%ymm5, %%ymm5 \n\t"
    "vpxor %%ymm6, %%ymm6, %%ymm6 \n\t"
    "vpxor %%ymm7, %%ymm7, %%ymm7 \n\t"

    "vpor 0x100(%[dst]), %%ymm0, %%ymm0 \n\t"
    "vpor 0x120(%[dst]), %%ymm1, %%ymm1 \n\t"
    "vpor 0x140(%[dst]), %%ymm2, %%ymm2 \n\t"
    "vpor 0x160(%[dst]), %%ymm3, %%ymm3 \n\t"
    "vpor 0x180(%[dst]), %%ymm4, %%ymm4 \n\t"
    "vpor 0x1a0(%[dst]), %%ymm5, %%ymm5 \n\t"
    "vpor 0x1c0(%[dst]), %%ymm6, %%ymm6 \n\t"
    "vpor 0x1e0(%[dst]), %%ymm7, %%ymm7 \n\t"

    "vpsubd %%ymm10, %%ymm0, %%ymm0 \n\t"
    "vpsubd %%ymm10, %%ymm1, %%ymm1 \n\t"
    "vpsubd %%ymm10, %%ymm2, %%ymm2 \n\t"
    "vpsubd %%ymm10, %%ymm3, %%ymm3 \n\t"
    "vpsubd %%ymm10, %%ymm4, %%ymm4 \n\t"
    "vpsubd %%ymm10, %%ymm5, %%ymm5 \n\t"
    "vpsubd %%ymm10, %%ymm6, %%ymm6 \n\t"
    "vpsubd %%ymm10, %%ymm7, %%ymm7 \n\t"

    "vpmulld %%ymm11, %%ymm0, %%ymm0 \n\t"
    "vpmulld %%ymm11, %%ymm1, %%ymm1 \n\t"
    "vpmulld %%ymm11, %%ymm2, %%ymm2 \n\t"
    "vpmulld %%ymm11, %%ymm3, %%ymm3 \n\t"
    "vpmulld %%ymm11, %%ymm4, %%ymm4 \n\t"
    "vpmulld %%ymm11, %%ymm5, %%ymm5 \n\t"
    "vpmulld %%ymm11, %%ymm6, %%ymm6 \n\t"
    "vpmulld %%ymm11, %%ymm7, %%ymm7 \n\t"

    "vpsravd %%ymm12, %%ymm0, %%ymm0 \n\t"
    "vpsravd %%ymm12, %%ymm1, %%ymm1 \n\t"
    "vpsravd %%ymm12, %%ymm2, %%ymm2 \n\t"
    "vpsravd %%ymm12, %%ymm3, %%ymm3 \n\t"
    "vpsravd %%ymm12, %%ymm4, %%ymm4 \n\t"
    "vpsravd %%ymm12, %%ymm5, %%ymm5 \n\t"
    "vpsravd %%ymm12, %%ymm6, %%ymm6 \n\t"
    "vpsravd %%ymm12, %%ymm7, %%ymm7 \n\t"

    "vpaddd %%ymm13, %%ymm0, %%ymm0 \n\t"
    "vpaddd %%ymm13, %%ymm1, %%ymm1 \n\t"
    "vpaddd %%ymm13, %%ymm2, %%ymm2 \n\t"
    "vpaddd %%ymm13, %%ymm3, %%ymm3 \n\t"
    "vpaddd %%ymm13, %%ymm4, %%ymm4 \n\t"
    "vpaddd %%ymm13, %%ymm5, %%ymm5 \n\t"
    "vpaddd %%ymm13, %%ymm6, %%ymm6 \n\t"
    "vpaddd %%ymm13, %%ymm7, %%ymm7 \n\t"

    "vpackssdw %%ymm1, %%ymm0, %%ymm0 \n\t"
    "vpackssdw %%ymm3, %%ymm2, %%ymm2 \n\t"
    "vpackssdw %%ymm5, %%ymm4, %%ymm4 \n\t"
    "vpackssdw %%ymm7, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm0, %%ymm0 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"

    "vpacksswb %%ymm2, %%ymm0, %%ymm14 \n\t"
    "vpacksswb %%ymm6, %%ymm4, %%ymm15 \n\t"
    "vpermq $0xd8, %%ymm14, %%ymm14 \n\t"
    "vpermq $0xd8, %%ymm15, %%ymm15 \n\t"

    "vmovdqu %%ymm14, 0x00(%[result1]) \n\t"
    "vmovdqu %%ymm15, 0x20(%[result1]) \n\t"

    : // outputs
    [dst] "+r"(dst), [result0] "+r"(result0), [result1] "+r"(result1)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");

}
