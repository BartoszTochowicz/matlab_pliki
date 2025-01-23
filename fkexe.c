#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    // Tworzenie pierwszego procesu potomnego
    if ((pid1 = fork()) == 0) {
        execl("./nowy1", "nowy1", NULL);
        perror("execl failed for nowy1");
        exit(1);
    } else if (pid1 < 0) {
        perror("Fork failed for nowy1");
        exit(1);
    }

    // Tworzenie drugiego procesu potomnego
    if ((pid2 = fork()) == 0) {
        execl("./nowy2", "nowy2", NULL);
        perror("execl failed for nowy2");
        exit(1);
    } else if (pid2 < 0) {
        perror("Fork failed for nowy2");
        exit(1);
    }

    // Proces macierzysty
    int status;
    pid_t finished_pid;
    while ((finished_pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Proces potomny o PID %d zakończył się z kodem %d\n", finished_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Proces potomny o PID %d zakończył się sygnałem %d\n", finished_pid, WTERMSIG(status));
        }
    }

    printf("Proces macierzysty kończy działanie.\n");
    return 0;
}
