   #include <stdio.h>

int main(){
int x;

 x = 1;

 #pragma omp parallel
 {
   #pragma omp single
   {
      #pragma omp task shared(x) depend(<???>: x)
         x = 2;
      #pragma omp task shared(x) depend(<???>: x)
         printf("WaW      dependence x = %d\n", x);
   }

 } // end parallel

}
