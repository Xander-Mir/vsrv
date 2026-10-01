#include <stdio.h>
#include <stdlib.h>

int main(){
		int rows, cols;
		printf("Введите rows и cols: ");
		if (scanf("%d %d",&rows, &cols)!=2 || rows <= 0 || cols <= 0){
			printf("Ошибка ввода\n");
			return 1;
		}


		int *arr = malloc((size_t)rows*cols*sizeof(int));
		if(!arr){
			printf("Не удалось выделить память.\n");
			return 1;
		}


		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				arr[i*cols + j] = i*j;
			}
		}

		//вывод значений
		printf("Значения массива:\n");
		for(int i = 0; i < rows; i++){
			printf("[");
			for(int j = 0; j < cols; j++){
				printf(" %d ", arr[i*cols + j]);
			}
			printf("]\n");
		}

		//вывод адресов
		printf("Адреса элементов массива:\n");
		for(int i = 0; i < rows; i++){
			printf("[");
			for(int j = 0; j < cols; j++){
				printf(" %p ", &arr[i*cols + j]);
			}
			printf("]\n");
		}

		free(arr);
	return 0;
}

