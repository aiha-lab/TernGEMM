#include "kernel.h"


void gemm_xor_baseline_32bit(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
                             int height, int depth, int width) {

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {

            int32_t temp = 0;
            for (int idx = 0; idx < depth; idx++) {
                temp += lhs[j * depth + idx] * rhs[width * idx + i];
            }

            dst[j * width + i] = temp;
        }
    }
}


void gemm_xor_baseline(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                       int height, int depth, int width,
                       int rhs_offset, int scale, int shift, int dst_offset) {

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {

            int32_t temp = 0;
            for (int idx = 0; idx < depth; idx++) {
                temp += lhs[j * depth + idx] * rhs[width * idx + i];
            }

            temp = scale * (temp - rhs_offset);
            temp = (temp >> shift) + dst_offset;

            dst[j * width + i] = static_cast<int8_t>(temp);
        }
    }
}
