#include <stdio.h>
#define N 16
void init(float *v1, float *v2, float *p, int n)
    { for(int i=0; i<n; i++){ v1[i]=2.0f; v2[i]=2.0f; p[i]=0.0f; } }
int maybe_change_v1(float *v1){ 
    if(_OPENMP > 201511) {v1[0]=1.0f; return 1;} 
    else{return 0;}
} 
//https://www.openmp.org/spec-html/5.0/openmpse10.html
   

int main(){
   float v1[N], v2[N], p[N];
   int changed;
   init(v1, v2, p, N); 

// TODO 1: Beginning of structured data region "to" for v's, from for p

   {   
      #pragma omp target
      #pragma omp parallel for 
      for (int i=0; i<N; i++) p[i] = v1[i] * v2[i];

      changed = maybe_change_v1(v1); 
      ///  TODO 1: update just v1[0] conditionally

      #pragma omp target
      #pragma omp parallel for 
      for (int i=0; i<N; i++)
        p[i] = p[i] + (v1[i] * v2[i]);
   }   

   printf("final loop used: v1[0]= %f, v1[1]= %f\n",v1[0],v1[2]);
   printf("p[0]= %f, p[1]= %f \n",p[0],p[1]);
   printf("_OPENMP= %d\n",_OPENMP);

}
