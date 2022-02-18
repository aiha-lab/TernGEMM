//
// Created by shchoi on 2021-01-28.
//

#ifndef MY_APPLICATION_KERNEL_H
#define MY_APPLICATION_KERNEL_H


#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <string>


void gemm_xor_baseline(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
                       int height, int depth, int width);

void gemm_xor_avx(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                  int height, int depth, int width,
                  int32_t rhs_offset, int32_t dst_offset,
                  int32_t scale, int32_t shift);

void gemm_xor_avx_1x128(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                        int height, int depth, int width,
                        int32_t rhs_offset, int32_t dst_offset,
                        int32_t scale, int32_t shift);

void gemm_xor_avx_4x32(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                       int height, int depth, int width,
                       int32_t rhs_offset, int32_t dst_offset,
                       int32_t scale, int32_t shift);

void gemm_xor_avx_2x64(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                       int height, int depth, int width,
                       int32_t rhs_offset, int32_t dst_offset,
                       int32_t scale, int32_t shift);

#endif //MY_APPLICATION_KERNEL_H
