#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <chrono>
#include <immintrin.h>
#include <cmath>
#include <malloc.h>

#define NUM_RUN 1000

#include "kernel/kernel.h"


using namespace std;


int main(int argc, char **argv) {

    // parse argc, argv
    // argv[1]: height
    // argv[2]: depth
    // argv[3]: width
    // argv[4]: bit  (default 4)
    // argv[5]: verbose (default false)

    if (argc < 4) {
        printf("[LOG] Arguments are not enough.\n");
        return EXIT_FAILURE;
    }

    int height = std::atoi(argv[1]);
    int depth = std::atoi(argv[2]);
    int width = std::atoi(argv[3]);
    int bit = 4;
    if (argc >= 5) {
        bit = std::atoi(argv[4]);
    }
    int verbose = 0;
    if (argc >= 6) {
        verbose = std::atoi(argv[5]);
    }

    if (verbose)
        printf("[LOG] height: %d, depth: %d, width: %d, bit: %d\n", height, depth, width, bit);

    if ((bit < 3) || (bit > 6)) {
        printf("[LOG] Bit range exceed.\n");
        return EXIT_FAILURE;
    }

    // ---------------------------------------------------------------- //
    // Load binary
    // ---------------------------------------------------------------- //
    auto lhs_m = (int8_t *) _mm_malloc(height * depth * sizeof(int8_t), 256);
    auto rhs_m = (int8_t *) _mm_malloc(width * depth * sizeof(int8_t), 256);
    auto dst_m_baseline = (int8_t *) _mm_malloc(height * width * sizeof(int8_t) + 256, 256);
    auto dst_m_avx = (int8_t *) _mm_malloc(height * width * sizeof(int8_t) + 256, 256);

    for (int j = 0; j < height * depth; j++) {
        lhs_m[j] = static_cast<int8_t>((j * j) % 3 - 1);   // [-1, 0, 1]
    }

    int rs = static_cast<int>(std::pow(2, bit)) - 1;  // 3bit: 7, 4bit: 15, 5bit: 31, 6bit: 63
    int ro = static_cast<int>(std::pow(2, bit - 1));  // 3bit: 4, 4bit: 8, 5bit: 16, 6bit: 32
    for (int j = 0; j < width * depth; j++) {
        rhs_m[j] = static_cast<int8_t>(((j + 1) * (j + 1)) % rs - ro);
    }
    for (int j = 0; j < height * width; j++) {
        dst_m_baseline[j] = 1;
        dst_m_avx[j] = -1;
    }

    // ---------------------------------------------------------------- //
    // Run
    // ---------------------------------------------------------------- //

    auto rhs_offset = (int32_t *) _mm_malloc(4 * sizeof(int32_t), 128);
    auto scale = (int32_t *) _mm_malloc(4 * sizeof(int32_t), 128);
    auto shift = (int32_t *) _mm_malloc(4 * sizeof(int32_t), 128);
    auto dst_offset = (int32_t *) _mm_malloc(4 * sizeof(int32_t), 128);
    rhs_offset[0] = rhs_offset[1] = rhs_offset[2] = rhs_offset[3] = 4;
    scale[0] = scale[1] = scale[2] = scale[3] = 8;
    shift[0] = shift[1] = shift[2] = shift[3] = 10;
    dst_offset[0] = dst_offset[1] = dst_offset[2] = dst_offset[3] = 7;

    // run baseline
    gemm_xor_baseline(lhs_m, rhs_m, dst_m_baseline, height, depth, width,
                      rhs_offset[0], scale[0], shift[0], dst_offset[0]);

    // run avx warmup
    for (int count=0; count < NUM_RUN; count++){
    if (bit == 3) {
        gemm_xor_avx_b3_1x96(lhs_m, rhs_m, dst_m_avx, 
                             height, depth, width,
                             rhs_offset, dst_offset, scale, shift);
    } else if (bit == 4) {
        gemm_xor_avx_b4_1x128(lhs_m, rhs_m, dst_m_avx,
                             height, depth, width,
                              rhs_offset, dst_offset, scale, shift);
    } else if (bit == 5) {
        gemm_xor_avx_b5_1x96(lhs_m, rhs_m, dst_m_avx,
                             height, depth, width,
                             rhs_offset, dst_offset, scale, shift);
    } else if (bit == 6) {
        gemm_xor_avx_b6_1x96(lhs_m, rhs_m, dst_m_avx,
                             height, depth, width,
                             rhs_offset, dst_offset, scale, shift);
    }
    }

    // run avx
    auto start_time = std::chrono::system_clock::now();

    for (int count = 0; count < NUM_RUN; count++) {

        if (bit == 3) {
            gemm_xor_avx_b3_1x96(lhs_m, rhs_m, dst_m_avx, 
                                 height, depth, width,
                                 rhs_offset, dst_offset, scale, shift);
        } else if (bit == 4) {
            gemm_xor_avx_b4_1x128(lhs_m, rhs_m, dst_m_avx,
                                 height, depth, width,
                                  rhs_offset, dst_offset, scale, shift);
        } else if (bit == 5) {
            gemm_xor_avx_b5_1x96(lhs_m, rhs_m, dst_m_avx, 
                                 height, depth, width,
                                 rhs_offset, dst_offset, scale, shift);
        } else if (bit == 6) {
            gemm_xor_avx_b6_1x96(lhs_m, rhs_m, dst_m_avx, 
                                 height, depth, width,
                                 rhs_offset, dst_offset, scale, shift);
        }
    }

    auto end_time = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    float duration_us = (float) duration.count() / NUM_RUN;

    printf("%f\n", duration_us);

    _mm_free(rhs_offset);
    _mm_free(scale);
    _mm_free(shift);
    _mm_free(dst_offset);

    // ---------------------------------------------------------------- //
    // Compare
    // ---------------------------------------------------------------- //

    int diff_count = 0;

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < width; i++) {
            if (dst_m_baseline[j * width + i] != dst_m_avx[j * width + i]) {
                diff_count += 1;

                if (verbose)
                    printf("... different at [%d, %d], %d vs %d\n", j, i,
                           dst_m_baseline[j * width + i], dst_m_avx[j * width + i]);
            }
        }
    }

    if (verbose)
        printf("... total different count: %d\n", diff_count);


    // ---------------------------------------------------------------- //
    // Clean
    // ---------------------------------------------------------------- //

    _mm_free(lhs_m);
    _mm_free(rhs_m);
    _mm_free(dst_m_baseline);
    _mm_free(dst_m_avx);


    return EXIT_SUCCESS;
}
