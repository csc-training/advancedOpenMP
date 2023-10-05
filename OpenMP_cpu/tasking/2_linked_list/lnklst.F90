module param
integer,parameter :: N=100
end module

module data
   type :: node
     integer            :: x
     type(node),pointer :: next
   end type
end module


program follow
use param
use data
implicit none
integer i
type(node), pointer :: ptr

!!   Trivially create nodes via
!!   an array of nodes, link them.

type(node),target    :: a(N)

  !for(i=0;i<N-1;i++){
   do i = 1,N-1
      a(i)%x= i
      a(i)%next=>a(i+1)
   end do
   a(N)%x    =  N 
   a(N)%next => null()
  
   ptr=>a(1)

!$omp parallel
!$omp single
   do while(associated(...)) !!<-- do while ??? is associated (not null)
     !$omp ...               !!<-- execute foo as a task
        call foo(...)        !!<-- function to task, hand it the pointer
     !$omp end task

                             !!     single threaded
      ... => ...%next        !!<<-- advances pointer serially
   end do
!$omp end single
!$omp end parallel

end program

subroutine foo(ptr)
use data
use omp_lib, only : omp_get_thread_num
type(node) :: ptr

   write(*, '( " executed node ",i3.3, "thrd ",i3.3)' ) ptr%x,omp_get_thread_num()

end subroutine

!! See the following for working with Fortran Pointers.
!!http://cs.ubishops.ca/ljensen/fortran/pointer.htm
!!http://www.cs.rpi.edu/~szymansk/OOF90/bugs.html#7
!!http://people.ds.cam.ac.uk/nmm1/fortran/paper_12.pdf
!!http://stackoverflow.com/questions/19436011/fortran-pointer-arithmetic pointer
!!http://stackoverflow.com/questions/19436011/fortran-pointer-arithmetic recursion
!!http://stackoverflow.com/questions/3940820/pointer-as-a-dummy-argument   passing pointer

!!https://en.wikibooks.org/wiki/Fortran/Fortran_examples
