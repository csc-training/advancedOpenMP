 
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
}

void free_data(Vec *A)
{
  // TODO 2:  insert a a target exit data construct here
  A->N = 0;
  free(A->data);
  A->data = NULL;
}

int main(){
  Vec A;
  int npts=16;
 
  init_data(&A,npts);
 
  // TODO 3:  offload with a target construct (no clauses)
 
  for(int i=0; i<A.N; i++){
    A.data[i]=1.0f; 
   }
 
  // TODO 4:  use an update construct to get back from device
 
  printf("A.data[0] = %f\n",A.data[0]);
 
  free_data(&A);
 
}
