  !! TODO 2: include  timer.f90 here
include "timer.f90"

program main
  !! TODO 2: use mod_timer here
  use mod_timer
  implicit none
  integer, parameter :: N=1024*1024*2**8   !2**28
 !integer, parameter :: N=1024*1024*2**10  !2**30
  real               :: x(N), y(N), a=2.0e0; 
  integer            :: i

  !! TODO 2: Instantiate timer object, Timer_collector, as timer.
  type(Timer_Collector) timer

  !! initialize x and y arrays on the host
  do i = 1,N;  x(i) = 1.0e0; y(i) = 1.0e0;  enddo

  !! TODO 2: Start timer here
  call timer%start("    Offload     ");

  !! TODO 1: Offload with teams distribute parallel for
    !$omp target teams distribute parallel for        !!blk
    do i = 1,N;  y(i) = a*x(i) + y(i); enddo

  !! TODO 2: Stop timer here and report resuls
  call timer%stop();
  call timer%print();

end program main
! if Intel compile emits this error:
!  *.f90:(.text+0x5f): relocation truncated to fit: R_X86_64_PC32 against `.bss'
! Compile with:
! ifort -mcmodel=medium   *.f90
