module data_A
  integer,parameter :: N=16
  real(8), allocatable :: A(:)

  contains
    subroutine init_A(n)
      integer :: n

      allocate(A(n))
!! TODO 1:  insert a a target enter data construct here

    end subroutine init_A

    subroutine free_A()

!! TODO 2:  insert a a target exit data construct here
      deallocate(A)

    end subroutine free_A
end module data_A

program main
   use data_A

   call init_A(N)

!! TODO 3:  offload with a target construct (no clauses)
       do i = 1,N
         A(i)=1.0
       end do

!! TODO 4:  use an update construct to get back from device

   print*,A(1)

   call free_A()

end program main
