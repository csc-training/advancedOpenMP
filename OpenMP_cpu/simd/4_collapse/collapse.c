#define M 4096
#define N    3
double a[M][N], b[M][N], c[M][N];

void element_mXm(){

// The two loops can be collapsed
 //#pragma omp 
   for (int j=0; j<M; j++) {
      for (int i=0; i<N; i++) {
      c[j][i] = c[j][i] + a[j][i] * b[j][i];
      }
   }
}
