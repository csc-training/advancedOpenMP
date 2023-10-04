#include <stdio.h>
#define N 100
void foo(int i, int *a, int n, int *sum);

int main(){

int  i,a[N], id=0 ;
int  sum = 0;

   for(i=0;i<N;i++)
      a[ i] = i+1;
      a[49] = 0;

#pragma omp parallel
#pragma omp single

   for(i=0;i<N;i++){
     if(a[i] != 0){

       #pragma omp task depend(in:id) firstprivate(i)
       foo(i, a,N, &sum);

     }else{

       #pragma omp task depend(out:id) firstprivate(i)
       foo(i, a,N, &sum);

     }
   }
                                              // since i is auto private
                                              // it becomes auto firstprivate for task
                                              // Hence firstprivate(i) is not necessary
                                              // but it is good practice to specify it as such
}

void foo(int i, int *a, int n, int *sum){

   #pragma omp critical
   {
     *sum = *sum + a[i];
   }
   if(a[i] == 0)
     printf(" Partial Sum at zero point, index=%d sum=%d\n", i,*sum);
}
