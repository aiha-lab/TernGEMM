#ifndef GEMMLOWP_XOR_KERNEL_H
#define GEMMLOWP_XOR_KERNEL_H

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <x86intrin.h>

void unpack_weight_baseline(const uint8_t *input, int depth, uint8_t *dst);

void unpacking(const uint8_t* input, int depth, uint8_t* output);

void unpacking_activation(const uint8_t* input, int depth, uint8_t* output);

void packing_activation(const uint8_t* input, int depth, uint8_t* output);

void gemm_xor_baseline_32bit(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
                             int height, int depth, int width);

void gemm_xor_baseline(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                       int height, int depth, int width,
                       int rhs_offset, int scale, int shift, int dst_offset);

void gemm_xor_avx_b3_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift);

void gemm_xor_avx_b4_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift);

void gemm_xor_avx_b4_1x96_n(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift, int32_t* n);

void gemm_xor_avx_b5_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift);

void gemm_xor_avx_b6_1x96(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                          int height, int depth, int width,
                          int32_t* rhs_offset, int32_t* dst_offset,
                          int32_t* scale, int32_t* shift);

void gemm_xor_avx_b4_1x128(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                           int height, int depth, int width,
                           int32_t *rhs_offset, int32_t *dst_offset,
                           int32_t *scale, int32_t *shift);

void gemm_xor_avx_b4_1x128_n(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                           int height, int depth, int width,
                           int32_t *rhs_offset, int32_t *dst_offset,
                           int32_t *scale, int32_t *shift, int32_t* n);

void gemm_xor_avx_b4_4x32(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                          int height, int depth, int width,
                          int32_t *rhs_offset, int32_t *dst_offset,
                          int32_t *scale, int32_t *shift);

void gemm_xor_avx_b4_4x32_n(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                          int height, int depth, int width,
                          int32_t *rhs_offset, int32_t *dst_offset,
                          int32_t *scale, int32_t *shift, int32_t* n);

void gemm_xor_avx_b4_2x64(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                          int height, int depth, int width,
                          int32_t *rhs_offset, int32_t *dst_offset,
                           int32_t *scale, int32_t *shift);

void gemm_xor_avx_b4_2x64_n(const int8_t *lhs, const int8_t *rhs, int8_t *dst,
                          int height, int depth, int width,
                          int32_t *rhs_offset, int32_t *dst_offset,
                           int32_t *scale, int32_t *shift, int32_t* n);

void scale_shift_x12(int32_t* dst, int8_t* result,
                     int32_t* rhs_offset, int32_t* dst_offset,
                     int32_t* scale, int32_t* shift);

void scale_shift_x16(int32_t *dst, int8_t *result,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift);

void scale_shift_4x4(int32_t *dst, int8_t *result0, int8_t *result1, int8_t *result2, int8_t *result3,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift);

void scale_shift_2x8(int32_t *dst, int8_t *result0, int8_t *result1,
                     int32_t *rhs_offset, int32_t *dst_offset,
                     int32_t *scale, int32_t *shift);



/*
void gemm_xor_avx_b4_1x96_new(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                              int8_t* tmp8, int32_t* tmp32a, int32_t* tmp32b,
                              int height, int depth, int width,
                              int32_t* rhs_offset, int32_t* dst_offset,
                              int32_t* scale, int32_t* shift);
*/
inline uint64_t rdtsc() {
    // https://stackoverflow.com/questions/13772567/how-to-get-the-cpu-cycle-count-in-x86-64-from-c
    _mm_lfence();  // optionally wait for earlier inst.s to retire before reading the clock
    uint64_t tsc = __rdtsc();
    _mm_lfence();  // optionally block later instructions until rdtsc retires
    return tsc;
}


#endif //GEMMLOWP_XOR_KERNEL_H
