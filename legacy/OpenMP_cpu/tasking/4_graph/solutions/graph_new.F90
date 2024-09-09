program graph
implicit none
integer :: a=0,b=0,c=0,d=0,e=0

!$omp parallel
!$omp single

  !$omp task depend(out:a,b,c)              !TASK 1
    call f1(a, b, c)
  !$omp end task

  !$omp task depend(out:d,e)                !TASK 2
    call f2(d, e)
  !$omp end task

  !$omp task depend(in:c,d)                 !TASK 3
    call f3(c,d)
  !$omp end task

  !$omp task depend(inout:e)                   !TASK 4
    call f4(e) 
  !$omp end task

  !$omp task depend(in:a,e) depend(out:b,c)   !TASK 5
    call f5(a,b,c,e) 
  !$omp end task

!$omp end single
!$omp end parallel

  write(*,'( /,"END a,b,c,d,e= ",i3,i3,i3,i3,i3,i3)' ) a,b,c,d,e

end program

   
subroutine f1(a,b,c)
integer :: a,b,c
            a = 1; b=1; c=1;
            write(*,'("T1  OUT_dep  a,b,c  ",3i2)' ) a,b,c
end subroutine

subroutine f2(d,e)
integer :: d,e
            d = 1; e=1;
            write(*,'("T2  OUT_dep  d,e =",2i2)' ) d,e
end subroutine

subroutine f3(c,d)
integer :: c,d
        if(c /=d ) print*,"Hmm"
        write(*,'("T3   IN_dep  c,d ",2i2)' ) c,d
end subroutine

subroutine f4(e)
integer :: e
        e=e+5;
        write(*,'("T4   INOUT_dep  e ",i2)' ) e
end subroutine

subroutine f5(a, b, c, e)
integer :: a,b,c,e
        if(a==0) print*,"Hmm" 
        b=9; c=9
        write(*,'("T5   IN_dep  a,e ",2i2,"   OUT_dep b,c  ",2i2)' ) a,e,b,c
end subroutine
