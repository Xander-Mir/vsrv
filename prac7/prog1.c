#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void alarm_handler(int sig){
	printf("\nНет ввода.\n");
	exit(0);
}

int main(){
	printf("Введите текст:");
	signal(SIGALRM, alarm_handler);
	alarm(10);

	char text[100];
	if(fgets(text, sizeof(text), stdin)!=NULL){
		alarm(0);
		printf("Спасибо!\n");
	}
}