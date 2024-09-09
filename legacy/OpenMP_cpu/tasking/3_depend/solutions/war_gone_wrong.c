   #include <stdio.h>
   #include <stdlib.h>

int main(){
int x;

 x = 1;

 #pragma omp parallel
 {
   #pragma omp single
   {
      #pragma omp task shared(x) depend(in: x)
      {
         system("sleep 2");
         x = 2;
      }
      #pragma omp task shared(x) depend(in: x)
         printf("WaR anti-dependence x = %d\n", x);
   }

 } // end parallel

}
