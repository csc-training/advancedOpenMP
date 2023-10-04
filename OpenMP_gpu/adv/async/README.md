# asynchronous offload with no wait


With the nowait clause on a target construct
the target task can execute in the background
and the encountering thead/task can immediately
continue execution.

Also, the depend clause can be used to order
(wait for) other asynchronous offloads to complete.

To ensure threads for the target tasks
a parallel region can be constructed to
enclose the asynchronous offloads to asssure
availability of threads*.  
(The standard does not state
anything about the implementation of
how threads are secured for asynch behavior.
In this example we create a parallel region to
get threads explicitly.
In the future "free agent" threads could
do the offloading.

The asyn_offload(.cpp | .F90) code illustrates
the concept of executing offloads asynchronously.
Initialization of v1 and v2 can occur simultaneously,
but the axpy operation must wait for their
completion.  Also, the host_independent_parallel_work
execution and the device axpy computation can occur
simultaneous.


1.) Look over the code.  
    We use integers just to make checking simple, and use
    one GPU thread to minimize the size of the target 
    directive name.

    a.) Have all three target offloads execute asynchornously
        with nowait clauses. TODO 1a-c:
    b.) Give the first two target out dependence type 
        "for" the v1 and v2 variables. TODO 1a-b:
    c.) On the third target region (axpy operation) 
        create "in" dependence type for v1 and v2 variables,
        and "out" for p. TODO 1c.
    d.) Provide a taskwait after the  host_independent_parallel_work
        call to wait for the target offload completions. TODO 1d

2.)  
    a.) Enclose the 3 targets and host_... execution in
        a parallel region which uses 3 threads (with
        a num_threads clause). TODO 2a:
    b.) Enclose the three target constructs within a masked
        (formerly master) construct. TODO 2b:
    c.) Have the master thread execute the validation loop

3.) Compile and run.
    Did it run correctly?

4.) Questions:
    Why were only three threads, the minimal number of 
    threads, suggested?
    Why was a master construct thread (not single) 

5.) Could you have created an explicit task for the
    validation loop and with an "in" dependence on 
    p?
