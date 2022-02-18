//
// Created by shchoi on 2021-01-28.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <chrono>

#include <malloc.h>

#define NUM_RUN 1000

#include "kernel/kernel.h"


using namespace std;


int main(int argc, char** argv) {

    // parse argc, argv
    // argv[1]: height
    // argv[2]: depth
    // argv[3]: width
    // argv[4]: binary_path
    // argv[4]: mode
    int height = std::atoi(argv[1]);
    int depth = std::atoi(argv[2]);
    int width = std::atoi(argv[3]);
    //printf("[LOG] height: %d, depth: %d, width: %d, path: %s, mode: %s\n", height, depth, width,
    //       binary_path.c_str(), mode.c_str());

    // ---------------------------------------------------------------- //
    // Load binary
    // ---------------------------------------------------------------- //


    std::string lhs_fname =
            "/lhs_" + std::to_string(height) + "x" + std::to_string(depth) + "_2bit.bin";
    std::string rhs_fname =
            "/rhs_" + std::to_string(depth) + "x" + std::to_string(width) + "_4bit.bin";
    std::string dst_fname =
            "/dst_" + std::to_string(height) + "x" + std::to_string(width) + "_32bit.bin";

    int8_t* lhs_m = new int8_t[height * depth];
    int8_t* rhs_m = new int8_t[depth * width];
    int8_t* dst_m = new int8_t[height * width];
    int32_t* dst_m_new = new int32_t[height * width];


    int32_t rhs_offset = 0;
    int32_t scale = 1;
    int32_t shift = 0;
    int32_t dst_offset = 0;

    auto start_time = std::chrono::system_clock::now();

    for (int count = 0; count < 100; count++) {
        gemm_xor_avx_4x32(lhs_m, rhs_m, dst_m, height, depth, width,
                          rhs_offset, dst_offset, scale, shift);
    }
    start_time = std::chrono::system_clock::now();

    for (int count = 0; count < NUM_RUN; count++) {
        //gemm_xor_avx(lhs_m, rhs_m, dst_m_new, height, depth, width);
        gemm_xor_avx_4x32(lhs_m, rhs_m, dst_m, height, depth, width,
                          rhs_offset, dst_offset, scale, shift);
    }

    //gemm_xor_avx_1x128(lhs_m, rhs_m, dst_m, height, depth, width,
//            rhs_offset, dst_offset, scale, shift);
    //gemm_xor_baseline(lhs_m, rhs_m, dst_m_new, height, depth, width);

    auto end_time = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    printf("%f\n", (float) (duration.count()) / NUM_RUN);
/*
    _mm_free(rhs_offset);
    _mm_free(scale);
    _mm_free(shift);
    _mm_free(dst_offset);*/
    // ---------------------------------------------------------------- //
    // Compare
    // ---------------------------------------------------------------- //

    int diff_count = 0;
/*
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < width; i++) {
            if (dst_m[j * width + i] != dst_m_new[j * width + i]) {
                diff_count += 1;
                printf("... different at [%d, %d], %d vs %d\n", j, i,
                        dst_m[j * width + i], dst_m_new[j * width + i]);
            }

        }
    }

    printf("... total different count: %d\n", diff_count);
*/

    // ---------------------------------------------------------------- //
    // Clean
    // ---------------------------------------------------------------- //

    delete[] lhs_m;
    delete[] rhs_m;
    delete[] dst_m;
    delete[] dst_m_new;
//    _mm_free(lhs_m);
//    _mm_free(rhs_m);
//    _mm_free(dst_m);
//    _mm_free(dst_m_new);


    return EXIT_SUCCESS;
}
