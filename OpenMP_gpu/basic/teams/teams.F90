
program main
    !! TODO 1: add openmp support with use statement

    integer :: team_num(1024), num_teams(1024)

    !! TODO 2: execute the 2 assignment statements in a target teams region on device

      num_teams(omp_get_team_num()+1)=omp_get_num_teams()
      team_num( omp_get_team_num()+1)=omp_get_team_num()

                         !! target teams is synchronous
    do i = 1,num_teams(1)
    write(*,'(" team number ",i0.6,"  out of ",i0.6)') team_num(i), num_teams(i)
    end do
end program main

