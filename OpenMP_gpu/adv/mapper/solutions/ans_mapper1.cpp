#include  <stdlib.h>
#include   <stdio.h>
#define N 100

typedef struct myvec{
    size_t len;
    double *data;
} myvec_t;

// TODO 1: create mapper for myvec_t type structure
//         with map for v and data array section
//         which starts at 0 and is of length v.len.
#pragma omp declare mapper(myvec_t v) \
                    map(v, v.data[0:v.len])
void init(myvec_t *s);

int main(){
   myvec_t s;

   s.data = (double *)calloc(N,sizeof(double));
   s.len  = N;

   #pragma omp target
   init(&s);

   printf("s.data[%d]=%lf\n",N-1,s.data[N-1]);  //s.data[99]=99.000000
}

void init(myvec_t *s)
{ for(size_t i=0; i<s->len; i++) s->data[i]=i; }
