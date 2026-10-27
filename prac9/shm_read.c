#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int main(){
	int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
	if (fd == -1){
		perror("shm_open");
		return 1;
	}

	char *ptr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED){
		perror("mmap");
		return 1;
	}
	printf("Получено сообщение: %s\n", ptr);

	munmap(ptr, SHM_SIZE);
	close(fd);
	shm_unlink(SHM_NAME);

}