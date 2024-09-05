program main
  use omp_lib
  integer :: i=0, cntr=100

  !$omp parallel 
  !$omp single
     do while(cntr>0)
       !$omp task firstprivate(i) firstprivate(cntr)  !! what clause goes here for cntr?
          if( i  ==  50 ) then
             call system ("sleep 1");
             write(*,'("Expecting ",i4," value=",i4)') i,cntr
          endif
       !$omp end task
       cntr = cntr -1
          i =    i +1
     end do
  !$omp end single
  !$omp end parallel

end program
