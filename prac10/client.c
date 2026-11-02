#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/shm_server_client"
#define SEM_NAME "/sem_server_client"
#define SIZE 256

int main() {
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    char *shmem = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);

    sem_t *sem = sem_open(SEM_NAME, 0);

    sem_wait(sem);

    printf("Клиент: Получено из памяти: \"%s\"\n", shmem);

    munmap(shmem, SIZE);
    close(fd);
    sem_close(sem);

    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);
    return 0;
}

