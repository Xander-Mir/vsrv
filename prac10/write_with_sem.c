#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SHM_NAME "/shm_counter"
#define SEM_NAME "/sem_counter"
#define SIZE sizeof(struct shmseg)

struct shmseg {
    int cntr;
    int write_complete;
};

void increment(struct shmseg *shmp, sem_t *sem, int total) {

    sem_wait(sem);

    int cntr = shmp->cntr;
    for (int i = 0; i < total; i++) {
        cntr += 1;
        shmp->cntr = cntr;
    }

    sem_post(sem);
}

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    struct shmseg *shmp = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    shmp->cntr = 0;

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    pid_t pid = fork();
    if (pid == 0) {
        increment(shmp, sem, 1000000);
        return 0;
    } else {
        increment(shmp, sem, 1000000);
        wait(NULL);
    }

    printf("Итоговый счётчик (с семафором): %d\n", shmp->cntr);

    sem_close(sem);
    sem_unlink(SEM_NAME);
    munmap(shmp, SIZE);
    close(fd);
    shm_unlink(SHM_NAME);
    return 0;
}