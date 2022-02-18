#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <chrono>
#include <immintrin.h>
#include <malloc.h>
#include "kernel.h"

using namespace std;

void unpacking(const uint8_t* input, int depth, uint8_t* output) {
    int64_t size = (int64_t) depth/32;
    int8_t* a = (int8_t*) _mm_malloc(4 * sizeof(int8_t), 256);
    a[0] = 3;
    a[1] = 12;
    a[2] = 48;
    a[3] = -64;

    asm volatile(
    "movq %[size], %%r12 \n\t"

    "vpbroadcastb 0x00(%[a]), %%ymm0 \n\t"
    "vpbroadcastb 0x01(%[a]), %%ymm1 \n\t"
    "vpbroadcastb 0x02(%[a]), %%ymm2 \n\t"
    "vpbroadcastb 0x03(%[a]), %%ymm3 \n\t"

    "Loop%=: \n\t"

    "vpand (%[input]), %%ymm0, %%ymm4 \n\t"
    "vpand (%[input]), %%ymm1, %%ymm5 \n\t"
    "vpand (%[input]), %%ymm2, %%ymm6 \n\t"
    "vpand (%[input]), %%ymm3, %%ymm7 \n\t"


    "vpmovzxbw %%xmm4, %%ymm8 \n\t"
    "vpermq $0xee, %%ymm4, %%ymm4 \n\t"
    "vpmovzxbw %%xmm4, %%ymm9 \n\t"
    "vpmovzxbw %%xmm5, %%ymm10 \n\t"
    "vpermq $0xee, %%ymm5, %%ymm5 \n\t"
    "vpmovzxbw %%xmm5, %%ymm11 \n\t"
    "vpmovzxbw %%xmm6, %%ymm12 \n\t"
    "vpermq $0xee, %%ymm6, %%ymm6 \n\t"
    "vpmovzxbw %%xmm6, %%ymm13 \n\t"
    "vpmovzxbw %%xmm7, %%ymm14 \n\t"
    "vpermq $0xee, %%ymm7, %%ymm7 \n\t"
    "vpmovzxbw %%xmm7, %%ymm15 \n\t"

    "vpsllw $0x0e, %%ymm8, %%ymm8 \n\t"
    "vpsraw $0x0e, %%ymm8, %%ymm8 \n\t"
    "vpsllw $0x0e, %%ymm9, %%ymm9 \n\t"
    "vpsraw $0x0e, %%ymm9, %%ymm9 \n\t"
    "vpsllw $0x0c, %%ymm10, %%ymm10 \n\t"
    "vpsraw $0x0e, %%ymm10, %%ymm10 \n\t"
    "vpsllw $0x0c, %%ymm11, %%ymm11 \n\t"
    "vpsraw $0x0e, %%ymm11, %%ymm11 \n\t"
    "vpsllw $0x0a, %%ymm12, %%ymm12 \n\t"
    "vpsraw $0x0e, %%ymm12, %%ymm12 \n\t"
    "vpsllw $0x0a, %%ymm13, %%ymm13 \n\t"
    "vpsraw $0x0e, %%ymm13, %%ymm13 \n\t"
    "vpsllw $0x08, %%ymm14, %%ymm14 \n\t"
    "vpsraw $0x0e, %%ymm14, %%ymm14 \n\t"
    "vpsllw $0x08, %%ymm15, %%ymm15 \n\t"
    "vpsraw $0x0e, %%ymm15, %%ymm15 \n\t"

    "vpacksswb %%ymm9, %%ymm8, %%ymm4 \n\t"
    "vpacksswb %%ymm11, %%ymm10, %%ymm5 \n\t"
    "vpacksswb %%ymm13, %%ymm12, %%ymm6 \n\t"
    "vpacksswb %%ymm15, %%ymm14, %%ymm7 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm5, %%ymm5 \n\t"
    "vpermq $0xd8, %%ymm6, %%ymm6 \n\t"
    "vpermq $0xd8, %%ymm7, %%ymm7 \n\t"

    "vmovdqu %%ymm4, 0x00(%[output]) \n\t"
    "vmovdqu %%ymm5, 0x20(%[output]) \n\t"
    "vmovdqu %%ymm6, 0x40(%[output]) \n\t"
    "vmovdqu %%ymm7, 0x60(%[output]) \n\t"

    "addq $0x20, %[input] \n\t"
    "addq $0x80, %[output] \n\t"

    "decq %%r12 \n\t"
    "jnz Loop%= \n\t"
    : // outputs
    [input] "+r"(input), [output] "+r"(output)
    : // inputs
    [size] "r"(size), [a] "r"(a)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");
}

void unpacking_activation(const uint8_t* input, int depth, uint8_t* output) {
    int64_t size = (int64_t) (depth-1)/64+1;
    int8_t* a = (int8_t*) _mm_malloc(4 * sizeof(int8_t), 256);
    a[0] = 15;
    a[1] = -16;

    asm volatile(
    "movq %[size], %%r12 \n\t"

    "vpbroadcastb 0x00(%[a]), %%ymm0 \n\t"
    "vpbroadcastb 0x01(%[a]), %%ymm1 \n\t"

    "Loop%=: \n\t"

    "vpand (%[input]), %%ymm0, %%ymm2 \n\t"
    "vpand (%[input]), %%ymm1, %%ymm3 \n\t"
    "vpand 0x20(%[input]), %%ymm0, %%ymm4 \n\t"
    "vpand 0x20(%[input]), %%ymm1, %%ymm5 \n\t"

    "vpmovzxbw %%xmm2, %%ymm6 \n\t"
    "vpermq $0xee, %%ymm2, %%ymm2 \n\t"
    "vpmovzxbw %%xmm2, %%ymm7 \n\t"
    "vpmovzxbw %%xmm3, %%ymm8 \n\t"
    "vpermq $0xee, %%ymm3, %%ymm3 \n\t"
    "vpmovzxbw %%xmm3, %%ymm9 \n\t"
    "vpmovzxbw %%xmm4, %%ymm10 \n\t"
    "vpermq $0xee, %%ymm4, %%ymm4 \n\t"
    "vpmovzxbw %%xmm4, %%ymm11 \n\t"
    "vpmovzxbw %%xmm5, %%ymm12 \n\t"
    "vpermq $0xee, %%ymm5, %%ymm5 \n\t"
    "vpmovzxbw %%xmm5, %%ymm13 \n\t"

    "vpsllw $0x0c, %%ymm6, %%ymm6 \n\t"
    "vpsraw $0x0c, %%ymm6, %%ymm6 \n\t"
    "vpsllw $0x0c, %%ymm7, %%ymm7 \n\t"
    "vpsraw $0x0c, %%ymm7, %%ymm7 \n\t"
    "vpsllw $0x08, %%ymm8, %%ymm8 \n\t"
    "vpsraw $0x0c, %%ymm8, %%ymm8 \n\t"
    "vpsllw $0x08, %%ymm9, %%ymm9 \n\t"
    "vpsraw $0x0c, %%ymm9, %%ymm9 \n\t"
    "vpsllw $0x0c, %%ymm10, %%ymm10 \n\t"
    "vpsraw $0x0c, %%ymm10, %%ymm10 \n\t"
    "vpsllw $0x0c, %%ymm11, %%ymm11 \n\t"
    "vpsraw $0x0c, %%ymm11, %%ymm11 \n\t"
    "vpsllw $0x08, %%ymm12, %%ymm12 \n\t"
    "vpsraw $0x0c, %%ymm12, %%ymm12 \n\t"
    "vpsllw $0x08, %%ymm13, %%ymm13 \n\t"
    "vpsraw $0x0c, %%ymm13, %%ymm13 \n\t"

    "vpacksswb %%ymm7, %%ymm6, %%ymm2 \n\t"
    "vpacksswb %%ymm9, %%ymm8, %%ymm3 \n\t"
    "vpacksswb %%ymm11, %%ymm10, %%ymm4 \n\t"
    "vpacksswb %%ymm13, %%ymm12, %%ymm5 \n\t"
    "vpermq $0xd8, %%ymm2, %%ymm2 \n\t"
    "vpermq $0xd8, %%ymm3, %%ymm3 \n\t"
    "vpermq $0xd8, %%ymm4, %%ymm4 \n\t"
    "vpermq $0xd8, %%ymm5, %%ymm5 \n\t"

    "vpand %%ymm0, %%ymm2, %%ymm2 \n\t"
    "vpand %%ymm0, %%ymm3, %%ymm3 \n\t"
    "vpand %%ymm0, %%ymm4, %%ymm4 \n\t"
    "vpand %%ymm0, %%ymm5, %%ymm5 \n\t"

    "vmovdqu %%ymm2, 0x00(%[output]) \n\t"
    "vmovdqu %%ymm3, 0x20(%[output]) \n\t"
    "vmovdqu %%ymm4, 0x40(%[output]) \n\t"
    "vmovdqu %%ymm5, 0x60(%[output]) \n\t"

 
    "addq $0x40, %[input] \n\t"
    "addq $0x80, %[output] \n\t"

    "decq %%r12 \n\t"
    "jnz Loop%= \n\t"
    : // outputs
    [input] "+r"(input), [output] "+r"(output)
    : // inputs
    [size] "r"(size), [a] "r"(a)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");
}


void packing_activation(const uint8_t* input, int depth, uint8_t* output) {
    int64_t size = (int64_t) (depth-1)/64+1;
    int8_t* a = (int8_t*) _mm_malloc(4 * sizeof(int8_t), 256);
    a[0] = 15;
    a[1] = -16;

    asm volatile(
    "movq %[size], %%r12 \n\t"

    "vpbroadcastb 0x00(%[a]), %%ymm0 \n\t"
    "vpbroadcastb 0x01(%[a]), %%ymm1 \n\t"

    "Loop%=: \n\t"

    "vpand 0x00(%[input]), %%ymm0, %%ymm2 \n\t"
    "vpand 0x20(%[input]), %%ymm0, %%ymm3 \n\t"
    "vpand 0x40(%[input]), %%ymm0, %%ymm4 \n\t"
    "vpand 0x60(%[input]), %%ymm0, %%ymm5 \n\t"

    "vpsllw $0x04, %%ymm3, %%ymm3 \n\t"
    "vpsllw $0x04, %%ymm5, %%ymm5 \n\t"

    "vpor %%ymm2, %%ymm3, %%ymm2 \n\t"    
    "vpor %%ymm4, %%ymm5, %%ymm4 \n\t"    

    "vmovdqu %%ymm2, 0x00(%[output]) \n\t"
    "vmovdqu %%ymm4, 0x20(%[output]) \n\t"

    "addq $0x80, %[input] \n\t"
    "addq $0x40, %[output] \n\t"

    "decq %%r12 \n\t"
    "jnz Loop%= \n\t"
    : // outputs
    [input] "+r"(input), [output] "+r"(output)
    : // inputs
    [size] "r"(size), [a] "r"(a)
    : // clobbers
    "cc", "memory", "%ymm0", "%ymm1", "%ymm2", "%ymm3", "%ymm4", "%ymm5", "%ymm6", "%ymm7",
            "%ymm8", "%ymm9", "%ymm10", "%ymm11", "%ymm12", "%ymm13", "%ymm14", "%ymm15", "%r12");
//	printf("%d %d %d %d \n", output[0], output[1], output[2], output[3]);
//	printf("%d %d %d %d \n", output[32], output[33], output[34], output[35]);

}
