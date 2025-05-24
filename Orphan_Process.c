#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Process Creation Failed:'(" );
        exit(1);
    }

    if (pid == 0) {
        printf("👶Child: My PID is %d, my parent's PID is %d\n", getpid(), getppid());
        sleep(3);
        printf("👶Child: Now my parent's PID is %d (should be 1 if orphaned)\n", getppid());
    } else {
        printf("👨‍👧Parent: My PID is %d, I created a child with PID %d\n", getpid(), pid);
        printf("👨‍👧Parent: Exiting now...\n");
        exit(0);
    }

    return 0;
}
