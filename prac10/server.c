#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/shm_server_client"
#define SEM_NAME "/sem_server_client"
#define SIZE 256

int main(){
   int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
   ftruncate(fd, SIZE);
   char *shmem = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

   sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);

   strcpy(shmem, "Проверка связи");
   printf("Server: Отправлено сообщение: \"%s\"\n", shmem);

   sem_post(sem);

   munmap(shmem, SIZE);
   close(fd);
   sem_close(sem);

   return 0;
}

