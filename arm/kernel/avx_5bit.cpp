//
// Created by shchoi on 2021-01-28.
//
#include <malloc.h>
#include <arm_neon.h>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <cstring>
#include "kernel.h"

/*
void loop6(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
           int depth1, int depth2) {
    asm volatile(

    "dup v4.4s, wzr\n"
    "dup v5.4s, wzr\n"
    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v8.4s, wzr\n"
    "dup v9.4s, wzr\n"
    "dup v10.4s, wzr\n"
    "dup v11.4s, wzr\n"
    "dup v12.4s, wzr\n"
    "dup v13.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v16.4s, wzr\n"
    "dup v17.4s, wzr\n"
    "dup v18.4s, wzr\n"
    "dup v19.4s, wzr\n"
    "dup v20.4s, wzr\n"
    "dup v21.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"
    "dup v24.4s, wzr\n"
    "dup v25.4s, wzr\n"
    "dup v26.4s, wzr\n"
    "dup v27.4s, wzr\n"

    "mov x0, %[lhs]\n"

    "cmp %[depth1], #0\n"
    "beq LAST_LOOP \n"

    "LOOP16: \n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"

    "subs %[depth1], %[depth1], #1 \n"
    "bne LOOP16 \n"


    "LAST_LOOP:\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "subs %[depth2], %[depth2], #1 \n"
    "bne LAST_LOOP \n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "Finish :\n"

    "sshll v4.4s, v8.4h, #0\n"
    "sshll2 v5.4s, v8.8h, #0\n"
    "sshll v6.4s, v9.4h, #0\n"
    "sshll2 v7.4s, v9.8h, #0\n"
    "sshll v8.4s, v10.4h, #0\n"
    "sshll2 v9.4s, v10.8h, #0\n"
    "sshll v10.4s, v11.4h, #0\n"
    "sshll2 v11.4s, v11.8h, #0\n"

    "sshll v12.4s, v16.4h, #0\n"
    "sshll2 v13.4s, v16.8h, #0\n"
    "sshll v14.4s, v17.4h, #0\n"
    "sshll2 v15.4s, v17.8h, #0\n"
    "sshll v16.4s, v18.4h, #0\n"
    "sshll2 v17.4s, v18.8h, #0\n"
    "sshll v18.4s, v19.4h, #0\n"
    "sshll2 v19.4s, v19.8h, #0\n"

    "sshll v20.4s, v24.4h, #0\n"
    "sshll2 v21.4s, v24.8h, #0\n"
    "sshll v22.4s, v25.4h, #0\n"
    "sshll2 v23.4s, v25.8h, #0\n"
    "sshll v24.4s, v26.4h, #0\n"
    "sshll2 v25.4s, v26.8h, #0\n"
    "sshll v26.4s, v27.4h, #0\n"
    "sshll2 v27.4s, v27.8h, #0\n"

    "mov x0, %[dst]\n"

    "st1 {v4.4s}, [x0], #16\n"
    "st1 {v5.4s}, [x0], #16\n"
    "st1 {v6.4s}, [x0], #16\n"
    "st1 {v7.4s}, [x0], #16\n"
    "st1 {v8.4s}, [x0], #16\n"
    "st1 {v9.4s}, [x0], #16\n"
    "st1 {v10.4s}, [x0], #16\n"
    "st1 {v11.4s}, [x0], #16\n"
    "st1 {v12.4s}, [x0], #16\n"
    "st1 {v13.4s}, [x0], #16\n"
    "st1 {v14.4s}, [x0], #16\n"
    "st1 {v15.4s}, [x0], #16\n"
    "st1 {v16.4s}, [x0], #16\n"
    "st1 {v17.4s}, [x0], #16\n"
    "st1 {v18.4s}, [x0], #16\n"
    "st1 {v19.4s}, [x0], #16\n"
    "st1 {v20.4s}, [x0], #16\n"
    "st1 {v21.4s}, [x0], #16\n"
    "st1 {v22.4s}, [x0], #16\n"
    "st1 {v23.4s}, [x0], #16\n"
    "st1 {v24.4s}, [x0], #16\n"
    "st1 {v25.4s}, [x0], #16\n"
    "st1 {v26.4s}, [x0], #16\n"
    "st1 {v27.4s}, [x0]\n"
    :
    [lhs] "+r"(lhs), [rhs] "+r"(rhs), [dst] "+r"(dst)
    :
    [depth1] "r"(depth1), [depth2] "r"(depth2)
    :
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );

}
*/

void loop5(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
           int depth1, int depth2) {
    asm volatile(

    "dup v4.4s, wzr\n"
    "dup v5.4s, wzr\n"
    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v8.4s, wzr\n"
    "dup v9.4s, wzr\n"
    "dup v10.4s, wzr\n"
    "dup v11.4s, wzr\n"
    "dup v12.4s, wzr\n"
    "dup v13.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v16.4s, wzr\n"
    "dup v17.4s, wzr\n"
    "dup v18.4s, wzr\n"
    "dup v19.4s, wzr\n"
    "dup v20.4s, wzr\n"
    "dup v21.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"
    "dup v24.4s, wzr\n"
    "dup v25.4s, wzr\n"
    "dup v26.4s, wzr\n"
    "dup v27.4s, wzr\n"

    "mov x0, %[lhs]\n"

    "cmp %[depth1], #0\n"
    "beq LAST_LOOP \n"

    "LOOP16: \n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"


    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"

    "subs %[depth1], %[depth1], #1 \n"
    "bne LOOP16 \n"


    "LAST_LOOP:\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "subs %[depth2], %[depth2], #1 \n"
    "bne LAST_LOOP \n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "Finish :\n"

    "sshll v4.4s, v8.4h, #0\n"
    "sshll2 v5.4s, v8.8h, #0\n"
    "sshll v6.4s, v9.4h, #0\n"
    "sshll2 v7.4s, v9.8h, #0\n"
    "sshll v8.4s, v10.4h, #0\n"
    "sshll2 v9.4s, v10.8h, #0\n"
    "sshll v10.4s, v11.4h, #0\n"
    "sshll2 v11.4s, v11.8h, #0\n"

    "sshll v12.4s, v16.4h, #0\n"
    "sshll2 v13.4s, v16.8h, #0\n"
    "sshll v14.4s, v17.4h, #0\n"
    "sshll2 v15.4s, v17.8h, #0\n"
    "sshll v16.4s, v18.4h, #0\n"
    "sshll2 v17.4s, v18.8h, #0\n"
    "sshll v18.4s, v19.4h, #0\n"
    "sshll2 v19.4s, v19.8h, #0\n"

    "sshll v20.4s, v24.4h, #0\n"
    "sshll2 v21.4s, v24.8h, #0\n"
    "sshll v22.4s, v25.4h, #0\n"
    "sshll2 v23.4s, v25.8h, #0\n"
    "sshll v24.4s, v26.4h, #0\n"
    "sshll2 v25.4s, v26.8h, #0\n"
    "sshll v26.4s, v27.4h, #0\n"
    "sshll2 v27.4s, v27.8h, #0\n"

    "mov x0, %[dst]\n"

    "st1 {v4.4s}, [x0], #16\n"
    "st1 {v5.4s}, [x0], #16\n"
    "st1 {v6.4s}, [x0], #16\n"
    "st1 {v7.4s}, [x0], #16\n"
    "st1 {v8.4s}, [x0], #16\n"
    "st1 {v9.4s}, [x0], #16\n"
    "st1 {v10.4s}, [x0], #16\n"
    "st1 {v11.4s}, [x0], #16\n"
    "st1 {v12.4s}, [x0], #16\n"
    "st1 {v13.4s}, [x0], #16\n"
    "st1 {v14.4s}, [x0], #16\n"
    "st1 {v15.4s}, [x0], #16\n"
    "st1 {v16.4s}, [x0], #16\n"
    "st1 {v17.4s}, [x0], #16\n"
    "st1 {v18.4s}, [x0], #16\n"
    "st1 {v19.4s}, [x0], #16\n"
    "st1 {v20.4s}, [x0], #16\n"
    "st1 {v21.4s}, [x0], #16\n"
    "st1 {v22.4s}, [x0], #16\n"
    "st1 {v23.4s}, [x0], #16\n"
    "st1 {v24.4s}, [x0], #16\n"
    "st1 {v25.4s}, [x0], #16\n"
    "st1 {v26.4s}, [x0], #16\n"
    "st1 {v27.4s}, [x0]\n"
    :
    [lhs] "+r"(lhs), [rhs] "+r"(rhs), [dst] "+r"(dst)
    :
    [depth1] "r"(depth1), [depth2] "r"(depth2)
    :
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );

}

/*
void loop4(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
           int depth1, int depth2) {
    asm volatile(

    "dup v4.4s, wzr\n"
    "dup v5.4s, wzr\n"
    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v8.4s, wzr\n"
    "dup v9.4s, wzr\n"
    "dup v10.4s, wzr\n"
    "dup v11.4s, wzr\n"
    "dup v12.4s, wzr\n"
    "dup v13.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v16.4s, wzr\n"
    "dup v17.4s, wzr\n"
    "dup v18.4s, wzr\n"
    "dup v19.4s, wzr\n"
    "dup v20.4s, wzr\n"
    "dup v21.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"
    "dup v24.4s, wzr\n"
    "dup v25.4s, wzr\n"
    "dup v26.4s, wzr\n"
    "dup v27.4s, wzr\n"

    "mov x0, %[lhs]\n"

    "cmp %[depth1], #0\n"
    "beq LAST_LOOP \n"

    "LOOP16: \n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"

    "subs %[depth1], %[depth1], #1 \n"
    "bne LOOP16 \n"


    "LAST_LOOP:\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "subs %[depth2], %[depth2], #1 \n"
    "bne LAST_LOOP \n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "Finish :\n"

    "sshll v4.4s, v8.4h, #0\n"
    "sshll2 v5.4s, v8.8h, #0\n"
    "sshll v6.4s, v9.4h, #0\n"
    "sshll2 v7.4s, v9.8h, #0\n"
    "sshll v8.4s, v10.4h, #0\n"
    "sshll2 v9.4s, v10.8h, #0\n"
    "sshll v10.4s, v11.4h, #0\n"
    "sshll2 v11.4s, v11.8h, #0\n"

    "sshll v12.4s, v16.4h, #0\n"
    "sshll2 v13.4s, v16.8h, #0\n"
    "sshll v14.4s, v17.4h, #0\n"
    "sshll2 v15.4s, v17.8h, #0\n"
    "sshll v16.4s, v18.4h, #0\n"
    "sshll2 v17.4s, v18.8h, #0\n"
    "sshll v18.4s, v19.4h, #0\n"
    "sshll2 v19.4s, v19.8h, #0\n"

    "sshll v20.4s, v24.4h, #0\n"
    "sshll2 v21.4s, v24.8h, #0\n"
    "sshll v22.4s, v25.4h, #0\n"
    "sshll2 v23.4s, v25.8h, #0\n"
    "sshll v24.4s, v26.4h, #0\n"
    "sshll2 v25.4s, v26.8h, #0\n"
    "sshll v26.4s, v27.4h, #0\n"
    "sshll2 v27.4s, v27.8h, #0\n"

    "mov x0, %[dst]\n"

    "st1 {v4.4s}, [x0], #16\n"
    "st1 {v5.4s}, [x0], #16\n"
    "st1 {v6.4s}, [x0], #16\n"
    "st1 {v7.4s}, [x0], #16\n"
    "st1 {v8.4s}, [x0], #16\n"
    "st1 {v9.4s}, [x0], #16\n"
    "st1 {v10.4s}, [x0], #16\n"
    "st1 {v11.4s}, [x0], #16\n"
    "st1 {v12.4s}, [x0], #16\n"
    "st1 {v13.4s}, [x0], #16\n"
    "st1 {v14.4s}, [x0], #16\n"
    "st1 {v15.4s}, [x0], #16\n"
    "st1 {v16.4s}, [x0], #16\n"
    "st1 {v17.4s}, [x0], #16\n"
    "st1 {v18.4s}, [x0], #16\n"
    "st1 {v19.4s}, [x0], #16\n"
    "st1 {v20.4s}, [x0], #16\n"
    "st1 {v21.4s}, [x0], #16\n"
    "st1 {v22.4s}, [x0], #16\n"
    "st1 {v23.4s}, [x0], #16\n"
    "st1 {v24.4s}, [x0], #16\n"
    "st1 {v25.4s}, [x0], #16\n"
    "st1 {v26.4s}, [x0], #16\n"
    "st1 {v27.4s}, [x0]\n"
    :
    [lhs] "+r"(lhs), [rhs] "+r"(rhs), [dst] "+r"(dst)
    :
    [depth1] "r"(depth1), [depth2] "r"(depth2)
    :
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );

}
 */
/*
void loop3(const int8_t* lhs, const int8_t* rhs, int32_t* dst,
           int depth1, int depth2) {
    asm volatile(

    "dup v4.4s, wzr\n"
    "dup v5.4s, wzr\n"
    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v8.4s, wzr\n"
    "dup v9.4s, wzr\n"
    "dup v10.4s, wzr\n"
    "dup v11.4s, wzr\n"
    "dup v12.4s, wzr\n"
    "dup v13.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v16.4s, wzr\n"
    "dup v17.4s, wzr\n"
    "dup v18.4s, wzr\n"
    "dup v19.4s, wzr\n"
    "dup v20.4s, wzr\n"
    "dup v21.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"
    "dup v24.4s, wzr\n"
    "dup v25.4s, wzr\n"
    "dup v26.4s, wzr\n"
    "dup v27.4s, wzr\n"

    "mov x0, %[lhs]\n"

    "cmp %[depth1], #0\n"
    "beq LAST_LOOP \n"

    "LOOP16: \n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v14.4s, wzr\n"
    "dup v15.4s, wzr\n"
    "dup v22.4s, wzr\n"
    "dup v23.4s, wzr\n"

    "subs %[depth1], %[depth1], #1 \n"
    "bne LOOP16 \n"


    "LAST_LOOP:\n"
    "ld1r {v0.16b}, [x0], #1 \n"

    "ld1 {v4.16b}, [%[rhs]], #16 \n"
    "ld1 {v5.16b}, [%[rhs]], #16 \n"
    "ld1 {v12.16b}, [%[rhs]], #16 \n"
    "ld1 {v13.16b}, [%[rhs]], #16 \n"
    "ld1 {v20.16b}, [%[rhs]], #16 \n"
    "ld1 {v21.16b}, [%[rhs]], #16 \n"

    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"

    "eor v4.16b, v4.16b, v1.16b\n"
    "eor v5.16b, v5.16b, v1.16b\n"
    "eor v12.16b, v12.16b, v1.16b\n"
    "eor v13.16b, v13.16b, v1.16b\n"
    "eor v20.16b, v20.16b, v1.16b\n"
    "eor v21.16b, v21.16b, v1.16b\n"

    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "sub v12.16b, v1.16b, v12.16b\n"
    "sub v13.16b, v1.16b, v13.16b\n"
    "sub v20.16b, v1.16b, v20.16b\n"
    "sub v21.16b, v1.16b, v21.16b\n"

    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "and v12.16b, v12.16b, v0.16b\n"
    "and v13.16b, v13.16b, v0.16b\n"
    "and v20.16b, v20.16b, v0.16b\n"
    "and v21.16b, v21.16b, v0.16b\n"

    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"
    "add v14.16b, v14.16b, v12.16b\n"
    "add v15.16b, v15.16b, v13.16b\n"
    "add v22.16b, v22.16b, v20.16b\n"
    "add v23.16b, v23.16b, v21.16b\n"

    "subs %[depth2], %[depth2], #1 \n"
    "bne LAST_LOOP \n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v16.8h, v16.8h, v14.8b\n"
    "saddw2 v17.8h, v17.8h, v14.16b\n"
    "saddw v18.8h, v18.8h, v15.8b\n"
    "saddw2 v19.8h, v19.8h, v15.16b\n"
    "saddw v24.8h, v24.8h, v22.8b\n"
    "saddw2 v25.8h, v25.8h, v22.16b\n"
    "saddw v26.8h, v26.8h, v23.8b\n"
    "saddw2 v27.8h, v27.8h, v23.16b\n"

    "Finish :\n"

    "sshll v4.4s, v8.4h, #0\n"
    "sshll2 v5.4s, v8.8h, #0\n"
    "sshll v6.4s, v9.4h, #0\n"
    "sshll2 v7.4s, v9.8h, #0\n"
    "sshll v8.4s, v10.4h, #0\n"
    "sshll2 v9.4s, v10.8h, #0\n"
    "sshll v10.4s, v11.4h, #0\n"
    "sshll2 v11.4s, v11.8h, #0\n"

    "sshll v12.4s, v16.4h, #0\n"
    "sshll2 v13.4s, v16.8h, #0\n"
    "sshll v14.4s, v17.4h, #0\n"
    "sshll2 v15.4s, v17.8h, #0\n"
    "sshll v16.4s, v18.4h, #0\n"
    "sshll2 v17.4s, v18.8h, #0\n"
    "sshll v18.4s, v19.4h, #0\n"
    "sshll2 v19.4s, v19.8h, #0\n"

    "sshll v20.4s, v24.4h, #0\n"
    "sshll2 v21.4s, v24.8h, #0\n"
    "sshll v22.4s, v25.4h, #0\n"
    "sshll2 v23.4s, v25.8h, #0\n"
    "sshll v24.4s, v26.4h, #0\n"
    "sshll2 v25.4s, v26.8h, #0\n"
    "sshll v26.4s, v27.4h, #0\n"
    "sshll2 v27.4s, v27.8h, #0\n"

    "mov x0, %[dst]\n"

    "st1 {v4.4s}, [x0], #16\n"
    "st1 {v5.4s}, [x0], #16\n"
    "st1 {v6.4s}, [x0], #16\n"
    "st1 {v7.4s}, [x0], #16\n"
    "st1 {v8.4s}, [x0], #16\n"
    "st1 {v9.4s}, [x0], #16\n"
    "st1 {v10.4s}, [x0], #16\n"
    "st1 {v11.4s}, [x0], #16\n"
    "st1 {v12.4s}, [x0], #16\n"
    "st1 {v13.4s}, [x0], #16\n"
    "st1 {v14.4s}, [x0], #16\n"
    "st1 {v15.4s}, [x0], #16\n"
    "st1 {v16.4s}, [x0], #16\n"
    "st1 {v17.4s}, [x0], #16\n"
    "st1 {v18.4s}, [x0], #16\n"
    "st1 {v19.4s}, [x0], #16\n"
    "st1 {v20.4s}, [x0], #16\n"
    "st1 {v21.4s}, [x0], #16\n"
    "st1 {v22.4s}, [x0], #16\n"
    "st1 {v23.4s}, [x0], #16\n"
    "st1 {v24.4s}, [x0], #16\n"
    "st1 {v25.4s}, [x0], #16\n"
    "st1 {v26.4s}, [x0], #16\n"
    "st1 {v27.4s}, [x0]\n"
    :
    [lhs] "+r"(lhs), [rhs] "+r"(rhs), [dst] "+r"(dst)
    :
    [depth1] "r"(depth1), [depth2] "r"(depth2)
    :
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );

}
*/
void Scale_Shift(int32_t* dst, int8_t* result,
                 int32_t rhs_offset, int32_t dst_offset,
                 int32_t scale, int32_t shift) {
    asm volatile (

    "mov x0, %[dst]\n"

    "ld1 {v0.4s}, [x0], #16 \n"
    "ld1 {v1.4s}, [x0], #16 \n"
    "ld1 {v2.4s}, [x0], #16 \n"
    "ld1 {v3.4s}, [x0], #16 \n"
    "ld1 {v4.4s}, [x0], #16 \n"
    "ld1 {v5.4s}, [x0], #16 \n"
    "ld1 {v6.4s}, [x0], #16 \n"
    "ld1 {v7.4s}, [x0], #16 \n"
    "ld1 {v8.4s}, [x0], #16 \n"
    "ld1 {v9.4s}, [x0], #16 \n"
    "ld1 {v10.4s}, [x0], #16 \n"
    "ld1 {v11.4s}, [x0], #16 \n"
    "ld1 {v12.4s}, [x0], #16 \n"
    "ld1 {v13.4s}, [x0], #16 \n"
    "ld1 {v14.4s}, [x0], #16 \n"
    "ld1 {v15.4s}, [x0], #16 \n"
    "ld1 {v16.4s}, [x0], #16 \n"
    "ld1 {v17.4s}, [x0], #16 \n"
    "ld1 {v18.4s}, [x0], #16 \n"
    "ld1 {v19.4s}, [x0], #16 \n"
    "ld1 {v20.4s}, [x0], #16 \n"
    "ld1 {v21.4s}, [x0], #16 \n"
    "ld1 {v22.4s}, [x0], #16 \n"
    "ld1 {v23.4s}, [x0] \n"

    "mov x0, %[rhs_offset]\n"
    "dup v24.4s, w0 \n"

    "sub v0.4s, v0.4s, v24.4s \n"
    "sub v1.4s, v1.4s, v24.4s \n"
    "sub v2.4s, v2.4s, v24.4s \n"
    "sub v3.4s, v3.4s, v24.4s \n"
    "sub v4.4s, v4.4s, v24.4s \n"
    "sub v5.4s, v5.4s, v24.4s \n"
    "sub v6.4s, v6.4s, v24.4s \n"
    "sub v7.4s, v7.4s, v24.4s \n"
    "sub v8.4s, v8.4s, v24.4s \n"
    "sub v9.4s, v9.4s, v24.4s \n"
    "sub v10.4s, v10.4s, v24.4s \n"
    "sub v11.4s, v11.4s, v24.4s \n"
    "sub v12.4s, v12.4s, v24.4s \n"
    "sub v13.4s, v13.4s, v24.4s \n"
    "sub v14.4s, v14.4s, v24.4s \n"
    "sub v15.4s, v15.4s, v24.4s \n"
    "sub v16.4s, v16.4s, v24.4s \n"
    "sub v17.4s, v17.4s, v24.4s \n"
    "sub v18.4s, v18.4s, v24.4s \n"
    "sub v19.4s, v19.4s, v24.4s \n"
    "sub v20.4s, v20.4s, v24.4s \n"
    "sub v21.4s, v21.4s, v24.4s \n"
    "sub v22.4s, v22.4s, v24.4s \n"
    "sub v23.4s, v23.4s, v24.4s \n"

    "mov x0, %[scale]\n"
    "dup v24.4s, w0 \n"

    "mul v0.4s, v0.4s, v24.4s \n"
    "mul v1.4s, v1.4s, v24.4s \n"
    "mul v2.4s, v2.4s, v24.4s \n"
    "mul v3.4s, v3.4s, v24.4s \n"
    "mul v4.4s, v4.4s, v24.4s \n"
    "mul v5.4s, v5.4s, v24.4s \n"
    "mul v6.4s, v6.4s, v24.4s \n"
    "mul v7.4s, v7.4s, v24.4s \n"
    "mul v8.4s, v8.4s, v24.4s \n"
    "mul v9.4s, v9.4s, v24.4s \n"
    "mul v10.4s, v10.4s, v24.4s \n"
    "mul v11.4s, v11.4s, v24.4s \n"
    "mul v12.4s, v12.4s, v24.4s \n"
    "mul v13.4s, v13.4s, v24.4s \n"
    "mul v14.4s, v14.4s, v24.4s \n"
    "mul v15.4s, v15.4s, v24.4s \n"
    "mul v16.4s, v16.4s, v24.4s \n"
    "mul v17.4s, v17.4s, v24.4s \n"
    "mul v18.4s, v18.4s, v24.4s \n"
    "mul v19.4s, v19.4s, v24.4s \n"
    "mul v20.4s, v20.4s, v24.4s \n"
    "mul v21.4s, v21.4s, v24.4s \n"
    "mul v22.4s, v22.4s, v24.4s \n"
    "mul v23.4s, v23.4s, v24.4s \n"

    "mov x0, %[shift]\n"
    "dup v24.4s, w0 \n"

    "sshl v0.4s, v0.4s, v24.4s \n"
    "sshl v1.4s, v1.4s, v24.4s \n"
    "sshl v2.4s, v2.4s, v24.4s \n"
    "sshl v3.4s, v3.4s, v24.4s \n"
    "sshl v4.4s, v4.4s, v24.4s \n"
    "sshl v5.4s, v5.4s, v24.4s \n"
    "sshl v6.4s, v6.4s, v24.4s \n"
    "sshl v7.4s, v7.4s, v24.4s \n"
    "sshl v8.4s, v8.4s, v24.4s \n"
    "sshl v9.4s, v9.4s, v24.4s \n"
    "sshl v10.4s, v10.4s, v24.4s \n"
    "sshl v11.4s, v11.4s, v24.4s \n"
    "sshl v12.4s, v12.4s, v24.4s \n"
    "sshl v13.4s, v13.4s, v24.4s \n"
    "sshl v14.4s, v14.4s, v24.4s \n"
    "sshl v15.4s, v15.4s, v24.4s \n"
    "sshl v16.4s, v16.4s, v24.4s \n"
    "sshl v17.4s, v17.4s, v24.4s \n"
    "sshl v18.4s, v18.4s, v24.4s \n"
    "sshl v19.4s, v19.4s, v24.4s \n"
    "sshl v20.4s, v20.4s, v24.4s \n"
    "sshl v21.4s, v21.4s, v24.4s \n"
    "sshl v22.4s, v22.4s, v24.4s \n"
    "sshl v23.4s, v23.4s, v24.4s \n"

    "mov x0, %[dst_offset]\n"
    "dup v24.4s, w0 \n"

    "add v0.4s, v0.4s, v24.4s \n"
    "add v1.4s, v1.4s, v24.4s \n"
    "add v2.4s, v2.4s, v24.4s \n"
    "add v3.4s, v3.4s, v24.4s \n"
    "add v4.4s, v4.4s, v24.4s \n"
    "add v5.4s, v5.4s, v24.4s \n"
    "add v6.4s, v6.4s, v24.4s \n"
    "add v7.4s, v7.4s, v24.4s \n"
    "add v8.4s, v8.4s, v24.4s \n"
    "add v9.4s, v9.4s, v24.4s \n"
    "add v10.4s, v10.4s, v24.4s \n"
    "add v11.4s, v11.4s, v24.4s \n"
    "add v12.4s, v12.4s, v24.4s \n"
    "add v13.4s, v13.4s, v24.4s \n"
    "add v14.4s, v14.4s, v24.4s \n"
    "add v15.4s, v15.4s, v24.4s \n"
    "add v16.4s, v16.4s, v24.4s \n"
    "add v17.4s, v17.4s, v24.4s \n"
    "add v18.4s, v18.4s, v24.4s \n"
    "add v19.4s, v19.4s, v24.4s \n"
    "add v20.4s, v20.4s, v24.4s \n"
    "add v21.4s, v21.4s, v24.4s \n"
    "add v22.4s, v22.4s, v24.4s \n"
    "add v23.4s, v23.4s, v24.4s \n"

    "xtn v0.4h, v0.4s \n"
    "xtn2 v0.8h, v1.4s \n"
    "xtn v2.4h, v2.4s \n"
    "xtn2 v2.8h, v3.4s \n"
    "xtn v4.4h, v4.4s \n"
    "xtn2 v4.8h, v5.4s \n"
    "xtn v6.4h, v6.4s \n"
    "xtn2 v6.8h, v7.4s \n"
    "xtn v8.4h, v8.4s \n"
    "xtn2 v8.8h, v9.4s \n"
    "xtn v10.4h, v10.4s \n"
    "xtn2 v10.8h, v11.4s \n"
    "xtn v12.4h, v12.4s \n"
    "xtn2 v12.8h, v13.4s \n"
    "xtn v14.4h, v14.4s \n"
    "xtn2 v14.8h, v15.4s \n"
    "xtn v16.4h, v16.4s \n"
    "xtn2 v16.8h, v17.4s \n"
    "xtn v18.4h, v18.4s \n"
    "xtn2 v18.8h, v19.4s \n"
    "xtn v20.4h, v20.4s \n"
    "xtn2 v20.8h, v21.4s \n"
    "xtn v22.4h, v22.4s \n"
    "xtn2 v22.8h, v23.4s \n"

    "xtn v26.8b, v0.8h \n"
    "xtn2 v26.16b, v2.8h \n"
    "xtn v27.8b, v4.8h \n"
    "xtn2 v27.16b, v6.8h \n"
    "xtn v28.8b, v8.8h \n"
    "xtn2 v28.16b, v10.8h \n"
    "xtn v29.8b, v12.8h \n"
    "xtn2 v29.16b, v14.8h \n"
    "xtn v30.8b, v16.8h \n"
    "xtn2 v30.16b, v18.8h \n"
    "xtn v31.8b, v20.8h \n"
    "xtn2 v31.16b, v22.8h \n"

    "mov x0, %[result]\n"

    "st1 {v26.16b}, [x0], #16\n"
    "st1 {v27.16b}, [x0], #16\n"
    "st1 {v28.16b}, [x0], #16\n"
    "st1 {v29.16b}, [x0], #16\n"
    "st1 {v30.16b}, [x0], #16\n"
    "st1 {v31.16b}, [x0]\n"


    : // outputs
    [dst] "+r"(dst), [result] "+r"(result)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );
}

void dst_init(int32_t* dst) {
    asm volatile(
    "mov x0, %[dst]\n"
    "dup v0.4s, wzr\n"

    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v0.16b}, [x0]\n"

    : // outputs
    [dst] "+r"(dst)
    : // inputs
    : // clobbers
    "cc", "memory", "x0", "v0"
    );
}


void dst_add(int32_t* dst, int32_t* dst_temp) {
    asm volatile(
    "mov x0, %[dst_temp]\n"

    "ld1 {v0.4s}, [x0], #16 \n"
    "ld1 {v1.4s}, [x0], #16 \n"
    "ld1 {v2.4s}, [x0], #16 \n"
    "ld1 {v3.4s}, [x0], #16 \n"
    "ld1 {v4.4s}, [x0], #16 \n"
    "ld1 {v5.4s}, [x0], #16 \n"
    "ld1 {v6.4s}, [x0], #16 \n"
    "ld1 {v7.4s}, [x0], #16 \n"
    "ld1 {v8.4s}, [x0], #16 \n"
    "ld1 {v9.4s}, [x0], #16 \n"
    "ld1 {v10.4s}, [x0], #16 \n"
    "ld1 {v11.4s}, [x0], #16 \n"
    "ld1 {v12.4s}, [x0], #16 \n"
    "ld1 {v13.4s}, [x0], #16 \n"
    "ld1 {v14.4s}, [x0], #16 \n"
    "ld1 {v15.4s}, [x0], #16 \n"
    "ld1 {v16.4s}, [x0], #16 \n"
    "ld1 {v17.4s}, [x0], #16 \n"
    "ld1 {v18.4s}, [x0], #16 \n"
    "ld1 {v19.4s}, [x0], #16 \n"
    "ld1 {v20.4s}, [x0], #16 \n"
    "ld1 {v21.4s}, [x0], #16 \n"
    "ld1 {v22.4s}, [x0], #16 \n"
    "ld1 {v23.4s}, [x0] \n"

    "mov x0, %[dst]\n"
    "ld1 {v24.4s}, [x0], #16 \n"
    "ld1 {v25.4s}, [x0], #16 \n"
    "ld1 {v26.4s}, [x0], #16 \n"
    "ld1 {v27.4s}, [x0], #16 \n"
    "ld1 {v28.4s}, [x0], #16 \n"
    "ld1 {v29.4s}, [x0], #16 \n"
    "ld1 {v30.4s}, [x0], #16 \n"
    "ld1 {v31.4s}, [x0], #16 \n"
    "add v0.4s, v0.4s, v24.4s \n"
    "add v1.4s, v1.4s, v24.4s \n"
    "add v2.4s, v2.4s, v24.4s \n"
    "add v3.4s, v3.4s, v24.4s \n"
    "add v4.4s, v4.4s, v24.4s \n"
    "add v5.4s, v5.4s, v24.4s \n"
    "add v6.4s, v6.4s, v24.4s \n"
    "add v7.4s, v7.4s, v24.4s \n"
    "ld1 {v24.4s}, [x0], #16 \n"
    "ld1 {v25.4s}, [x0], #16 \n"
    "ld1 {v26.4s}, [x0], #16 \n"
    "ld1 {v27.4s}, [x0], #16 \n"
    "ld1 {v28.4s}, [x0], #16 \n"
    "ld1 {v29.4s}, [x0], #16 \n"
    "ld1 {v30.4s}, [x0], #16 \n"
    "ld1 {v31.4s}, [x0], #16 \n"
    "add v8.4s, v8.4s, v24.4s \n"
    "add v9.4s, v9.4s, v24.4s \n"
    "add v10.4s, v10.4s, v24.4s \n"
    "add v11.4s, v11.4s, v24.4s \n"
    "add v12.4s, v12.4s, v24.4s \n"
    "add v13.4s, v13.4s, v24.4s \n"
    "add v14.4s, v14.4s, v24.4s \n"
    "add v15.4s, v15.4s, v24.4s \n"
    "ld1 {v24.4s}, [x0], #16 \n"
    "ld1 {v25.4s}, [x0], #16 \n"
    "ld1 {v26.4s}, [x0], #16 \n"
    "ld1 {v27.4s}, [x0], #16 \n"
    "ld1 {v28.4s}, [x0], #16 \n"
    "ld1 {v29.4s}, [x0], #16 \n"
    "ld1 {v30.4s}, [x0], #16 \n"
    "ld1 {v31.4s}, [x0] \n"
    "add v16.4s, v16.4s, v24.4s \n"
    "add v17.4s, v17.4s, v24.4s \n"
    "add v18.4s, v18.4s, v24.4s \n"
    "add v19.4s, v19.4s, v24.4s \n"
    "add v20.4s, v20.4s, v24.4s \n"
    "add v21.4s, v21.4s, v24.4s \n"
    "add v22.4s, v22.4s, v24.4s \n"
    "add v23.4s, v23.4s, v24.4s \n"

    "mov x0, %[dst]\n"
    "st1 {v0.16b}, [x0], #16\n"
    "st1 {v1.16b}, [x0], #16\n"
    "st1 {v2.16b}, [x0], #16\n"
    "st1 {v3.16b}, [x0], #16\n"
    "st1 {v4.16b}, [x0], #16\n"
    "st1 {v5.16b}, [x0], #16\n"
    "st1 {v6.16b}, [x0], #16\n"
    "st1 {v7.16b}, [x0], #16\n"
    "st1 {v8.16b}, [x0], #16\n"
    "st1 {v9.16b}, [x0], #16\n"
    "st1 {v10.16b}, [x0], #16\n"
    "st1 {v11.16b}, [x0], #16\n"
    "st1 {v12.16b}, [x0], #16\n"
    "st1 {v13.16b}, [x0], #16\n"
    "st1 {v14.16b}, [x0], #16\n"
    "st1 {v15.16b}, [x0], #16\n"
    "st1 {v16.16b}, [x0], #16\n"
    "st1 {v17.16b}, [x0], #16\n"
    "st1 {v18.16b}, [x0], #16\n"
    "st1 {v19.16b}, [x0], #16\n"
    "st1 {v20.16b}, [x0], #16\n"
    "st1 {v21.16b}, [x0], #16\n"
    "st1 {v22.16b}, [x0], #16\n"
    "st1 {v23.16b}, [x0]\n"
    : // outputs
    [dst] "+r"(dst), [dst_temp] "+r"(dst_temp)
    : // inputs
    : // clobbers
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );
}

void gemm_xor_avx_big(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                      int height, int depth, int width,
                      int32_t rhs_offset, int32_t dst_offset,
                      int32_t scale, int32_t shift) {
    //int32_t depth_outer = (depth-1)/1024-1;
    //int32_t depth_last_2nd = 1024;
    //int32_t depth_last = (depth-1)%1024+1;
    int32_t depth_outer = (depth - 1) / 2048 - 1;
    int32_t depth_last_2nd = 2048;
    int32_t depth_last = (depth - 1) % 2048 + 1;
    //int32_t depth_outer = (depth-1)/4096-1;
    //int32_t depth_last_2nd = 4096;
    //int32_t depth_last = (depth-1)%4096+1;
    //int32_t depth_outer = (depth-1)/8192-1;
    //int32_t depth_last_2nd = 8192;
    //int32_t depth_last = (depth-1)%8192+1;
    if (depth_last < 96) {
        depth_last_2nd -= 95;
        depth_last += 95;
    }
    int64_t depth1 = (int64_t)(depth_last - 1) / 8;
    int64_t depth2 = (int64_t)(depth_last - 1) % 8 + 1;
    int64_t depth3 = (int64_t)(depth_last_2nd - 1) / 8;
    int64_t depth4 = (int64_t)(depth_last_2nd - 1) % 8 + 1;

    int8_t* rhs_m = new int8_t[depth * 96];
    int32_t* dst_temp = new int32_t[96];
    int32_t* dst_acc = new int32_t[96];

    for (int i = 0; i < (width - 1) / 96; i++) {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width + 96 * i) * sizeof(int8_t), 96 * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            dst_init(dst_acc);
            for (int k = 0; k < depth_outer; k++) {
                //loop6(lhs+depth*j+k*1024, rhs_m+k*1024*96, dst_temp, 340, 3);
                loop5(lhs + depth * j + k * 2048, rhs_m + k * 2048 * 96, dst_temp, 292, 3);
                //loop4(lhs+depth*j+k*4096, rhs_m+k*4096*96, dst_temp, 272, 15);
                //loop3(lhs+depth*j+k*8192, rhs_m+k*8192*96, dst_temp, 264, 11);

                dst_add(dst_acc, dst_temp);
            }
            //loop6(lhs+depth*j+depth_outer*1024, rhs_m+depth_outer*1024*96, dst_temp, depth3, depth4);
            loop5(lhs + depth * j + depth_outer * 2048, rhs_m + depth_outer * 2048 * 96, dst_temp, depth3, depth4);
            //loop4(lhs+depth*j+depth_outer*4096, rhs_m+depth_outer*4096*96, dst_temp, depth3, depth4);
            //loop3(lhs+depth*j+depth_outer*8192, rhs_m+depth_outer*8192*96, dst_temp, depth3, depth4);
            dst_add(dst_acc, dst_temp);

            //loop6(lhs+depth*j+depth_outer*1024+depth_last_2nd, rhs_m+(depth_outer*1024+depth_last_2nd)*96, dst_temp, depth1, depth2);
            loop5(lhs + depth * j + depth_outer * 2048 + depth_last_2nd, rhs_m + (depth_outer * 2048 + depth_last_2nd) * 96, dst_temp, depth1, depth2);
            //loop4(lhs+depth*j+depth_outer*4096+depth_last_2nd, rhs_m+(depth_outer*4096+depth_last_2nd)*96, dst_temp, depth1, depth2);
            //loop3(lhs+depth*j+depth_outer*8192+depth_last_2nd, rhs_m+(depth_outer*8192+depth_last_2nd)*96, dst_temp, depth1, depth2);
            dst_add(dst_acc, dst_temp);
            Scale_Shift(dst_acc, dst + width * j + 96 * i,
                        rhs_offset, dst_offset, scale, shift);
        }
    }

    if (width < 96) {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width) * sizeof(int8_t), width * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            dst_init(dst_acc);
            for (int k = 0; k < depth_outer; k++) {
                //loop6(lhs+depth*j+k*1024, rhs_m+k*1024*96, dst_temp, 255, 4);
                loop5(lhs + depth * j + k * 2048, rhs_m + k * 2048 * 96, dst_temp, 255, 8);
                //loop4(lhs+depth*j+k*4096, rhs_m+k*4096*96, dst_temp, 255, 16);
                //loop3(lhs+depth*j+k*8192, rhs_m+k*8192*96, dst_temp, 255, 32);

                dst_add(dst_acc, dst_temp);
            }

            //loop6(lhs+depth*j+depth_outer*1024, rhs_m+depth_outer*1024*96, dst_temp, depth3, depth4);
            loop5(lhs + depth * j + depth_outer * 2048, rhs_m + depth_outer * 2048 * 96, dst_temp, depth3, depth4);
            //loop4(lhs+depth*j+depth_outer*4096, rhs_m+depth_outer*4096*96, dst_temp, depth3, depth4);
            //loop3(lhs+depth*j+depth_outer*8192, rhs_m+depth_outer*8192*96, dst_temp, depth3, depth4);

            dst_add(dst_acc, dst_temp);
            //loop6(lhs+depth*j+depth_outer*1024+depth_last_2nd, rhs_m+(depth_outer*1024+depth_last_2nd)*96, dst_temp, depth1, depth2);
            loop5(lhs + depth * j + depth_outer * 2048 + depth_last_2nd, rhs_m + (depth_outer * 2048 + depth_last_2nd) * 96, dst_temp, depth1, depth2);
            //loop4(lhs+depth*j+depth_outer*4096+depth_last_2nd, rhs_m+(depth_outer*4096+depth_last_2nd)*96, dst_temp, depth1, depth2);
            //loop3(lhs+depth*j+depth_outer*8192+depth_last_2nd, rhs_m+(depth_outer*8192+depth_last_2nd)*96, dst_temp, depth1, depth2);

            dst_add(dst_acc, dst_temp);
            Scale_Shift(dst_acc, dst + width * j,
                        rhs_offset, dst_offset, scale, shift);
        }
    }
    else {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width + width - 96) * sizeof(int8_t), 96 * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            dst_init(dst_acc);
            for (int k = 0; k < depth_outer; k++) {
                //loop6(lhs+depth*j+k*1024, rhs_m+k*1024*96, dst_temp, 255, 4);
                loop5(lhs + depth * j + k * 2048, rhs_m + k * 2048 * 96, dst_temp, 255, 8);
                //loop4(lhs+depth*j+k*4096, rhs_m+k*4096*96, dst_temp, 255, 16);
                //loop3(lhs+depth*j+k*8192, rhs_m+k*8192*96, dst_temp, 255, 32);

                dst_add(dst_acc, dst_temp);
            }

            //loop6(lhs+depth*j+depth_outer*1024, rhs_m+depth_outer*1024*96, dst_temp, depth3, depth4);
            loop5(lhs + depth * j + depth_outer * 2048, rhs_m + depth_outer * 2048 * 96, dst_temp, depth3, depth4);
            //loop4(lhs+depth*j+depth_outer*4096, rhs_m+depth_outer*4096*96, dst_temp, depth3, depth4);
            //loop3(lhs+depth*j+depth_outer*8192, rhs_m+depth_outer*8192*96, dst_temp, depth3, depth4);

            dst_add(dst_acc, dst_temp);
            //loop6(lhs+depth*j+depth_outer*1024+depth_last_2nd, rhs_m+(depth_outer*1024+depth_last_2nd)*96, dst_temp, depth1, depth2);
            loop5(lhs + depth * j + depth_outer * 2048 + depth_last_2nd, rhs_m + (depth_outer * 2048 + depth_last_2nd) * 96, dst_temp, depth1, depth2);
            //loop4(lhs+depth*j+depth_outer*4096+depth_last_2nd, rhs_m+(depth_outer*4096+depth_last_2nd)*96, dst_temp, depth1, depth2);
            //loop3(lhs+depth*j+depth_outer*8192+depth_last_2nd, rhs_m+(depth_outer*8192+depth_last_2nd)*96, dst_temp, depth1, depth2);

            dst_add(dst_acc, dst_temp);
            Scale_Shift(dst_temp, dst + width * j + width - 96,
                        rhs_offset, dst_offset, scale, shift);
        }
    }


    delete (rhs_m);
    delete (dst_temp);
    delete (dst_acc);
}

void gemm_xor_avx_small(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                        int height, int depth, int width,
                        int32_t rhs_offset, int32_t dst_offset,
                        int32_t scale, int32_t shift) {

    int64_t depth1 = (int64_t)(depth - 1) / 8;
    int64_t depth2 = (int64_t)(depth - 1) % 8 + 1;

    int8_t* rhs_m = new int8_t[depth * 96];
    int32_t* dst_temp = new int32_t[96];
    for (int i = 0; i < (width - 1) / 96; i++) {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width + 96 * i) * sizeof(int8_t), 96 * sizeof(int8_t));

        }
        for (int j = 0; j < height; j++) {
            loop5(lhs + depth * j, rhs_m, dst_temp, depth1, depth2);

            Scale_Shift(dst_temp, dst + width * j + 96 * i,
                        rhs_offset, dst_offset, scale, shift);
        }
    }

    if (width < 96) {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width) * sizeof(int8_t), width * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            loop5(lhs + depth * j, rhs_m, dst_temp, depth1, depth2);
            Scale_Shift(dst_temp, dst + width * j,
                        rhs_offset, dst_offset, scale, shift);
        }
    }
    else {
        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 96 * sizeof(int8_t), rhs + (a * width + width - 96) * sizeof(int8_t), 96 * sizeof(int8_t));
        }
        for (int j = 0; j < height; j++) {
            loop5(lhs + depth * j, rhs_m, dst_temp, depth1, depth2);
            Scale_Shift(dst_temp, dst + width * j + width - 96,
                        rhs_offset, dst_offset, scale, shift);
        }
    }

    delete (rhs_m);
    delete (dst_temp);
}


void gemm_xor_avx(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                  int height, int depth, int width,
                  int32_t rhs_offset, int32_t dst_offset,
                  int32_t scale, int32_t shift) {

//    if(depth < 8193){
//    if(depth < 4097){
    if (depth < 2049) {
//    if(depth < 1025){
        gemm_xor_avx_small(lhs, rhs, dst, height, depth, width, rhs_offset, dst_offset, scale, shift);
    }
    else {
        gemm_xor_avx_big(lhs, rhs, dst, height, depth, width, rhs_offset, dst_offset, scale, shift);
    }

}


