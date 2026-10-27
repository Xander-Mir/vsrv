#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MQ_NAME "/my_mq"

int main(){
	mqd_t mq = mq_open(MQ_NAME, O_RDWR, 0644, NULL);
	if (mq == (mqd_t)-1){
		perror("mq_open");
		return 1;
	}
	char buf[256];
	unsigned int prio;
	ssize_t rcvd_msg = mq_receive(mq, buf, sizeof(buf), &prio);
	if(rcvd_msg == -1){
		perror("mq_receive");
	}
	else{
		printf("Received message: %s\nBytes: %zd\nPriority: %u\n", buf, rcvd_msg, prio);
	}
	mq_close(mq);
	mq_unlink(MQ_NAME);
	return 0;
}