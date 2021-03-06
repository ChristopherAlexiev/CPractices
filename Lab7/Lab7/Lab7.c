#include <stdio.h>
#include <stdlib.h>

int sq(int x) {
	return x * x;
}

int cu(int x) {
	return x * x*x;
}

int driver(int(*f)(int), int x) {
	return (*f)(x);
}

int main(void) {
	int j = 0;
	int(*g)(int) = cu;
	printf("adx of function sq: %p\n", sq);
	printf("adx of function cu: %p\n", cu);
	for (j = 0;j<0xa;j = j + 1) {
		printf("%d: %d %d\n", j, driver(sq, j), (*g)(j));
	}
	while(1){ }
}
int bubbleSort(int *array, int size) {
	int i;
	int swapped = 1;
	int temp;
	if (array == NULL) {
		return -1;
	}

	while (swapped) {
		swapped = 0;
		for (i = 1;i<size;i++) {
			if (array[i - 1]>array[i]) {
				temp = array[i - 1];
				array[i - 1] = array[i];
				array[i] = temp;
				swapped = 1;
			}
		}
	}

	return 0;

}

