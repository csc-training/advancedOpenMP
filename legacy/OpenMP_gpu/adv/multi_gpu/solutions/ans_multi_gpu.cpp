//#define N 1000  // evenly divisible by ndevices
  #define N 999  // evenly divisible by ndevices
#include <assert.h>
#include <stdio.h>
#include <omp.h>

int main(){
  int a=2;
  int start, end, blk_size;
  int x[N], y[N];

//TODO 1: Get the number of devices on the node
//    ndevs = omp_get_num_devices();
  int     ndevs = omp_get_num_devices();
  printf("%d num of devices\n",ndevs);
  
  blk_size=N/ndevs;

  for(int i=0;i<N;++i){ x[i]=1; y[i]=1;}

!!TODO 2:Create a parallel region with the number thread
!!       equal to the number of devices.
  #pragma omp parallel for num_threads(ndevs) private(start,end)
  for (int idev=0; idev<ndevs; idev++)
  {
      start=blk_size*idev;  end=start+blk_size;
      printf("start=%d, end=%d\n",start,end);

      // Each device will calculated a partition of the arrays.
      // Device 0 calculates the first block, dev 1 the second, etc.
      // TODO 3: For each device_id (idev) map only the portion
      //         of x and y needed on the device.

      #pragma omp target device(idev) map(tofrom: x[start:blk_size]) \
                                      map(to:     y[start:blk_size])
      {
      for( int i=start; i<end; i++){ x[i] = x[i] + a*y[i]; }
      printf("start %d  end %d idev %d\n",start,end,idev);
      }
  }
  for(int i=0; i<N; i++) printf(" %4d  %4d\n",i,x[i]);

  for(int i=0; i<N; i++) assert(x[i]==3);//Validate
}
