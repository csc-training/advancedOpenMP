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
            // Scope of a: 
            // Scope of b: 
            // Scope of c: 
            // Scope of d: 
            // Scope of e: 
        }
    }
}