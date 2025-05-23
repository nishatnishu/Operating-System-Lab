#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};
int main() {
    int n, completed = 0, currentTime = 0, minIndex;
    float totalTAT = 0, totalWT = 0;

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter the Arrival Time of P%d: ",p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter the Burst Time of P%d: ",p[i].pid);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    printf("\n Preemptive SJF (SRTF) Scheduling...\n");

    while (completed < n) {
        minIndex = -1;
        int minRT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                if (p[i].remainingTime < minRT) {
                    minRT = p[i].remainingTime;
                    minIndex = i;
                } else if (p[i].remainingTime == minRT) {
                    if (p[i].arrivalTime < p[minIndex].arrivalTime) {
                        minIndex = i;
                    }
                }
            }
        }

        if (minIndex != -1) {
            p[minIndex].remainingTime--;
            currentTime++;

            if (p[minIndex].remainingTime == 0) {
                completed++;
                p[minIndex].completionTime = currentTime;
                p[minIndex].turnaroundTime = p[minIndex].completionTime - p[minIndex].arrivalTime;
                p[minIndex].waitingTime = p[minIndex].turnaroundTime - p[minIndex].burstTime;

                totalTAT += p[minIndex].turnaroundTime;
                totalWT += p[minIndex].waitingTime;
            }
        } else {
            currentTime++; 
        }
    }

    printf("\n SRTF Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\n Average Waiting Time: %.2f\n", totalWT / n);
    printf(" Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
