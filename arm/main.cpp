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

    //int8_t* lhs_m =(int8_t*)_mm_malloc(height*depth*sizeof(int8_t), 256);
    //int8_t* rhs_m =(int8_t*)_mm_malloc(width*depth*sizeof(int8_t), 256);
    //int32_t* dst_m =(int32_t*)_mm_malloc(height*width*sizeof(int32_t)+256, 256);
    //need to change into pointer of int8_t after appling Scale & Shift.
    //int32_t* dst_m_new =(int32_t*)_mm_malloc(height*width*sizeof(int32_t)+256, 256);
    //int8_t* dst_m_2 =(int8_t*)_mm_malloc(height*width*sizeof(int8_t)+256, 256);
    /*
    for(int j=0;j<height*depth;j++){
        lhs_m[j]=(char)(3*j*j%7+3*j)%2-1;
    }
    for(int j=0;j<width*depth;j++){
        rhs_m[j]=(char)(j*j*j%23+2*j)%4-4;
    }
    for(int j=0;j<height*width;j++){
        dst_m[j]=(char)(5*j+6*j*j)%2-1;
    }

    std::ifstream lhs_is(binary_path + lhs_fname, std::ios::in | std::ios::binary);
    if (lhs_is.is_open()) {
        lhs_is.read((char*) lhs_m, height * depth * sizeof(int8_t));
    }
    else {
        printf("LHS binary %s load fail", lhs_fname.c_str());
        return EXIT_FAILURE;
    }
    lhs_is.close();

    std::ifstream rhs_is(binary_path + rhs_fname, std::ios::in | std::ios::binary);
    if (rhs_is.is_open()) {
        rhs_is.read((char*) rhs_m, depth * width * sizeof(int8_t));
    }
    else {
        printf("RHS binary %s load fail", rhs_fname.c_str());
        return EXIT_FAILURE;
    }
    rhs_is.close();

    std::ifstream dst_is(binary_path + dst_fname, std::ios::in | std::ios::binary);
    if (dst_is.is_open()) {
        dst_is.read((char*) dst_m, height * width * sizeof(int32_t));
    }
    else {
        printf("DST binary %s load fail", lhs_fname.c_str());
        return EXIT_FAILURE;
    }
    dst_is.close();
*/
    // ---------------------------------------------------------------- //
    // Check
    // ---------------------------------------------------------------- //
/*
    printf("LHS Check...\n[");
    for (int i = 0; i < depth; i++) {
        printf("%d ", lhs_m[i]);
    }
    printf("]\n");

    printf("RHS Check...\n[");
    for (int i = 0; i < width; i++) {
        printf("%d ", rhs_m[i]);
    }
    printf("]\n");

    printf("DST Check...\n[");
    for (int i = 0; i < width; i++) {
        printf("%d ", dst_m[i]);
    }
    printf("]\n");
*/
    // ---------------------------------------------------------------- //
    // Run
    // ---------------------------------------------------------------- //

    /*
    while(true) {
        auto start_time = std::chrono::system_clock::now();

        if(mode == "xor"){
                  gemm_xor_avx(lhs_m, rhs_m, dst_m_2, height, depth, width,
                                rhs_offset, dst_offset, scale, shift);
        start_time = std::chrono::system_clock::now();

        for (int count = 0; count < min_time_counter; count++) {
                //gemm_xor_avx(lhs_m, rhs_m, dst_m_new, height, depth, width);
                  gemm_xor_avx(lhs_m, rhs_m, dst_m_2, height, depth, width,
                                rhs_offset, dst_offset, scale, shift);
            }
        }
        else {
        for (int count = 0; count < min_time_counter; count++) {
                gemm_xor_baseline(lhs_m, rhs_m, dst_m_new, height, depth, width);
        }
        }


        auto end_time = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        if (duration.count() > 10000) {
            printf("%f\n", (float)(duration.count()) / min_time_counter);
            break;
        }
        min_time_counter *=2;
    }
    */

    int32_t rhs_offset = 0;
    int32_t scale = 1;
    int32_t shift = 0;
    int32_t dst_offset = 0;

    auto start_time = std::chrono::system_clock::now();

    for (int count = 0; count < 100; count++) {
        gemm_xor_avx(lhs_m, rhs_m, dst_m, height, depth, width,
                     rhs_offset, dst_offset, scale, shift);
    }
    start_time = std::chrono::system_clock::now();
    for (int count = 0; count < NUM_RUN; count++) {
        //gemm_xor_avx(lhs_m, rhs_m, dst_m_new, height, depth, width);

        gemm_xor_avx(lhs_m, rhs_m, dst_m, height, depth, width,
                     rhs_offset, dst_offset, scale, shift);
    }

    //gemm_xor_avx(lhs_m, rhs_m, dst_m, height, depth, width,
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
