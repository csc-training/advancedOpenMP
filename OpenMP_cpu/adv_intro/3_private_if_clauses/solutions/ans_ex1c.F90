program ex1c
use  omp_lib
   integer :: id
   !$omp parallel
      if(omp_get_thread_num() > 0) then
        id = omp_get_thread_num()
        call system("sleep 1")
      else
        id = omp_get_thread_num()
      end if
      call foo(id)
   !$omp end parallel
end program ex1c

subroutine foo(id)
  write( *, '(" thrd_id ",i0.3)' ) id
end subroutine

