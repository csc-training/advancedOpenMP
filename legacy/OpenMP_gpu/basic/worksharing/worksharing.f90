  !! TODO 2: include  timer.f90 here
  ...

program main
  !! TODO 2: use mod_timer here
  use ...

  implicit none
  integer, parameter :: N=1024*1024*2**8
  real               :: x(N), y(N), a=2.0e0; 
  integer            :: i

  !! TODO 2: Instantiate timer object, Timer_collector, as timer.
  ...

  !! initialize x and y arrays on the host
  do i = 1,N;  x(i) = 1.0e0; y(i) = 1.0e0;  enddo

  !! TODO 2: Start timer here
  ...

  !! TODO 1: Offload with teams distribute parallel for
    !$omp  ...
    do i = 1,N;  y(i) = a*x(i) + y(i); enddo

  !! TODO 2: Stop timer here and report resuls
  ...
  ...

end program main
! if Intel compile error:
!ans_worksharing.f90:(.text+0x5f): relocation truncated to fit: R_X86_64_PC32 against `.bss'
! ifort -mcmodel=medium   *.f90
