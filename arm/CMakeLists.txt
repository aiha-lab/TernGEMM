# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("myapplication")

# ------------------------------------------------------------------------------------------------ #

# SET FLAG

# ------------------------------------------------------------------------------------------------ #

add_library(gemm_xor_lib STATIC
        kernel/avx_4bit.cpp
        kernel/avx_1x128.cpp
        kernel/kernel.h
        kernel/baseline.cpp
        kernel/avx_2x64.cpp
        kernel/avx_4x32.cpp
        )

add_executable(test_main_4bit main.cpp)
target_link_libraries(test_main_4bit gemm_xor_lib)

add_executable(test_main_1x128 main_1x128.cpp)
target_link_libraries(test_main_1x128 gemm_xor_lib)

add_executable(test_main_2x64 main_2x64.cpp)
target_link_libraries(test_main_2x64 gemm_xor_lib)

add_executable(test_main_4x32 main_4x32.cpp)
target_link_libraries(test_main_4x32 gemm_xor_lib)
