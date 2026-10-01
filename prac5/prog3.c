#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

bool simple(int num){ // функция возвращает 1 если число простое, 0 если нет
	if (num <= 1) return false;   // 0, 1, отрицательные — не простые
    if (num <= 3) return true;    // 2 и 3 — простые
    if (num % 2 == 0) return false;  // чётные > 2 — не простые
	for(int i=3; (long long)i*i<=num; i+=2){
		if(num%i==0){
			return false;
		}
	}
	return true;
}

void func(int arr[], int size, int *count, int *max){
	*count = 0;
	*max = 0;
	for(size_t i=0; i < size; i++){
		int num = arr[i];
		if (num > 1 && !simple(num)) {
    		(*count)++;
    		if (num > *max) *max = num;
		}
	}
}

int main(){
	int arr[] = {4,6,3,6,8,9,12,35,123,53,78,2,34,67,8,2,9,47,39};
	int count = 0;
	int max = 0;
	int size = (int)ARRAY_SIZE(arr);
	func(arr, size, &count, &max);
	printf("Массив:");
	for(size_t i=0; i<size; i++){
		printf(" %d", arr[i]);
	}
	printf("\nЧисло составных чисел: %d\nМаксимальное из них: %d\n", count, max);
	return 0;
}

