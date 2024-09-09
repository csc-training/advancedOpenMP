program main
  use omp_lib
  integer,parameter :: N=1000
  integer           :: i, a=2, init_dev, ndevs
  integer           :: istart, iend, iblk_size
  integer           :: x(N), y(N)

!!TODO 1: Get the number of devices on the node
  ndevs = omp_get...
  iblk_size=N/ndevs      !! assume even divisibility

  do i=1,N; x(i)=1; y(i)=1; enddo

!!TODO 1:Create a parallel region with the number thread
!!       equal to the number of devices.
  !$omp parallel do...
  do idev=0,ndevs-1

      istart=iblk_size*idev+1;  iend=istart+iblk_size-1
!!    print*, istart, iend

      !! Each device will calculated a partition of the arrays.
      !! Device 0 calculates the first block, dev 1 the second, etc.
      !! TODO 3: For each device_id (idev) map only the portion
      !!         of x and y needed on the device.
      !$omp target...
      do i=istart,iend
         x(i) = x(i) + a*y(i);
      enddo
      !$omp end target
  end do

  do i=1,N; if(x(i) /= 3)  stop("y != 3"); enddo  !!LUMI
!!do i=1,N; if(x(i) /= 3) print*,"failed"; enddo  !!Others

end program main
