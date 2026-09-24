/*
 * ИМЯ: Миронов Александр Александрович
 * ID: 24К0272
 * СРОК: 24.09.2026
 * НАЗНАЧЕНИЕ: Практическая работа №4
 * ФАЙЛ: task.c
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_COUNT 200

void ChildProcess(void);
void ParentProcess(void);

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execlp("echo", "echo", "I am the child", NULL);
        perror("execlp");
        exit(1);
    }
    ParentProcess();
    wait(NULL);

    return 0;
}

/* ChildProcess: выводит счётчик от 1 до MAX_COUNT */
void ChildProcess(void) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf(" This line is from child, value = %d\n", i);
    }
    printf("Child process is done\n");
}

/* ParentProcess: выводит счётчик от 1 до MAX_COUNT */
void ParentProcess(void) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("Parent process is done\n");
}
