#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1 = fork();
    int status;

    if (child1 < 0) {
        printf("Error in forking.\n");
        exit(EXIT_FAILURE);
    } else if (child1 == 0) {
        execlp("ls", "ls", "-l", NULL);
        exit(EXIT_SUCCESS); 
    } else {
        pid_t child2 = fork();
        if (child2 < 0) {
            printf("Error in forking.\n");
            exit(EXIT_FAILURE);
        } else if (child2 == 0) {
            execlp("ps", "ps", "-l", NULL);
            exit(EXIT_SUCCESS); 
        } else {
            wait(&status);
            printf("The first child that completed is %d\n", status);
            wait(NULL); 
            printf("Both child processes have completed.\n");
        }
    }

    return 0;
}
