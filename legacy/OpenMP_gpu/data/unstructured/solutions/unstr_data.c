 
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int N;
  double *data;
} Vec;

void init_data(Vec *A, int n)
{
  A->N = n;
  A->data = (double *)malloc(n*sizeof(double));
  // TODO 1:  insert a a target enter data construct here
  #pragma omp target enter data map(alloc:A, A->data[0:n]   )
  #pragma omp target update to (A->N)
}

void free_data(Vec *A)
{
  // TODO 2:  insert a a target exit data construct here
  #pragma omp target exit data  map(delete:A->data[0:A->N])
  A->N = 0;
  free(A->data);
  A->data = NULL;
}

int main(){
  Vec A;
  int npts=16;
 
  init_data(&A,npts);
 
  // TODO 3:  offload with a target construct (no clauses)
  #pragma omp target
 
  for(int i=0; i<A.N; i++){
    A.data[i]=1.0f; 
   }
 
  // TODO 4:  use an update construct to get back from device
  #pragma omp target update from(A.data[0:A.N])



  for (int i=0; i<A.N; ++i) 
  printf("A.data[%d] = %f\n",i,A.data[i]);
 
  free_data(&A);
 
}
