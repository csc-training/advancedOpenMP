#include <stdio.h>

int main(){
   int x;


 #pragma omp parallel
 {
   x = 1;
   #pragma omp barrier
   #pragma omp single
   {
      #pragma omp task shared(x) depend(out: x)
         x = 2;
      #pragma omp task shared(x) depend( in: x)
         printf("a RaW x(2) = %d\n", x);
   }

   x = 1;   
   #pragma omp barrier
   #pragma omp single
   {
      #pragma omp task shared(x) depend( in: x)
         x = 2;
      #pragma omp task shared(x) depend(out: x)
         printf("b WaR x(2) = %d\n", x);
   }


   x = 1;
   #pragma omp barrier
   #pragma omp single
   {
      #pragma omp task shared(x) depend(out: x)
         x = 2;
      #pragma omp task shared(x) depend(out: x)
         printf("c WaW x(2) = %d\n", x);
   }

   x = 1;
   #pragma omp barrier
   #pragma omp single
   {
      #pragma omp task shared(x) depend( in: x)
         x = 2;
      #pragma omp task shared(x) depend( in: x)
         printf("d RaR x(1|2) = %d\n", x);
   }


 } // end parallel

}

