           !unverified
module funs
 use omp_lib
 integer,parameter :: N=16

contains
 subroutine init(v1, v2, p, n) 
   real    :: v1(*), v2(*), p(*)
    do i = 1,n
      v1(i)=2.0
      v2(i)=2.0
       p(i)=0.0
    enddo
 end subroutine init

 function maybe_change_v1(v1) result(changed)
    real    :: v1(*)
    logical :: changed
    if(_OPENMP > 201511) then
      v1(1)=1.0
      changed=.TRUE.
    else
      changed=.FALSE.
    endif
 end function
    !!https://www.openmp.org/spec-html/5.0/openmpse10.html
end module funs
   

program main
   use omp_lib
   use funs
   real    :: v1(N), v2(N), p(N)
   logical ::  changed

   call init(v1, v2, p, N) 

!! TODO 1: Beginning of structured data region "to" for v's, from for p
!! !$omp target data map(to: v1[:N], v2[:N]) map(from: p[0:N])
   !$omp target data map(to: v1, v2) map(from: p)

      !$omp target
      !$omp parallel do
      do i = 1,N; p(i) = p(i) + (v1(i) * v2(i)); enddo

      changed = maybe_change_v1(v1); 
      !! TODO 1: update just v1(0) conditionally
      !$omp target update if(changed) to(v1(1:1))

      !$omp target
      !$omp parallel do
      do i = 1,N; p(i) = p(i) + (v1(i) * v2(i)); enddo

   !$omp end target data
!! end TODO 1: end of structured data region

   print*,"final loop used: v1(1), v1(1)=",v1(1),v1(2)
   print*,"p(1), p(2)=", p(1),p(2)
   print*,"_OPENMP= ",   _OPENMP

end program main
