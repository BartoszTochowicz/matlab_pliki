#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2]; // Tablica do przechowywania deskryptorów łącza
    pid_t pid1, pid2;

    // Tworzenie łącza komunikacyjnego
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Tworzenie pierwszego procesu
    if ((pid1 = fork()) == 0) {
        // Proces potomny wykonujący `cat /etc/passwd`

        // Zamykamy nieużywany koniec łącza (do odczytu)
        close(pipefd[0]);

        // Przekierowanie wyjścia standardowego (stdout) na koniec do zapisu łącza
        dup2(pipefd[1], STDOUT_FILENO);

        // Zamykamy deskryptor zapisu łącza (już przekierowany)
        close(pipefd[1]);

        // Uruchamiamy `cat /etc/passwd`
        execlp("cat", "cat", "/etc/passwd", NULL);

        // W razie błędu
        perror("execlp cat");
        exit(1);
    } else if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    // Tworzenie drugiego procesu
    if ((pid2 = fork()) == 0) {
        // Proces potomny wykonujący `sort`

        // Zamykamy nieużywany koniec łącza (do zapisu)
        close(pipefd[1]);

        // Przekierowanie wejścia standardowego (stdin) na koniec do odczytu łącza
        dup2(pipefd[0], STDIN_FILENO);

        // Zamykamy deskryptor odczytu łącza (już przekierowany)
        close(pipefd[0]);

        // Uruchamiamy `sort`
        execlp("sort", "sort", NULL);

        // W razie błędu
        perror("execlp sort");
        exit(1);
    } else if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    // Proces macierzysty

    // Zamykamy obydwa końce łącza (nie będą używane przez proces macierzysty)
    close(pipefd[0]);
    close(pipefd[1]);

    // Oczekiwanie na zakończenie obu procesów potomnych
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
