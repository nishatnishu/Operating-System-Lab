#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {
    int n, currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter the Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter the Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        printf("Enter the Priority of P%d (lower value = higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
    }

    printf("\n Priority Scheduling(Preemptive)...\n");

    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].isCompleted && p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remainingTime--;
            currentTime++;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                p[idx].isCompleted = 1;

                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printf("\n  Priority (Preemptive) Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].priority,
               p[i].completionTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT/(float) n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT/(float) n);

    return 0;
}
