program basic-tasking
    use omp
    integer :: i=0
    !$omp parallel
        do while (i < 12) 
            !$omp task
            printf("Task %d by thread %d\n", i, omp_get_thread_num());
            !$omp end task
            i=i+1;
        end do
    !$omp end parallel
end program