# operating_systems_projects
Process scheduler
Process Structure: A structure to hold process information, including PID, burst time, waiting time, and turnaround time.

Functions:
calculate_waiting_time: Computes waiting time for each process.
calculate_turnaround_time: Computes turnaround time for each process.
find_average_times: Calculates and prints average waiting and turnaround times.
print_processes: Displays the details of each process.

Main Function:
Initializes an array of processes.
Forks child processes to simulate execution.
Each child process sleeps for its burst time to simulate work.
The parent process waits for all child processes to complete before calculating and printing the average times.

Compile the C program using the gcc compiler. Run the following command:
gcc -o process_scheduler process_scheduler.c

This command tells the compiler to compile process_scheduler.c and create an executable file named process_scheduler.

Once the code is compiled successfully, you can run the executable with the following command:
./process_scheduler

This is a simple implementation of a process scheduler using the First-Come, First-Serve (FCFS) algorithm. This example will create child processes using fork() and simulate the scheduling
