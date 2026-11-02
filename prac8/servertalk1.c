#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"
int main() {
   int fd;
   char readbufOld[80] = {0}, readbufNew[80] = {0};
   char end[10];
   int to_end;
   int read_bytes;
   
   /* Создаем FIFO файл, если он не существует*/
   mknod(FIFO_FILE, S_IFIFO|0640, 0);
   strcpy(end, "end");
//организуем непрерывный цикл для обмена сообщениями
   fd = open(FIFO_FILE, O_RDONLY);
   while(1) {
//открываем FIFO файл для чтения
      read_bytes = read(fd, readbufNew, sizeof(readbufNew));
      readbufNew[read_bytes] = '\0';
      if(read_bytes>0 && strcmp(readbufNew, readbufOld)!=0){
         printf("Received string: \"%s\" and length is %d\n", readbufNew, (int)strlen(readbufNew));
//копируем строку из буфера
      }
      strcpy(readbufOld, readbufNew);
      to_end = strcmp(readbufNew, end);
      if (to_end == 0) {
         close(fd);
         break;
      }
   }
   close(fd);
   return 0;
}

