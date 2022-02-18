cmake_minimum_required(VERSION 3.5)
project(GEMMLOWP_XOR)


set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11 -pthread -Wno-unused-local-typedefs")

add_definitions(-DCMAKE_BUILD_TYPE=Release)


add_library(gemmlowp_xor_lib SHARED
        kernel/kernel.h
        kernel/baseline.cpp
        kernel/postprocess.cpp
        kernel/packing.cpp #added

        kernel/bit3/avx_b3_1x96.cpp
        kernel/bit4/avx_b4_1x96.cpp
        kernel/bit5/avx_b5_1x96.cpp
        kernel/bit6/avx_b6_1x96.cpp
        kernel/common_1x96.h
        kernel/common_1x128.h
        kernel/common_2x64.h
        kernel/common_4x32.h

        #kernel/bit4/avx_b4_1x96_new.cpp
        kernel/bit4/avx_b4_1x128.cpp
        kernel/bit4/avx_b4_4x32.cpp
        kernel/bit4/avx_b4_2x64.cpp
        )

add_executable(test_main_1x96 main.cpp)
target_link_libraries(test_main_1x96 gemmlowp_xor_lib)

add_executable(test_main_1x128 main_1x128.cpp)
target_link_libraries(test_main_1x128 gemmlowp_xor_lib)

add_executable(test_main_4x32 main_4x32.cpp)
target_link_libraries(test_main_4x32 gemmlowp_xor_lib)

add_executable(test_main_2x64 main_2x64.cpp)
target_link_libraries(test_main_2x64 gemmlowp_xor_lib)
