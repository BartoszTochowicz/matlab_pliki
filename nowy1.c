#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
    printf("Proces nowy1.c zakończony sygnałem %d\n", sig);
    exit(1);
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    printf("Proces nowy1.c działa. PID: %d\n", getpid());
    sleep(20);
    printf("Proces nowy1.c zakończył swoje działanie.\n");
    return 0;
}
