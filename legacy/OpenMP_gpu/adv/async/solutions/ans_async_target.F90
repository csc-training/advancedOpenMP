!include "open_lib.h"

!subroutine host_independent_parallel_work(); call sleep(1); end subroutine
subroutine host_independent_parallel_work()
use omp_lib, only : omp_get_thread_num; print*,omp_get_thread_num(); call sleep(1); end subroutine

program main
   implicit none
   integer,parameter   :: N=16
   integer             :: i
   integer,allocatable :: p(:), v1(:), v2(:)
   allocate( p(N), v1(N), v2(N) )

!! TODO 2a: create a prallel region with three threads.
   !$omp parallel num_threads(3)

!! TODO 2b: use master|masked to have a single generator thread
      !$omp master !or masked

!!TODO 1a: add nowait and depend(out:...) and appropriate map
         !$omp target nowait depend(out:v1) map(from:v1)
         do i =1,N; v1(i)=1; enddo
         !$omp end target

!!TODO 1b: add nowait and depend(out:...) and appropriate map
         !$omp target nowait depend(out:v2) map(from:v2)
         do i =1,N; v2(i)=2; enddo
         !$omp end target

!!TODO 1c: add nowait and depend(in:...) and appropriate maps
!!         for v1,v2 and p.  (optional: depend(out:p))*

         !$omp target nowait depend(in:v1,v2) depend(out:p) &
         !$omp&                 map(to:v1,v2)   map(from:p)
         do i=1,N; p(i) = v1(i) * v2(i); enddo
         !$omp end target
     !$omp end master

         call host_independent_parallel_work()

!!TODO 1d: wait for target asks to complete here.
         !$omp taskwait
                             !! or  !$omp task depend(in:p)

!! TODO 2c: use master|masked for a single thread here
         !$omp master !or masked
          do i=1,N; if( p(i) /= 2 ) stop ("p != 2"); enddo
          print*,"Passed."
!! end TODO 2c:
         !$omp end master
                             !!     !$omp end task

   !$omp end parallel

   deallocate( p, v1, v2 )
 
end program main

