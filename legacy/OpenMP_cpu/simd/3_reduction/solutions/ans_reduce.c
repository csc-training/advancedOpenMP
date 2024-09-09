#include <omp.h>
double fun(double a);

double red_sum(int n,double *a){
  int i;
  double red_sum=0.0e0;

// Reduction here causes a dependence
// But SIMD units can now handle reductions!
  #pragma omp simd reduction(+:red_sum)
  for(i=0;i<n;i++){
     red_sum = red_sum + fun(a[i]);
  }
  return red_sum;
}

//https://software.intel.com/en-us/articles/openmp-40-new-features-supported-in-intel-compiler-160
