#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
 
int main() {
    const char *shm_name = "/my_shared_memory";
    const int SIZE = 4096;
 
/*создание сегмента и конфигурирование разделяемой памяти */
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
 
    pid_t pid = fork();
//создаем дочерний процесс
    if (pid == 0) {
        //Дочерний процесс: чтение разделяемой памяти
        char *shared_mem = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("Child read: ");
        printf("%s\n",shared_mem);
        munmap(shared_mem, SIZE);
    } else {
        //Процесс родитель: запись в разделяемую память
        char *shared_mem = (char *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        const char *message = "Hello from parent!";
        sprintf(shared_mem, "%s", message);
        munmap(shared_mem, SIZE);
// ожидание завершения дочернего процесса
        wait(NULL);  
    }
 // удаление разделяемой памяти
    shm_unlink(shm_name); 
    return 0;
}