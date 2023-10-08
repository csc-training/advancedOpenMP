  module mod_timer
   ! Developed by Lars Koesterke @ TACC 
   
   private
   integer, parameter     :: m = 20
   
   type, public :: cls_timer
   
   private
   integer                         :: n = 0
   integer(8), dimension(2,m)      :: it
   integer(8)                      :: itr
   character(len=16), dimension(m) :: c
   
   contains
   
   procedure, public :: reset
   procedure, public :: start
   procedure, public :: stop
   procedure, public :: print
   
   endtype cls_timer
   
   contains
   
   subroutine reset(this)
   
   class(cls_timer) :: this
   this%n  = 0
   this%it = -1
   this%c  = 'undef'
   
   end subroutine
   
   
   subroutine start(this, c)
   
   class(cls_timer) :: this
   character(len=*) :: c
   character(len=16) :: c16
   
   this%n = this%n + 1
   if (this%n > m) then
     write (*,*) 'No more timers available'
     stop 'Fatal ERROR in method START of class CLS_TIMER'
   endif
   call system_clock(this%it(1,this%n), this%itr)
   ! to get PGI 11 going
   c16 = c
   this%c(this%n) = c16
   
   end subroutine
   
   
   subroutine stop(this)
   
   class(cls_timer) :: this
   
   call system_clock(this%it(2,this%n))
   
   end subroutine
   
   
   subroutine print(this)
   
   class(cls_timer) :: this
   
   write (*,*)
   write (*,'(a,es7.1)') 'Action           ::   time/s     Time resolution = ', 1./real(this%itr)
   write (*,'(a)')       '------'
   do i=1, this%n
     write (*,'(a,a, f7.3)') this%c(i), ' :: ',               &
                               (real(this%it(2,i) - this%it(1,i))) / real(this%itr)
   enddo
   
   end subroutine
   
 end module mod_timer
