#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void processNetos() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("Processo %d, filho de %d\n", pid, ppid);

    sleep(5);

    printf("Processo %d finalizado\n", pid);
    exit(0);
}

void processFilhos() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("Processo %d, filho de %d\n", pid, ppid);

    for (int i = 0; i < 3; i++) {
        pid_t child_pid = fork();

        if (child_pid == 0) {
            processNetos();
        }
    }

    while(wait(NULL)>=0);

    printf("Processo %d finalizado\n", pid);
    exit(0);
}

int main() {
    pid_t main_pid = getpid();

    for (int i = 0; i < 2; i++) {
        pid_t child_pid = fork();

        if (child_pid == 0) {
            processFilhos();
        }
    }
    while(wait(NULL)>=0);

    printf("Processo principal %d finalizado\n", main_pid);
    return 0;
}

