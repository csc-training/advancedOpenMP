#For these exercises you should use 1 nodes:


```
        Frontera:   $ idev            -N 1 -tpn 56  For Tutorial Reservation

       Stampded2:   $ idev            -N 1 -tpn 48  For Tutorial Reservation
                    $ idev -p skx-dev -N 1 -tpn 48  Outside of Tutorial time

            SDSC:   $ srun -p debug   -N 1 --ntasks-per-node=24 -t 00:30:00 \
                                           --pty --wait=0 --export=ALL /bin/bash
            PSC:    $ interact        -N 1 --ntasks-per-node=28

            LUMI: Interactive Use
                  export PP=/project/project_462000390

                  partition C:
                  source $PP/sourceme_cpu
                  mlc                     #ml LUMI/23.03 ...  #see sourceme_cu
                  idevc                   #srun -p debug ...  #see sourceme_cpu

                  partition G:
                  source $PP/sourceme_gpu
                  mlg                     #ml LUMI/23.03 ...  #see sourceme_cu
                  idevg                   #srun -p debug ...  #see sourceme_cpu
```

