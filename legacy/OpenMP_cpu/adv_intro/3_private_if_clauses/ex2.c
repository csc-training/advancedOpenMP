#include "omp.h"
#include <stdio.h>
#define N 25000
int main(){

   int   i;
   double sum = 0.0e0;

   #pragma omp parallel for reduction(+:sum)
   for(i=1; i<=N; i++)
     sum = sum + (double)i;

   printf("sum= %f\n",sum);

}

