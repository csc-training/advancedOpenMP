#include <stdio.h>
// TODO 1:  Add openmp header


int main()
{ 
    // TODO 2: execute the print statement in target teams region on device

    { printf(" team=%0.5d of %0.5d \n", omp_get_team_num(),omp_get_num_teams()); }

    return 0;
}

