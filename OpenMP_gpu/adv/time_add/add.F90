include "timer.f90"

subroutine add(n, x, y)
  implicit none
  integer :: n,i
  real    :: x(n),y(n)

    !! TODO 2b:
!F1 !$omp target teams distribute parallel for num_teams(108) num_threads(256) !!1 .4s
!F2 !$omp        teams distribute parallel for num_teams(108) num_threads(256) !!2 mins
!F3 !$omp              distribute parallel for                num_threads(256) !!2 .1s
    !$omp              distribute parallel for !!             num_threads(256) !!2 .1s
    do i=1,n;  y(i)=x(i)+y(i);  enddo

end subroutine 

program main
  use mod_Timer
  implicit none

  type(Timer_Collector) timer

 !integer,parameter :: N=2**28 !! use 28 for timing, 1024*1024*2**8
  integer,parameter :: N=2**25 !! use 25 for code validation,  1024*1024*2**5
  real    :: x(N), y(N), error
  integer :: i


  do i=1,n;  x(i)=1.0e0; y(i)=1.0e0; enddo  !init x and y on host

  call timer%start(" Data TO   & Alloc  "); !! TODO 1
    !$omp target data map(tofrom:y) map(to:x) !allocate and move data
  call timer%stop();                        !! TODO 1
 
  call timer%start(" Add on GPU         "); !! TODO 1

    !! TODO 3:
    !!    Time Loop on Host
    !!#pragma omp target teams distribute parallel for num_teams(108) num_threads(256)
    !!do i=1,n;  y(i)=x(i)+y(i);  enddo

    !! TODO 2a:
    !!    Time function call with "target" "target teams and num_teams/thread_limit clauses
    !F1 -- no construct here                      !!1 .4s
    !F2 #pragma !$omp target                      !!3  mins
    !F3 #pragma !$omp target teams num_teams(108) !!2 .1s
    !F4 #pragma !$omp target teams thread_limit(256) !! num_teams(108) !!2 .008s
    !$omp target teams thread_limit(512) !! num_teams(108) !!2 
    call add(N,x,y);

  call timer%stop();                        !! TODO 1

  call timer%start(" Data FROM & Dealloc"); !! TODO 1
    !$omp end target data 
  call timer%stop();                        !! TODO 1

  do i=1,N
     error = max( 0.0e0, abs(y(i)-2.0e0))
     if ( error > 0.0000001 ) &
        print*, " error e10-6 exceeded at ",i," val= ",error
  end do
  print*, "Max error = ", error, " for count of ", N

  call timer%print();                       !! TODO 1

end program main
