program hello
  !! TODO 1: Add appropriate use statement for OMP functions

  implicit none

  integer :: num_devs
  logical :: init_dev

    num_devs = omp_get_num_devices()
    print *, "Number of available devices", num_devs


   !! TODO 2: execute function on a device
   !!         PUT "map(init_dev)" after target directive
   !!         Will explain map clause later.

      init_dev = omp_is_initial_device()


    if (init_dev) then
      write(*,*) "Ran on host"
    else 
      write(*,*) "Ran on device"
    end if

end program
