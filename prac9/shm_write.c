/* shm_posix_write.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int main(void) {
    /* 1. Создаём объект разделяемой памяти */
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); return 1; }

    /* 2. Устанавливаем размер */
    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    /* 3. Отображаем в адресное пространство */
    char *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) { perror("mmap"); return 1; }

    /* 4. Пишем данные */
    const char *msg = "Hello from writer!";
    strcpy(ptr, msg);
    printf("Writer: wrote \"%s\"\n", msg);

    /* 5. Отключаем и закрываем */
    munmap(ptr, SHM_SIZE);
    close(fd);

    /* 6. НЕ удаляем — читатель ещё не прочитал! */
    /* shm_unlink(SHM_NAME); — вызывать в читателе или после синхронизации */

    return 0;
}