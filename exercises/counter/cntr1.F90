program main
  use omp_lib
  integer :: cntr=100

  print*, " The sequence of values printed should be, 1 - 100."
  print*, " Execute:  ./a.out | sort for checking."

  !$omp parallel 
  !$omp single
     do while(cntr>0)
       !$omp task              !! what clause goes here for cntr?
             write(*,'("cntr value=",i0.3)') cntr
       !$omp end task
       cntr = cntr -1
     end do
  !$omp end single
  !$omp end parallel

end program
