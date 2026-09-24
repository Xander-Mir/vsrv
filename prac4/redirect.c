#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    execvp(argv[2], &argv[2]);
    perror("execvp");
    return 1;
}