#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MQ_NAME "/my_mq"
struct mq_attr attr = {
    .mq_maxmsg = 10,
    .mq_msgsize = 256
};
int main(){
	mqd_t mq = mq_open(MQ_NAME, O_CREAT|O_RDWR, 0644, &attr);
	if (mq == (mqd_t)-1){
		perror("mq_open");
		return 1;
	}
	const char *msg = "Привет из Лондона!";
	if(mq_send(mq, msg, strlen(msg)+1,1)==-1){
		perror("mq_send");
	}
	else{
		printf("Sent message: %s\n", msg);
	}
	mq_close(mq);
	return 0;
}