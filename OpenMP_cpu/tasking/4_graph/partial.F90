program partial
implicit none
integer,parameter :: N=100
integer :: i,a(N), id=0
integer :: sum=0
!integer :: id=0  ! dependence var

   do i = 1,N
      a(i) = i
   end do
   a(50) = 0

!$omp parallel
!$omp single

   do i = 1,N

     if(a(i) == 0) then
                               ! use id, defined above as the "dependence" variable
                               ! What dependence type? Hint: You want these tasks to
                               ! compute simultaneous.
                               ! Does "i" need to be put in a firstprivate clause?

                               ! depend(<???>:id) firstprivate(<other_var?>)

        !$omp task             ! fill in dependence and data sharing
          call foo(i,a,N, sum)
        !$omp end task
     else
                               ! use id, defined above as the "dependence" variable
                               ! What dependence type? You want all previous tasks
                               ! to finish. Hint:  Will a "write dependence" do this?
                               ! Does "i" need to be put in a firstprivate clause?

                               ! depend(<???>:id) firstprivate(<other_var?>)

        !$omp task             ! fill in dependence and data sharing
          call foo(i,a,N, sum)
        !$omp end task
     endif

   end do

!$omp end single
!$omp end parallel


end program

subroutine foo(i,a,n, sum)
implicit none
integer :: i,n,a(n), sum
   !$omp critical
     sum = sum + a(i)
   !$omp end critical
   if(a(i) == 0) then
     print*," Partial Sum at zero point ", sum
   end if
end subroutine
