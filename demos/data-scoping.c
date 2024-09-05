int a=1;
void foo()
{    
    int b = 2, c = 3;
    #pragma omp parallel private(b)
    {
        int d=4;
        #pragma omp task
        {
            int e=5;
            // Scope of a:                  value of a:
            // Scope of b:                  value of b: 
            // Scope of c:                  value of c:
            // Scope of d:                  value of d: 
            // Scope of e:                  value of e: 
        }
    }
}