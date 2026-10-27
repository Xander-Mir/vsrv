#include <unistd.h>
#include <stdio.h>
#define READ 0
#define WRITE 1

int main(){
	int fd[2];
	pipe(fd);
	if (fork() == 0){
		dup2(fd[WRITE], fileno(stdout));
		close(fd[0]); close(fd[1]);
		execlp("ls", "ls", NULL);
	}
	else{
		dup2(fd[READ], fileno(stdin));
		close(fd[0]); close(fd[1]);
		execlp("wc", "wc", "-l", NULL);
	}

}