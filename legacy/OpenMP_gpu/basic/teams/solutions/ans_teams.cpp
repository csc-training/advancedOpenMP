#include <stdio.h>
// TODO 1:  Add openmp header
#include <omp.h>

int main()
{ 
    // TODO 2: execute the print statement in target teams region on device
    #pragma omp target teams num_teams(104)
    { printf(" team=%0.5d of %0.5d \n", omp_get_team_num(),omp_get_num_teams()); }

    return 0;
}

