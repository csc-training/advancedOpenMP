# Advanced OpenMP - tasks and GPU offloading

Material for the CSC course "Advanced OpenMP - tasks and GPU offloading".
The most recent version of the course is found in the `main` branch, previous versions can be found in Releases/Tags.

Learning outcome
- Awareness of task based parallelism
- Ability to implement task parallel algorithms with OpenMP
- Ability to utilize GPUs efficiently with OpenMP offloading

Prerequisites
- Good knowledge of C/C++ or Fortran
- Basic knowledge of OpenMP for CPUs


# GPU programming I-III: exercises

## Intro to GPUs in HPC
- [Device query](intro/)

## Basics of OpenMP offloading

- [Hello world](hello-world/)
- [Vector addition](vector-sum/)
- [Simple offloading for Laplace equation](jacobi/)

## Controlling data movement

- [Dot product](dot-product/)
- [Sum and dot product](sum-dot/)
- [Offloading the heat equation](heat-equation/README-simple.md)

## Unstructured data 

- [Unstructured data in heat equation](heat-equation/README-unstructured.md)

## Device functions

- [Device functions](gpu-functions/)

## Interoperability with libraries

- [Using HIP library](device-ptr)

## Asynchronous operations

- [Asynchronous operations](async-operations)

## Using multiple GPUs

- [Multi-GPU parallelization for heat equation](heat-equation/README-multigpu.md)
