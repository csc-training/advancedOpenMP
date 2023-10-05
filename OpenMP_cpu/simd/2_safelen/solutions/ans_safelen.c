#include <math.h>
#define N 10000
double ac[N][N], as[N][N];

void  transform(int j,int offset){
//  offset will always be  8 or greater
int i;

   #pragma omp simd safelen(8)
   for(i=0;i<N;i++){
      as[j][i] = as[j][i-offset] + (as[j][i]);
      ac[j][i] = ac[j][i+offset] + (ac[j][i]);
   }
}
