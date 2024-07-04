# 5-State-CPU-Simulator
LINUX CPU SCHEDULING SIMULATOR (5 STATE MODEL)
-Overview-
This project is a CPU Scheduling Simulator implemented in C++ using the 5 state model. The simulator makes use of various Linux system calls such as fork, exec, pipes (both named and unnamed), dup/dup2, as well as the pthread library.

-Features-
5 State Model: Implements the five states of a process - New, Ready, Running, Blocked, Exit.
Scheduling Algorithms: Includes First-Come-First-Serve (FCFS), Round Robin (RR), Shortest Job First (SJF), and Shortest Remaining Time First (SRTF).
Process Management: Uses Linux system calls and pipes for inter-process communication.
Statistics: Outputs average Turnaround Time (TAT) and average Waiting Time (WT) to process_stats.txt for further analysis.

-Compilation and Usage-
Please refer to compile_instructions.txt for detailed instructions on how to compile and use the program.

-Known Issues-
Multithreading: Mutex or semaphores are not implemented, which may lead to false values due to preemption (though this is very unlikely).
MinHeap Class: The MinHeap class is implemented using linked lists instead of a binary tree, which may affect performance.

-Output-
process_stats.txt: This file saves the average Turnaround Time (TAT) and average Waiting Time (WT), providing useful statistics for analysis.
