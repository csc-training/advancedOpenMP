program ex1
use  omp_lib

!$omp parallel
  call foo(omp_get_thread_num())	
!$omp end parallel

end program ex1
	
subroutine foo(id)
  write( *, '(" thrd_id ",i0.3)' ),id
end subroutine
