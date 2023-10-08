
include  "timer.f90"

program main

!! TODO 1a: Use the module in timer.f90 
!!          and instantiate a type(cls_timer) class
  !use  ...
  !type(...) timer

!! TODO 1b: Time a 1 second sleep
  !call timer%...
      call sleep(1);
  !call timer%...

!! TODO 1c: Now time a print statement
  !call timer%...
      print*, " Hello Helsinki."
  !call timer%...

!! TODO 1d: report measurements
  !call timer%...

end program main
