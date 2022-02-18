# TernGEMM: Fast GEMM with Ternary weights

This repository contains a code for the paper:

**TernGEMM: GEneral Matrix Multiply Library with Ternary Weights for Fast DNN Inference**

Seokhyeon Choi, Kyuhong Shim, Jungwook Choi, Wonyong Sung, Byonghyo Shim

* IEEE Workshop on Signal Processing Systems (SiPS) 2021: https://ieeexplore.ieee.org/document/9605039


## Summary

Many CPUs for personal computers and embedded systems equip SIMD instructions, 
which can be utilized to implement an efficient GEMM that is very necessary for efficient DNN inference.
While many deep neural networks show quite good performance even at 1-bit or 2-bit precision, 
the current CPU instruction and library do not efficiently support arithmetic operations below 8-bit.
We propose **TernGEMM**, a special GEMM library using SIMD instructions for Deep Neural Network (DNN) inference with 
**ternary weights** and **activations under 8-bit**.



## Key Idea and Implementations

1. We propose TernMAC, which efficiently utilize the fact that multiplication with {-1, 0, 1} does not change the bit precision. As a result, expensive MUL instructions are no more necessary. 
2. We implement TernGEMM for ARM and Intel CPUs with carefully polished kernels written in assembly.
3. we build multiple version of kernels that make use of registers differently by changing the block size (=tiling size) of the microkernel. Specifically, we support 4 types of kernels:
   1. 1x96
   2. 1x128
   3. 2x64
   4. 4x32
4. The repository contains both kernel and test code for the evaluation purpose.



## Performance

The number of instructions for GEMMLowp (which is one of the most famous 8-bit GEMM library)[1], 
is 25% higher than TernGEMM. Furthermore, the IPC of TernaryGEMM (= 2.91) is 35% larger than
that of GEMMLowp (= 2.16). 
The larger IPC implies that TernaryGEMM demonstrates better pipeline efficiency than GEMMLowp. 
Together, the TernGEMM kernel exhibits ×1.68 speed-up over GEMMLowp.

we also conduct the performance evaluation of various DNNs on Intel and ARM platforms. 
When compared to GEMMLowp, TernGEMM’s average speed is 2.052 times faster in ResNet50, 2.973 times faster in MobileNet-V2, and 2.986 times faster in EfficientNet-B0.
We further demonstrate that the proposed ternary MAC operation allows flexibility of tile size, which
results in an additional increase in performance of up to 18.96%.


[1] GEMMLowp: A Small Self-contained Low-precision GEMM Library https://github.com/google/gemmlowp




## How to Build and Evaluate

Each folder contains platform-specific kernels and build requirements.

To build the test code, please build executables as below.

```
mkdir build
cd build
cmake ..
./test_main_MxN HEIGHT DEPTH WIDTH BIT
```

After the build, there will be four executables that indicates the four type of tiling operations.
Executables take four integer arguments (HEIGHT, DEPTH, WIDTH, BIT).
* Matrix multiplication shape is AxB = (HEIGHT, DEPTH) x (DEPTH, WIDTH).
* BIT determines the bit precision of B.
* A is fixed to ternary.
* For the speed evaluation, main files will generate dummy data, run the code for 1,000 times, average the execution latency and print the result. 
