#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main() {
    int pid1, pid2, pid3;

    pid1=fork();
    if(pid1==0)
    {
        while(1)
        {
            printf("Pid1 is alive\n");
            sleep(1);
        }
    }
    else
    {
        pid2=fork();
        if(pid2==0)
        {
            while(1)
            {
                printf("Pid2 is alive\n");
                sleep(1);
            }
        }
        else
        {
            sleep(3);
            kill(pid1,SIGINT);
            sleep(3);
            pid3 = fork();
            if(pid3 == 0)
            {
                while(1)
                {
                    printf("Pid2 is stopped\n");
                    sleep(1);
                }   
            }
            else{
                kill(pid2, SIGSTOP);
                sleep(3);
                kill(pid3,SIGINT);
                kill(pid2, SIGCONT);
                sleep(3);
                kill(pid2,SIGINT); 
            }
            

            
        }
    }
    return 0;
}