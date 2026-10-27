#include <stdio.h>
void never_call(void){
    printf("[*] wow how did you manage to call this?\n");
}
int main(int argc, char **argv){
    printf("[*] you ran this binary!\n");
    return 0;
}
