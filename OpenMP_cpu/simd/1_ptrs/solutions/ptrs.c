void add_floats(float *a, float *b, float *c, float *d, float *e, int n) {
//   With 5 pointers, compiler gives up on vectorization
//   Need to force the compiler to SIMDize it.
   int i;
    #pragma omp simd
    for (i=0; i<n; i++)
       a[i] = a[i] + b[i] + c[i] + d[i] + e[i];
}
