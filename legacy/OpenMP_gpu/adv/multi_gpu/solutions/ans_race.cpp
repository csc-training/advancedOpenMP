//#define N 1000  // evenly divisible by ndevices
  #define N 999  // evenly divisible by ndevices
#include <assert.h>
#include <stdio.h>
#include <omp.h>

int main(){
  int a=2;
  int start, end, blk_size;
  int x[N], y[N];

//int init_dev  = omp_get_initial_device();
  int     ndevs = omp_get_num_devices();
  printf("%d num of devices\n",ndevs);
  
//int ndevs=3;
  blk_size=N/ndevs;

  for(int i=0;i<N;++i){ x[i]=1; y[i]=1;}

  #pragma omp parallel for num_threads(ndevs)
  for (int idev=0; idev<ndevs; idev++)
  {
      start=blk_size*idev;  end=start+blk_size;
      printf("start=%d, end=%d\n",start,end);

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
