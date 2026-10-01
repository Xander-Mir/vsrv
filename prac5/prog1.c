#include <stdio.h>
#include <stdlib.h>

int main(){
	int N = 0;
	printf("Введите количество элементов: ");
	if (scanf("%d", &N) == 1) {
        printf("Вы ввели: %d\n", N);
    } else {
        printf("Ошибка: это не число\n");
    }
	int *ptr = (int*) calloc(N,sizeof(int));
	if(ptr == NULL){
		printf("Не удалось выделить память.");
	}

	for(int i=0; i<N; i++){
		printf("Адрес ptr[%d]=%p\n",i,ptr + i);
	}
	free(ptr);
	return 0;
}

