#include <stdio.h>
// TODO 1: Add appropriate header for function prototypes
#include <omp.h>

int main() 
{

  int num_devices = omp_get_num_devices();
  printf("Number of available (GPU) devices %d\n", num_devices);

// TODO 2: execute this block on a device
  #pragma omp target
  {
    if (omp_is_initial_device()) {
      printf("Running on host\n");    
    } else {
      printf("Running on device\n");
    }
  }

}
