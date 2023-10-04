program partial
implicit none
integer,parameter :: N=100
integer :: i,a(N), id=0
integer :: sum=0

   do i = 1,N
      a(i) = i
   end do
   a(50) = 0

!$omp parallel
!$omp single

   do i = 1,N

     if(a(i) /= 0) then
        !$omp task depend(in:id) firstprivate(i)
          call foo(i,a,N, sum)
        !$omp end task
     else
        !$omp task depend(out: id) firstprivate(i) 
          call foo(i,a,N, sum)
        !$omp end task
     endif
                                               ! since i is auto private
                                               ! it becomes auto firstprivate for task
                                               ! Hence firstprivate(i) is not necessary
                                               ! but it is good practice to specify it as such
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
     print*," Partial Sum at zero point at index=",i," sum=", sum
   end if
end subroutine
