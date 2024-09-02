---
title:  Introduction to task based parallelism
author: CSC Training
date:   2024
lang:   en
---

# Introduction to task based parallelism {.section}

# Review Worksharing

- Parallel regions are created by forking  TEAM OF THREADS.
- Worksharing constructs are placed inside parallel regions.
    - LOOP ITERATION ARE PARTITIONED
    - DATA ENVIRONMENT
    - IMPLIED BARRIERS
    - work is assigned (implicitetly) to the threads.

# Worksharing Pros

- Simplicity: Easy to implement for loop-based parallelism where iterations can be evenly distributed across threads.
- Efficiency for Regular Workloads: Ideal for situations where the workload is uniform, such as in simple loops with predictable iteration counts.
- Automatic Load Balancing (with Scheduling): OpenMP provides different scheduling options (static, dynamic) to balance the load across threads, improving performance when work distribution is uneven.
- Low Overhead: The overhead of using `#pragma omp for` is generally low, as there is no need for task creation and management.

# Worksharing Limitations

- Limited Flexibility: Suitable mainly for loop-based parallelism. Not as flexible for irregular or complex workloads that do not fit well into loop iterations.
- Barrier Synchronization: Implicit barriers at the end of the loop can cause delays, especially if some threads finish their work much earlier than others.
- No Fine-Grained Control: The developer has less control over the execution order and the distribution of work compared to tasking.

# Terminology


# Summary

- OpenMP tasks
