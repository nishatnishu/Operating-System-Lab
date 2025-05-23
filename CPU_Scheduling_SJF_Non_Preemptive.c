#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool isCompleted;
};

int main() {
    int n, currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter the Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter the Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        p[i].isCompleted = false;
    }

    printf("\n Scheduling processes using SJF (Non-Preemptive)...\n");

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].isCompleted && p[i].arrivalTime <= currentTime) {
                if (p[i].burstTime < minBT) {
                    minBT = p[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].completionTime = currentTime + p[idx].burstTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            currentTime = p[idx].completionTime;
            p[idx].isCompleted = true;
            completed++;
        } else {
            currentTime++; 
        }
    }


    printf("\n SJF Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\n  Average Waiting Time: %.2f\n", totalWT / n);
    printf("  Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
