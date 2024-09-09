#include <stdio.h>
#define N 100
void foo(int i, int *a, int n, int *sum);

int main(){

int  i,a[N], id=0 ;
int  sum = 0;
//int id=0;  // dependence var

   for(i=0;i<N;i++)
      a[ i] = i+1;
      a[49] = 0;

#pragma omp parallel
#pragma omp single

   for(i=0;i<N;i++){
     if(a[i] != 0){

                               // use id, defined above as the "dependence" variable
                               // What dependence type? Hint: You want these tasks to
                               // compute simultaneous.
                               // Does "i" need to be put in a firstprivate clause?
                               // depend(<???>:id) firstprivate(<other_var?>)
       #pragma omp task        // fill in dependence and data sharing
       foo(i, a,N, &sum);

     }else{

                               // use id, defined above as the "dependence" variable
                               // What dependence type? You want all previous tasks
                               // to finish. Hint:  Will a "write dependence" do this?
                               // Does "i" need to be put in a firstprivate clause?
                               // depend(<???>:id) firstprivate(<other_var?>)
       #pragma omp task        // fill in dependence and data sharing
       foo(i, a,N, &sum);

     }
   }

}

void foo(int i, int *a, int n, int *sum){

   #pragma omp critical
   {
     *sum = *sum + a[i];
   }
   if(a[i] == 0)
     printf(" Partial Sum at zero point %d\n", *sum);
}
