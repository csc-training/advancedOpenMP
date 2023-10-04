#include <stdio.h>
int main(){

 int cntr=100;
 printf(" The sequence of values printed should be, 1 - 100.\n");
 printf(" Execute:  ./a.out | sort for checking.\n");


 #pragma omp parallel
 #pragma omp single

  while(cntr>0){

    #pragma omp task firstprivate(cntr)   // what clauses go here for cntr?
    {
       printf(" %0.4d \n",cntr);  
    }
  
    cntr--;
  
  }

}

