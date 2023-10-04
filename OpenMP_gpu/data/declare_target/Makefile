
# LUMI
ifneq ("$(LUMI_LMOD_FAMILY_PRGENV)","")
  CPP=CC
# OMP_FLAG=-fopenmp
  OMP_TARG=
  ifneq ($(shell ml is-loaded partition/G && echo 0), 0)
            $(error Partition partition/G not loaded.)
  endif
endif

#TACC
ifeq ($(TACC_SYSTEM),ls6)
  CPP=clang++
# OMP_FLAG=-fopenmp 
# OMP_TARG=-fopenmp-targets=nvptx64
  ifneq ($(shell ml is-loaded my_llvm16 && echo 0), 0)
            $(error Partition my_llvm16 not loaded.)
  endif
endif

a.out: main.o fun.o
	$(CPP) $(OMP_FLAG) $(OMP_TARG) $^ -o $@ 

%.o: %.cpp
	$(CPP) $(OMP_FLAG) $(OMP_TARG) $? -o $@ -c 

clean:
	rm -f a.out *.o

# clang++ --help
# https://makefiletutorial.com
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# -Wl,-v   is the way to pass -v to loader
