# private clause with a work index

## BACKGROUND
The present ex1.F90 code creates a parallel region,
and passes the thread number to a routine to print it.
(You can compile and run it. --not necessary--)

```
    !$omp parallel
       call foo(omp_get_thread_num())
    !$omp end parallel
```

## Exercise
Copy ex1.F90 to ex1b.F90 and make the following changes:

1.)  Make "id" a variable in the main program.
2.)  Assign id in the parallel construct using the omp_get_thread_num() api function
     and pass it as an argument like this:

```
     integer :: id

     !$omp parallel ...    !! leave this alone
        id = omp_get_thread_num()
        call  foo(id)
     !$omp end parallel
```

3.)  Compile and run the code:

```
     ftn   -fopenmp ex1b.F90       #LUMI
     ifort -fopenmp ex1b.F90       #TACC
     export OMP_NUM_THREADS=64
     ./a.out | sort
```

     What happened?  (Probably the code works-- but is it correct? **
     (Oops, forget to make id a private variable?)
     If so, use the private clause to make id private (recompile & run)
     Do not look at ex1c.F90 below until you have tried your exe1b.c execution.

4.)  Now copy ex1c.F90 below into a file called ex1c.F90, compile and run. 
     It illustrates the idea of slowing down threads to convince
     yourself that a race condition exists on the id variable.
     Look at the code carefully, and explain what is happening in this code.

     Hmmm, quess why  foo(omp_get_thread_num()) does the right thing?

 
``` 
program ex1b  !! broken
use  omp_lib
integer :: id

!$omp parallel
  id = omp_get_thread_num()
  call foo(id)
 !call foo(omp_get_thread_num())
!$omp end parallel

end program ex1

subroutine foo(id)
  write( *, '(" thrd_id ",i0.3)' ),id
end subroutine

end program ex1b
```
```
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
```
