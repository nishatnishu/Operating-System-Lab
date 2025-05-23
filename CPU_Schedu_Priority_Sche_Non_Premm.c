#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
};

int main() {
    int n, completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        printf("Enter Priority of P%d (lower value = higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].isCompleted = 0;
    }

    printf("\n Scheduling using Priority (Non-Preemptive)...\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].isCompleted && p[i].arrivalTime <= currentTime) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            p[idx].isCompleted = 1;

            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\n Priority (Non-Preemptive) Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].priority,
               p[i].completionTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
