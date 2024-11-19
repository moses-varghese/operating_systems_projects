//compile by executing gcc -o process_scheduler process_scheduler.c in bash or linux terminal 
//and then execute ./process_scheduler which is the new file generated by gcc
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
    int pid;          // Process ID
    int burst_time;   // Burst time of the process
    int waiting_time; // Waiting time for the process
    int turnaround_time; // Turnaround time for the process
} Process;

void calculate_waiting_time(Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void calculate_turnaround_time(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void find_average_times(Process processes[], int n) {
    calculate_waiting_time(processes, n);
    calculate_turnaround_time(processes, n);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void print_processes(Process processes[], int n) {
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n = 4; // Number of processes
    Process processes[n];

    // Define processes (Process ID, Burst Time)
    processes[0].pid = 1; processes[0].burst_time = 10;
    processes[1].pid = 2; processes[1].burst_time = 5;
    processes[2].pid = 3; processes[2].burst_time = 8;
    processes[3].pid = 4; processes[3].burst_time = 12;

    // Fork processes
    for (int i = 0; i < n; i++) {
        /**
         * Forks a new child process.
         *
         * This line of code creates a new child process by calling the `fork()` system call. 
         The child process will be an exact copy of the current process, with its own memory 
         space and execution context. The `pid` variable will be set to 0 in the child 
         process, and to the process ID of the child process in the parent process.
         */
        pid_t pid = fork();
        if (pid == 0) { // Child process
            printf("Process %d started with burst time %d\n", processes[i].pid, processes[i].burst_time);
            sleep(processes[i].burst_time); // Simulate process execution
            printf("Process %d completed\n", processes[i].pid);
            exit(0); // Exit child process
        }
    }

    // Wait for all child processes to complete
    //The parent process waits for all child processes 
    //to complete before calculating and printing the average times.
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    find_average_times(processes, n);
    print_processes(processes, n);

    return 0;
}