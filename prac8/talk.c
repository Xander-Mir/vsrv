#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define READ 0
#define WRITE 1 
char *msg = "Hello from parent!"; 
int main(){
   int fd[2], bytesRead; 
   char buffer[128]; 
   pipe(fd);
   if (fork()==0) { //создаем дочерний процесс
      //код для дочернего процесса 
      close(fd[READ]);
      write(fd[WRITE], msg, strlen(msg)+1);
      close(fd [WRITE]);
    }else{
      //код для родительского процесса
      close(fd[WRITE]);
      bytesRead = read(fd[READ], buffer, sizeof(buffer) - 1);
      if (bytesRead > 0) {
          buffer[bytesRead] = '\0';   // завершаем строку
          printf("Получено: %s\n", buffer);
      }
      close(fd[READ]);
      }
   return 0;
}