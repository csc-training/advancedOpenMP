# Offloading to specific devices

## BACKGROUND
On multi-device nodes, you can specify a device to
perform the offload to, with the device clause.

## Exercises

1.) Look over the code.
    It loops over the devices, and offloads to each device a
    portion  of the aypx operation.
    Create a parallel for|do around this loop have the number
    threads match the number of devices (1 thread per device).
    In the target construct specify a device for each thread to
    do a portion, and map x and y portions to the device. 
     
    compile and run.

2.) Could you have done this without the do loop, and just
    use the thread number and the device number.  Try it....
     
