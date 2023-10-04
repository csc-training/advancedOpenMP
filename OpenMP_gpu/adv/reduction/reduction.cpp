#include <stdio.h>
#include <omp.h>

float dotprod(float B[], float C[], int n)
{
   float sum = 0.0f;
   int i=9;
   int k=9;
// TODO 1a-c map B and C, make scalars tofrom by default
//           and include a reduction if necessary
  for (i=0; i<n; i++) sum += B[i] * C[i];
 
   k=omp_get_team_num();

   printf("i AF = %d, k= %d\n",i,k);
   return sum;
}

int main(){
   int  N=1<<20;
   float sum, B[N],C[N]; //init vv
   for(int i=0; i<N; i++){B[i]=1.0f; C[i]=1.0f;}

   sum=dotprod(B,C,N);

   printf("N= %d,  sum= %f\n", N,sum);
}

/* Note:  The variable sum is now mapped with tofrom from the defaultmap
          clause on the combined target teams construct, for correct
          execution with 4.5 (and pre-4.5) compliant compilers.
          See Devices Intro. 
 */
