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

void loop4_4x32(const int8_t* lhs0,
                const int8_t* lhs1,
                const int8_t* lhs2,
                const int8_t* lhs3,
                const int8_t* rhs,
                int32_t* dst,
                int depth1,
                int depth2) {
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
    "dup v28.4s, wzr\n"
    "dup v29.4s, wzr\n"
    "dup v30.4s, wzr\n"
    "dup v31.4s, wzr\n"



    "cmp %[depth1], #0\n"
    "beq 2f \n"

    "1: \n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"


    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"


    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v14.8h, v14.8h, v12.8b\n"
    "saddw2 v15.8h, v15.8h, v12.16b\n"
    "saddw v16.8h, v16.8h, v13.8b\n"
    "saddw2 v17.8h, v17.8h, v13.16b\n"
    "saddw v20.8h, v20.8h, v18.8b\n"
    "saddw2 v21.8h, v21.8h, v18.16b\n"
    "saddw v22.8h, v22.8h, v19.8b\n"
    "saddw2 v23.8h, v23.8h, v19.16b\n"
    "saddw v26.8h, v26.8h, v24.8b\n"
    "saddw2 v27.8h, v27.8h, v24.16b\n"
    "saddw v30.8h, v30.8h, v25.8b\n"
    "saddw2 v31.8h, v31.8h, v25.16b\n"

    "dup v6.4s, wzr\n"
    "dup v7.4s, wzr\n"
    "dup v12.4s, wzr\n"
    "dup v13.4s, wzr\n"
    "dup v18.4s, wzr\n"
    "dup v19.4s, wzr\n"
    "dup v24.4s, wzr\n"
    "dup v25.4s, wzr\n"

    "subs %[depth1], %[depth1], #1 \n"
    "bne 1b \n"


    "2:\n"

    "ld1 {v2.16b}, [%[rhs]], #16 \n"
    "ld1 {v3.16b}, [%[rhs]], #16 \n"

    "ld1r {v0.16b}, [%[lhs0]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v6.16b, v6.16b, v4.16b\n"
    "add v7.16b, v7.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs1]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v12.16b, v12.16b, v4.16b\n"
    "add v13.16b, v13.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs2]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v18.16b, v18.16b, v4.16b\n"
    "add v19.16b, v19.16b, v5.16b\n"

    "ld1r {v0.16b}, [%[lhs3]], #1 \n"
    "cmge v1.16b, v0.16b, #0\n"
    "cmeq v0.16b, v0.16b, #0\n"
    "not v0.16b, v0.16b \n"
    "eor v4.16b, v2.16b, v1.16b\n"
    "eor v5.16b, v3.16b, v1.16b\n"
    "sub v4.16b, v1.16b, v4.16b\n"
    "sub v5.16b, v1.16b, v5.16b\n"
    "and v4.16b, v4.16b, v0.16b\n"
    "and v5.16b, v5.16b, v0.16b\n"
    "add v24.16b, v24.16b, v4.16b\n"
    "add v25.16b, v25.16b, v5.16b\n"

    "subs %[depth2], %[depth2], #1 \n"
    "bne 2b \n"

    "saddw v8.8h, v8.8h, v6.8b\n"
    "saddw2 v9.8h, v9.8h, v6.16b\n"
    "saddw v10.8h, v10.8h, v7.8b\n"
    "saddw2 v11.8h, v11.8h, v7.16b\n"
    "saddw v14.8h, v14.8h, v12.8b\n"
    "saddw2 v15.8h, v15.8h, v12.16b\n"
    "saddw v16.8h, v16.8h, v13.8b\n"
    "saddw2 v17.8h, v17.8h, v13.16b\n"
    "saddw v20.8h, v20.8h, v18.8b\n"
    "saddw2 v21.8h, v21.8h, v18.16b\n"
    "saddw v22.8h, v22.8h, v19.8b\n"
    "saddw2 v23.8h, v23.8h, v19.16b\n"
    "saddw v26.8h, v26.8h, v24.8b\n"
    "saddw2 v27.8h, v27.8h, v24.16b\n"
    "saddw v30.8h, v30.8h, v25.8b\n"
    "saddw2 v31.8h, v31.8h, v25.16b\n"

    "sshll v0.4s, v8.4h, #0\n"
    "sshll2 v1.4s, v8.8h, #0\n"
    "sshll v2.4s, v9.4h, #0\n"
    "sshll2 v3.4s, v9.8h, #0\n"
    "sshll v4.4s, v10.4h, #0\n"
    "sshll2 v5.4s, v10.8h, #0\n"
    "sshll v6.4s, v11.4h, #0\n"
    "sshll2 v7.4s, v11.8h, #0\n"

    "sshll v8.4s, v14.4h, #0\n"
    "sshll2 v9.4s, v14.8h, #0\n"
    "sshll v10.4s, v15.4h, #0\n"
    "sshll2 v11.4s, v15.8h, #0\n"
    "sshll v12.4s, v16.4h, #0\n"
    "sshll2 v13.4s, v16.8h, #0\n"
    "sshll v14.4s, v17.4h, #0\n"
    "sshll2 v15.4s, v17.8h, #0\n"

    "sshll v16.4s, v20.4h, #0\n"
    "sshll2 v17.4s, v20.8h, #0\n"
    "sshll v18.4s, v21.4h, #0\n"
    "sshll2 v19.4s, v21.8h, #0\n"
    "sshll v20.4s, v22.4h, #0\n"
    "sshll2 v21.4s, v22.8h, #0\n"
    "sshll v22.4s, v23.4h, #0\n"
    "sshll2 v23.4s, v23.8h, #0\n"

    "sshll v24.4s, v26.4h, #0\n"
    "sshll2 v25.4s, v26.8h, #0\n"
    "sshll v26.4s, v27.4h, #0\n"
    "sshll2 v27.4s, v27.8h, #0\n"
    "sshll v28.4s, v30.4h, #0\n"
    "sshll2 v29.4s, v30.8h, #0\n"
    "sshll v30.4s, v31.4h, #0\n"
    "sshll2 v31.4s, v31.8h, #0\n"

    "mov x0, %[dst]\n"

    "st1 {v0.4s}, [x0], #16\n"
    "st1 {v1.4s}, [x0], #16\n"
    "st1 {v2.4s}, [x0], #16\n"
    "st1 {v3.4s}, [x0], #16\n"
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
    "st1 {v27.4s}, [x0], #16\n"
    "st1 {v28.4s}, [x0], #16\n"
    "st1 {v29.4s}, [x0], #16\n"
    "st1 {v30.4s}, [x0], #16\n"
    "st1 {v31.4s}, [x0]\n"
    :
    [lhs0] "+r"(lhs0),[lhs1] "+r"(lhs1),[lhs2] "+r"(lhs2),[lhs3] "+r"(lhs3), [rhs] "+r"(rhs), [dst] "+r"(dst)
    :
    [depth1] "r"(depth1), [depth2] "r"(depth2)
    :
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );

}

void
scale_shift_4x32(int32_t* dst, int8_t* result0, int8_t* result1, int8_t* result2, int8_t* result3,
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
    "ld1 {v15.4s}, [x0] \n"

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

    "xtn v16.8b, v0.8h \n"
    "xtn2 v16.16b, v2.8h \n"
    "xtn v17.8b, v4.8h \n"
    "xtn2 v17.16b, v6.8h \n"
    "xtn v18.8b, v8.8h \n"
    "xtn2 v18.16b, v10.8h \n"
    "xtn v19.8b, v12.8h \n"
    "xtn2 v19.16b, v14.8h \n"

    "mov x0, %[dst]\n"
    "add x0, x0, #256 \n"

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
    "ld1 {v15.4s}, [x0] \n"

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

    "xtn v20.8b, v0.8h \n"
    "xtn2 v20.16b, v2.8h \n"
    "xtn v21.8b, v4.8h \n"
    "xtn2 v21.16b, v6.8h \n"
    "xtn v22.8b, v8.8h \n"
    "xtn2 v22.16b, v10.8h \n"
    "xtn v23.8b, v12.8h \n"
    "xtn2 v23.16b, v14.8h \n"

    "mov x0, %[result0]\n"
    "st1 {v16.16b}, [x0], #16\n"
    "st1 {v17.16b}, [x0]\n"

    "mov x0, %[result1]\n"
    "st1 {v18.16b}, [x0], #16\n"
    "st1 {v19.16b}, [x0]\n"

    "mov x0, %[result2]\n"
    "st1 {v20.16b}, [x0], #16\n"
    "st1 {v21.16b}, [x0]\n"

    "mov x0, %[result3]\n"
    "st1 {v22.16b}, [x0], #16\n"
    "st1 {v23.16b}, [x0]\n"

    : // outputs
    [dst] "+r"(dst), [result0] "+r"(result0), [result1] "+r"(result1), [result2] "+r"(result2), [result3] "+r"(result3)
    : // inputs
    [rhs_offset] "r"(rhs_offset), [scale] "r"(scale), [shift] "r"(shift), [dst_offset] "r"(dst_offset)
    : // clobbers
    "cc", "memory", "x0", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7",
            "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17",
            "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27",
            "v28", "v29", "v30", "v31"
    );
}

void dst_init_4x32(int32_t* dst) {
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


void dst_add_4x32(int32_t* dst, int32_t* dst_temp) {
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
    "ld1 {v15.4s}, [x0] \n"

    "mov x0, %[dst]\n"
    "ld1 {v16.4s}, [x0], #16 \n"
    "ld1 {v17.4s}, [x0], #16 \n"
    "ld1 {v18.4s}, [x0], #16 \n"
    "ld1 {v19.4s}, [x0], #16 \n"
    "ld1 {v20.4s}, [x0], #16 \n"
    "ld1 {v21.4s}, [x0], #16 \n"
    "ld1 {v22.4s}, [x0], #16 \n"
    "ld1 {v23.4s}, [x0], #16 \n"
    "ld1 {v24.4s}, [x0], #16 \n"
    "ld1 {v25.4s}, [x0], #16 \n"
    "ld1 {v26.4s}, [x0], #16 \n"
    "ld1 {v27.4s}, [x0], #16 \n"
    "ld1 {v28.4s}, [x0], #16 \n"
    "ld1 {v29.4s}, [x0], #16 \n"
    "ld1 {v30.4s}, [x0], #16 \n"
    "ld1 {v31.4s}, [x0], #16 \n"

    "add v0.4s, v0.4s, v16.4s \n"
    "add v1.4s, v1.4s, v17.4s \n"
    "add v2.4s, v2.4s, v18.4s \n"
    "add v3.4s, v3.4s, v19.4s \n"
    "add v4.4s, v4.4s, v20.4s \n"
    "add v5.4s, v5.4s, v21.4s \n"
    "add v6.4s, v6.4s, v22.4s \n"
    "add v7.4s, v7.4s, v23.4s \n"
    "add v8.4s, v8.4s, v24.4s \n"
    "add v9.4s, v9.4s, v25.4s \n"
    "add v10.4s, v10.4s, v26.4s \n"
    "add v11.4s, v11.4s, v27.4s \n"
    "add v12.4s, v12.4s, v28.4s \n"
    "add v13.4s, v13.4s, v29.4s \n"
    "add v14.4s, v14.4s, v30.4s \n"
    "add v15.4s, v15.4s, v31.4s \n"

    "mov x0, %[dst] \n"
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
    "st1 {v15.16b}, [x0] \n"

    "mov x0, %[dst_temp]\n"
    "add x0, x0, #256 \n"

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
    "ld1 {v15.4s}, [x0] \n"

    "mov x0, %[dst]\n"
    "add x0, x0, #256 \n"
    "ld1 {v16.4s}, [x0], #16 \n"
    "ld1 {v17.4s}, [x0], #16 \n"
    "ld1 {v18.4s}, [x0], #16 \n"
    "ld1 {v19.4s}, [x0], #16 \n"
    "ld1 {v20.4s}, [x0], #16 \n"
    "ld1 {v21.4s}, [x0], #16 \n"
    "ld1 {v22.4s}, [x0], #16 \n"
    "ld1 {v23.4s}, [x0], #16 \n"
    "ld1 {v24.4s}, [x0], #16 \n"
    "ld1 {v25.4s}, [x0], #16 \n"
    "ld1 {v26.4s}, [x0], #16 \n"
    "ld1 {v27.4s}, [x0], #16 \n"
    "ld1 {v28.4s}, [x0], #16 \n"
    "ld1 {v29.4s}, [x0], #16 \n"
    "ld1 {v30.4s}, [x0], #16 \n"
    "ld1 {v31.4s}, [x0], #16 \n"
    "add v0.4s, v0.4s, v16.4s \n"
    "add v1.4s, v1.4s, v17.4s \n"
    "add v2.4s, v2.4s, v18.4s \n"
    "add v3.4s, v3.4s, v19.4s \n"
    "add v4.4s, v4.4s, v20.4s \n"
    "add v5.4s, v5.4s, v21.4s \n"
    "add v6.4s, v6.4s, v22.4s \n"
    "add v7.4s, v7.4s, v23.4s \n"
    "add v8.4s, v8.4s, v24.4s \n"
    "add v9.4s, v9.4s, v25.4s \n"
    "add v10.4s, v10.4s, v26.4s \n"
    "add v11.4s, v11.4s, v27.4s \n"
    "add v12.4s, v12.4s, v28.4s \n"
    "add v13.4s, v13.4s, v29.4s \n"
    "add v14.4s, v14.4s, v30.4s \n"
    "add v15.4s, v15.4s, v31.4s \n"

    "mov x0, %[dst]\n"
    "add x0, x0, #256 \n"
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
    "st1 {v15.16b}, [x0] \n"
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

    int32_t depth_outer = (depth - 1) / 256 - 1;
    int32_t depth_last_2nd = 256;
    int32_t depth_last = (depth - 1) % 256 + 1;

    if (depth_last < 96) {
        depth_last_2nd -= 95;
        depth_last += 95;
    }
    int64_t depth1 = (int64_t)(depth_last - 1) / 15;
    int64_t depth2 = (int64_t)(depth_last - 1) % 15 + 1;
    int64_t depth3 = (int64_t)(depth_last_2nd - 1) / 15;
    int64_t depth4 = (int64_t)(depth_last_2nd - 1) % 15 + 1;

    int8_t* rhs_m = new int8_t[depth * 96];
    int32_t* dst_temp = new int32_t[96];
    int32_t* dst_acc = new int32_t[height * 96];
    int j = 0;

    for (int i = 0; i < (width - 1) / 32; i++) {
        for (; j <= height - 4; j += 4) {
            dst_init_4x32(dst_acc + 128 * j);
        }
        if (j < height) {
            j = height - 4;
            dst_init_4x32(dst_acc + 128 * j);
        }
        j = 0;

        for (int k = 0; k < depth_outer; k++) {
            for (int a = 0; a < 1024; a++) {
                memcpy(rhs_m + a * 32, rhs + ((a + k * 1024) * width + 32 * i), 32 * sizeof(int8_t));
            }
            for (; j <= height - 4; j += 4) {
                loop4_4x32(lhs + depth * j + k * 1024,
                           lhs + depth * (j + 1) + k * 1024,
                           lhs + depth * (j + 2) + k * 1024,
                           lhs + depth * (j + 3) + k * 1024,
                           rhs_m,
                           dst_temp, 15, 16);
                dst_add_4x32(dst_acc + 128 * j, dst_temp);
            }
            if (j < height) {
                j = height - 4;

                loop4_4x32(lhs + depth * j + k * 1024,
                           lhs + depth * (j + 1) + k * 1024,
                           lhs + depth * (j + 2) + k * 1024,
                           lhs + depth * (j + 3) + k * 1024,
                           rhs_m,
                           dst_temp, 15, 16);
                dst_add_4x32(dst_acc + 128 * j, dst_temp);
            }
            j = 0;
        }

        for (int a = 0; a < depth_last_2nd; a++) {
            memcpy(rhs_m + a * 32, rhs + ((a + 256 * depth_outer) * width + 32 * i), 32 * sizeof(int8_t));
        }
        for (; j <= height - 4; j += 4) {
            loop4_4x32(lhs + depth * j + depth_outer * 1024,
                       lhs + depth * (j + 1) + depth_outer * 1024,
                       lhs + depth * (j + 2) + depth_outer * 1024,
                       lhs + depth * (j + 3) + depth_outer * 1024,
                       rhs_m,
                       dst_temp, depth3, depth4);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);

        }
        if (j < height) {
            j = height - 4;
            loop4_4x32(lhs + depth * j + depth_outer * 1024,
                       lhs + depth * (j + 1) + depth_outer * 1024,
                       lhs + depth * (j + 2) + depth_outer * 1024,
                       lhs + depth * (j + 3) + depth_outer * 1024,
                       rhs_m,
                       dst_temp, depth3, depth4);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);
        }
        j = 0;

        for (int a = 0; a < depth_last; a++) {
            memcpy(rhs_m + a * 32, rhs + ((a + 1024 * depth_outer + depth_last_2nd) * width + 32 * i), 32 * sizeof(int8_t));
        }
        for (; j <= height - 4; j += 4) {
            loop4_4x32(lhs + depth * j + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 1) + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 2) + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 3) + depth_outer * 1024 + depth_last_2nd,
                       rhs_m,
                       dst_temp, depth1, depth2);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j + 32 * i,
                             dst + width * (j + 1) + 32 * i,
                             dst + width * (j + 2) + 32 * i,
                             dst + width * (j + 3) + 32 * i,
                             rhs_offset, dst_offset, scale, shift);
        }
        if (j < height) {
            j = height - 4;
            loop4_4x32(lhs + depth * j + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 1) + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 2) + depth_outer * 1024 + depth_last_2nd,
                       lhs + depth * (j + 3) + depth_outer * 1024 + depth_last_2nd,
                       rhs_m,
                       dst_temp, depth1, depth2);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j + 32 * i,
                             dst + width * (j + 1) + 32 * i,
                             dst + width * (j + 2) + 32 * i,
                             dst + width * (j + 3) + 32 * i,
                             rhs_offset, dst_offset, scale, shift);
        }
        j = 0;
    }
    for (; j <= height - 4; j += 4) {
        dst_init_4x32(dst_acc + 128 * j);
    }
    if (j < height) {
        j = height - 4;
        dst_init_4x32(dst_acc + 128 * j);
    }
    j = 0;

    for (int k = 0; k < depth_outer; k++) {
        for (int a = 0; a < 1024; a++) {
            memcpy(rhs_m + a * 32, rhs + ((a + k * 1024) * width + width - 32), 32 * sizeof(int8_t));
        }
        for (; j <= height - 4; j += 4) {
            loop4_4x32(lhs + depth * j + k * 1024,
                       lhs + depth * (j + 1) + k * 1024,
                       lhs + depth * (j + 2) + k * 1024,
                       lhs + depth * (j + 3) + k * 1024,
                       rhs_m,
                       dst_temp, 15, 16);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);
        }
        if (j < height) {
            j = height - 4;

            loop4_4x32(lhs + depth * j + k * 1024,
                       lhs + depth * (j + 1) + k * 1024,
                       lhs + depth * (j + 2) + k * 1024,
                       lhs + depth * (j + 3) + k * 1024,
                       rhs_m,
                       dst_temp, 15, 16);
            dst_add_4x32(dst_acc + 128 * j, dst_temp);
        }
        j = 0;
    }

    for (int a = 0; a < depth_last_2nd; a++) {
        memcpy(rhs_m + a * 32, rhs + ((a + 1024 * depth_outer) * width + width - 32), 32 * sizeof(int8_t));
    }
    for (; j <= height - 4; j += 4) {
        loop4_4x32(lhs + depth * j + depth_outer * 1024,
                   lhs + depth * (j + 1) + depth_outer * 1024,
                   lhs + depth * (j + 2) + depth_outer * 1024,
                   lhs + depth * (j + 3) + depth_outer * 1024,
                   rhs_m,
                   dst_temp, depth3, depth4);
        dst_add_4x32(dst_acc + 128 * j, dst_temp);

    }
    if (j < height) {
        j = height - 4;
        loop4_4x32(lhs + depth * j + depth_outer * 1024,
                   lhs + depth * (j + 1) + depth_outer * 1024,
                   lhs + depth * (j + 2) + depth_outer * 1024,
                   lhs + depth * (j + 3) + depth_outer * 1024,
                   rhs_m,
                   dst_temp, depth3, depth4);
        dst_add_4x32(dst_acc + 128 * j, dst_temp);
    }
    j = 0;
    for (int a = 0; a < depth_last; a++) {
        memcpy(rhs_m + a * 32, rhs + ((a + 1024 * depth_outer + depth_last_2nd) * width + width - 32), 32 * sizeof(int8_t));
    }
    for (; j <= height - 4; j += 4) {
        loop4_4x32(lhs + depth * j + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 1) + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 2) + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 3) + depth_outer * 1024 + depth_last_2nd,
                   rhs_m,
                   dst_temp, depth1, depth2);
        dst_add_4x32(dst_acc + 128 * j, dst_temp);
        if (width >= 32) {
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j + width - 32,
                             dst + width * (j + 1) + width - 32,
                             dst + width * (j + 2) + width - 32,
                             dst + width * (j + 3) + width - 32,
                             rhs_offset, dst_offset, scale, shift);
        }
        else {
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j,
                             dst + width * (j + 1),
                             dst + width * (j + 2),
                             dst + width * (j + 3),
                             rhs_offset, dst_offset, scale, shift);
        }
    }
    if (j < height) {
        j = height - 4;
        loop4_4x32(lhs + depth * j + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 1) + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 2) + depth_outer * 1024 + depth_last_2nd,
                   lhs + depth * (j + 3) + depth_outer * 1024 + depth_last_2nd,
                   rhs_m,
                   dst_temp, depth1, depth2);
        dst_add_4x32(dst_acc + 128 * j, dst_temp);
        if (width >= 32) {
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j + width - 32,
                             dst + width * (j + 1) + width - 32,
                             dst + width * (j + 2) + width - 32,
                             dst + width * (j + 3) + width - 32,
                             rhs_offset, dst_offset, scale, shift);
        }
        else {
            scale_shift_4x32(dst_acc + 128 * j, dst + width * j,
                             dst + width * (j + 1),
                             dst + width * (j + 2),
                             dst + width * (j + 3),
                             rhs_offset, dst_offset, scale, shift);
        }
    }


    delete[] rhs_m;
    delete[] dst_temp;
    delete[] dst_acc;
}

void gemm_xor_avx_small(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                        int height, int depth, int width,
                        int32_t rhs_offset, int32_t dst_offset,
                        int32_t scale, int32_t shift) {

    int64_t depth1 = (int64_t)(depth - 1) / 15;
    int64_t depth2 = (int64_t)(depth - 1) % 15 + 1;

    int8_t* rhs_m = new int8_t[depth * 96];
    int32_t* dst_temp = new int32_t[96];

    for (int i = 0; i < (width - 1) / 32; i++) {

        for (int a = 0; a < depth; a++) {
            memcpy(rhs_m + a * 32, rhs + (a * width + 32 * i), 32 * sizeof(int8_t));
        }
        int j = 0;
        for (; j <= height - 4; j += 4) {
            loop4_4x32(lhs + depth * j,
                       lhs + depth * (j + 1),
                       lhs + depth * (j + 2),
                       lhs + depth * (j + 3),
                       rhs_m,
                       dst_temp, depth1, depth2);

            scale_shift_4x32(dst_temp,
                             dst + width * j + 32 * i,
                             dst + width * (j + 1) + 32 * i,
                             dst + width * (j + 2) + 32 * i,
                             dst + width * (j + 3) + 32 * i,
                             rhs_offset, dst_offset, scale, shift);
        }
        if (j < height) {
            j = height - 4;
            loop4_4x32(lhs + depth * j,
                       lhs + depth * (j + 1),
                       lhs + depth * (j + 2),
                       lhs + depth * (j + 3),
                       rhs_m,
                       dst_temp, depth1, depth2);

            scale_shift_4x32(dst_temp,
                             dst + width * j + 32 * i,
                             dst + width * (j + 1) + 32 * i,
                             dst + width * (j + 2) + 32 * i,
                             dst + width * (j + 3) + 32 * i,
                             rhs_offset, dst_offset, scale, shift);
        }
    }
    for (int a = 0; a < depth; a++) {
        memcpy(rhs_m + a * 32, rhs + (a * width + width - 32), 32 * sizeof(int8_t));
    }
    int j = 0;
    for (; j <= height - 4; j += 4) {
        loop4_4x32(lhs + depth * j,
                   lhs + depth * (j + 1),
                   lhs + depth * (j + 2),
                   lhs + depth * (j + 3),
                   rhs_m,
                   dst_temp, depth1, depth2);

        if (width >= 32) {
            scale_shift_4x32(dst_temp,
                             dst + width * j + width - 32,
                             dst + width * (j + 1) + width - 32,
                             dst + width * (j + 2) + width - 32,
                             dst + width * (j + 3) + width - 32,
                             rhs_offset, dst_offset, scale, shift);
        }
        else {
            scale_shift_4x32(dst_temp,
                             dst + width * j,
                             dst + width * (j + 1),
                             dst + width * (j + 2),
                             dst + width * (j + 3),
                             rhs_offset, dst_offset, scale, shift);
        }
    }
    if (j < height) {
        j = height - 4;
        loop4_4x32(lhs + depth * j,
                   lhs + depth * (j + 1),
                   lhs + depth * (j + 2),
                   lhs + depth * (j + 3),
                   rhs_m,
                   dst_temp, depth1, depth2);

        if (width >= 32) {
            scale_shift_4x32(dst_temp,
                             dst + width * j + width - 32,
                             dst + width * (j + 1) + width - 32,
                             dst + width * (j + 2) + width - 32,
                             dst + width * (j + 3) + width - 32,
                             rhs_offset, dst_offset, scale, shift);
        }
        else {
            scale_shift_4x32(dst_temp,
                             dst + width * j,
                             dst + width * (j + 1),
                             dst + width * (j + 2),
                             dst + width * (j + 3),
                             rhs_offset, dst_offset, scale, shift);
        }
    }

    delete[] rhs_m;
    delete[] dst_temp;
}


void gemm_xor_avx_4x32(const int8_t* lhs, const int8_t* rhs, int8_t* dst,
                       int height, int depth, int width,
                       int32_t rhs_offset, int32_t dst_offset,
                       int32_t scale, int32_t shift) {

    gemm_xor_avx_small(lhs, rhs, dst, height, depth, width, rhs_offset, dst_offset, scale, shift);


}


