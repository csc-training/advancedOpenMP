# Hello world with OpenMP offloading



Offload and create teams for statements a code block that
captures (and reports) the number of teams and the team number 
with/without specifying the number of teams. Code is teams(.cpp|.F90)

1.) Look over the code.
    Does the initial thread of the program run as a team?
    Try compiling code, as is, with the -fopenmp and run it.
    What are the number of teams for the initial thread.?
    You can also create a league of teams on the CPU
    (#pragma omp teams | !$omp teams), but we are not
    interested in that here.
    

2.) Offload and creates teams for  the statement that p 
    print (CPP version) or capture (F90) the number of
    teams and team numbers.  

    (**Fortan print on devices is limited, that is why the
    information is captures, and printed from the host)

    Hints   use the combined target teams construct,
            and don't forget to provide header (CPP)
            and use statements.

    How many teams are created by default for CPP code,
    and F90?

    It is 28160 for cpp, and 220.
    These are implementation and compiler dependent.
    (For "nonsense" things, CCP creates a lot of 
     teams, while the Fortran is conservative, more
     in line with the number of CUs, 104 .)

3.) Now, add a num_teams clause and specify 104 teams.
    Compile and run to check your clause insertion.

         ./a.out | sort 
          

```
#!/bin/bash
#SBATCH --job-name=teams
#SBATCH --account=project_#######
#SBATCH --partition=test
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

srun ./a.out
```
