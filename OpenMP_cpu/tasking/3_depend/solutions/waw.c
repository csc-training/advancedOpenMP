   #include <stdio.h>

int main(){
int x;

 x = 1;

 #pragma omp parallel
 {
   #pragma omp single
   {
      #pragma omp task shared(x) depend(out: x)
         x = 2;
      #pragma omp task shared(x) depend(out: x)
         printf("WaW      dependence x = %d\n", x);
   }

 } // end parallel

}
