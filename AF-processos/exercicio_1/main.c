#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void processoFilhoDosFilhos() {
    pid_t meu_pid = getpid();
    printf("Processo filho %d criado\n", meu_pid);
}

void processoFilhoDoPai() {
    pid_t meu_pid = getpid();
    printf("Processo filho %d criado\n", meu_pid);
}

int main() {
    pid_t primeiro_filho = fork();
    if (primeiro_filho == 0) {
        processoFilhoDoPai();
    } else {
        printf("Processo pai criou %d\n", primeiro_filho);
        fflush(stdout);
        pid_t segundo_filho = fork();
        if (segundo_filho == 0) {
            processoFilhoDosFilhos();
        } else {
            printf("Processo pai criou %d\n", segundo_filho);
            while(wait(NULL) < 0);
            printf("Processo pai finalizado!\n");
        }
    }
    return 0;
}