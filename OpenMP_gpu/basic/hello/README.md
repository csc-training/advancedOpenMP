# Hello world with OpenMP offloading



Compile and run the simple OpenMP `hello(.c|.F90)` with/without offloading.

1.) Look over the code.
    What is the purpose of omp_is_init_device()?
    What is the purpose of omp_is_init_device()?

2.) Compile the code, as is, without any openmp support.
    (LUMI: CC hello.cpp  |  ftn hello.F90)
    What is the problem?
    Hint:  openmp functions have no support without turning on compiler support
           Comp. support and header|use (C/C++|F90) files are required.

3.) Correct so that openmp functions are supported.
    Compile code with JUST openmp support and run.
    (LUMI: CC -fopenmp hello.cpp  |  ftn -fopenmp hello.F90)

    How many devices did it find.
    On LUMI compiler option -fopenmp-target options were inserted,
            so it sees a GPU.
            Use CC -fopenmp -cray-verbose hello.cpp 
                            ^^^^^^^^^^^^^
            to see the real compilation command.
    Otherwise, without the offload target options, the omp_get_num_devices
               will report 0.

    Did it run on the host or a device? NO, because we have no target constructs.

4.) Now let's instrument it to run on the device, 
    Execute the code block below the TODO2: comment on the GPU
    with an appropriate target construct without any clauses.
    and compile with

    Compile and run.
          
    Did the TODO2: block run on the device (GPU)?

5.) Now turn off offloading with the OMP_TARGET_OFFLOAD variable,
    and show that it works:

       export OMP_TARGET_OFFLOAD=disabled
       ./a.out

    Where did it run? 
    FYI:  You can also require aborting, to avoid target 
          fallback executions on the host (for whatever reason)
          by setting OMP_TARGET_OFFLOAD=mandatory.

```
#!/bin/bash
#SBATCH --job-name=hello
#SBATCH --account=project_#######
#SBATCH --partition=test
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

srun hello
```
