# places for sockets

## BACKGROUND

## Exercises
The lscpu command shows that there are 8 numa nodes:
  
NUMA node(s):          8
NUMA node0 CPU(s):     0-15,128-143
NUMA node1 CPU(s):     16-31,144-159
NUMA node2 CPU(s):     32-47,160-175
NUMA node3 CPU(s):     48-63,176-191
NUMA node4 CPU(s):     64-79,192-207
NUMA node5 CPU(s):     80-95,208-223
NUMA node6 CPU(s):     96-111,224-239
NUMA node7 CPU(s):     112-127,240-255

## Exercises

node0='{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}'
node1='{16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}'
node2='{32,33,34,35,36,37,38,39,40,41,42,43,44 45,46,47}'
node3='{48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63}'
export OMP_PLACES="$node0,$node1,$node2,$node3"


export OMP_PLACES="{0}:16,{16}:16,{32}:16,{48}:16"

1.)
    Convince yourself that 
    processors 0-63   are on socket 0 (core id 0-63)
    processors 64-127 are on socket 1 (core id 64-127)

    by looking at the /proc/cpuinfo file 
    (look around at the first location of "physical id     : 1" 
    you will see procssor 63 just before it, and it's value is 64)


    processors 128-191 are on socket 0 (core id 0-63)
    processors 192-255 are on socket 1 (core id 64-127)

    What does "numactl -H"  tell you about the numa nodes?
    (Hint:  do numa nodes 0-3 all have about the same "distance"
    from each other?)

    So, to a rough approximation:
    processors 0-63   and 128-191 (core ids 0-63) can be considered as 1 numa node, and
    processors 64-127 and 192-225 (core ids 64-127) can be considered as another numa node, and

    
2.)
   Set 4 single-occupation (binding) places and use 8 threads: 

``
        export OMP_NUM_THREADS=8
        export OMP_PLACES="{0},{16},{32},{48}"
        amask_omp
```
   What is the occupation of each core.
   Fix this, by including possible cores in each place.
                                             
```
        export OMP_PLACES="{0,1},{16,17},{32,33},{48,49}"
```
   Note, the threads share of pair of cores, which could be OK.
   What is the most reasonable solution? Just assign a single
   core to each thread?  If so, change the places, and run again.

3.)
   Exercise ex3 covers NUMA more in detail, using interal notation.
   Explicitly enumerating the places, is just asking for frustration.
   Try the following, and not that you might overlook on small comma,
   with everything appearing to run coorectly, but not really so:
```
   export OMP_NUM_THREADS=16
   export OMP_PLACES='{32,33,34,35,36,37,38,39,40,41,42,43,44 45 46,47}'
   amask_omp
```
