#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int startTime;
    int waitingTime;
    int turnaroundTime;
};

void sortByArrivalTime(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].burstTime);
    }

    sortByArrivalTime(p, n);

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;

        p[i].startTime = currentTime;
        p[i].waitingTime = p[i].startTime - p[i].arrivalTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
        currentTime += p[i].burstTime;

        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\n FCFS Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tStart\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime,
               p[i].burstTime, p[i].startTime,
               p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\n Average Waiting Time: %.2f\n", totalWT / n);
    printf(" Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
