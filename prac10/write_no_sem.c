#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#define SHM_NAME "/shm_counter"
#define SIZE sizeof(struct shmseg)

struct shmseg {
    int cntr;
    int write_complete;
};

void increment(struct shmseg *shmp, int total) {
    int cntr = shmp->cntr;
    for (int i = 0; i < total; i++) {
        cntr += 1;
        shmp->cntr = cntr;
    }
}

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    struct shmseg *shmp = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    shmp->cntr = 0;
    shmp->write_complete = 0;

    pid_t pid = fork();
    if (pid == 0) {
        increment(shmp, 1000000);
        return 0;
    } else {
        increment(shmp, 1000000);
        wait(NULL);
    }

    printf("Итоговый счётчик (без семафора): %d\n", shmp->cntr);

    munmap(shmp, SIZE);
    close(fd);
    shm_unlink(SHM_NAME);
    return 0;
}

