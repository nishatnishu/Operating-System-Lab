#include <stdio.h>

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
    int n, quantum, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    int queue[n], front = 0, rear = 0, visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    printf("\n Starting Round Robin Scheduling...\n");

    while (completed < n) {
        int idx = queue[front++];
        if (p[idx].remainingTime > 0) {
            if (p[idx].remainingTime > quantum) {
                time += quantum;
                p[idx].remainingTime -= quantum;
            } else {
                time += p[idx].remainingTime;
                p[idx].remainingTime = 0;
                p[idx].completionTime = time;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                completed++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrivalTime <= time && p[i].remainingTime > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remainingTime > 0) {
            queue[rear++] = idx;
        }
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (p[i].remainingTime > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    float totalWT = 0, totalTAT = 0;

    printf("\n Round Robin Scheduling Result:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].waitingTime, p[i].turnaroundTime);
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
