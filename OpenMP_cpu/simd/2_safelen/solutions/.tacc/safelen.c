#include <math.h>
#define N 10000
double ac[N][N], as[N][N];

void  transform(int j,int offset){
//  offset will always be 16 or greater
int i;

   #pragma omp simd safelen(16)
   for(i=0;i<N;i++){
      as[j][i] = as[j][i-offset] + sin(as[j][i]);
      ac[j][i] = ac[j][i+offset] + cos(ac[j][i]);
   }
}
