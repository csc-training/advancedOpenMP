
function dotprod(B,C,n) result(sum)
   real    :: B(n), C(n), sum
   integer :: n, i
   integer :: sum_teams = 0
   integer :: got_teams = 0
   sum       = 0.0e0
  
   !! TODO 1a: map B and C and scalars as "tofrom"
   !! TODO 1b-c include reductions for sum and sum_teams.
   !$omp  target teams num_teams(100) \
   !$omp&              map(to: B[0:n], C[0:n]) defaultmap(tofrom:scalar) \
   !$omp&              reduction(+:sum,sum_teams)

   !$omp distribute simd reduction(+:sum)
      do i = 1,N
         sum = sum + B(i) * C(i)
      end do

      sum_teams=sum_teams + 1
      if(omp_get_team_num()==0) got_teams=omp_get_num_teams()

      write(*,'("sum_teams= ",i4," got_teams=",i4," sum= ",f12.0,"  (n=",i12,")" )') &
                 sum_teams,got_teams,sum,n
   !$omp end target teams

end function

program main
   integer, parameter ::  N=1024*1024
   integer :: i
   real    :: sum, B(N),C(N)  !!init vv

   do i=1,N;  B(i)=1.0e0; C(i)=1.0e0;  end do

   sum=dotprod(B,C,N)

end program main
