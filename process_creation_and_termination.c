#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Uh-oh!☹️ Failed to create the Process!");
        return 1;
    }
    else if (pid == 0) {

        printf("👶Hilluu! I'm the child process 😎\n");
        printf("My PID is: %d\n", getpid());
        printf("My parent's PID is: %d\n", getppid());
        printf("I'm off to do some cool stuff...\n");
        sleep(2);
        printf("👶Aaaand I'm done! Time to nap (exit) 💤\n");
        exit(0);
    }
    else {

        printf("🧓Hey hey! Parent process reporting in 🧠\n");
        printf("My PID is: %d\n", getpid());
        printf("Just created a child with PID: %d\n", pid);
        printf("🧓Gonna chill here and wait for my kid to finish...\n");
        wait(NULL);
        printf("🧓My kid's done! Now it's my turn to peace out 👋\n");
    }

    return 0;
}

