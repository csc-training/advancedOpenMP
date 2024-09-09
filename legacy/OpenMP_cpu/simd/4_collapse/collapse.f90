
subroutine element_mxm(a,b,c)
integer,parameter :: N=3, M=4096
double precision,dimension(N,*) :: a,b,c

!! The two loops can be collapsed

 !!$omp 
   do j=1,M
      do i = 1,N
      c(i,j) = c(i,j) + a(i,j) * b(i,j)
   enddo; enddo
end subroutine
