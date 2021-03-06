#include <stdio.h>
#include <stdlib.h>
int bs(int *x, int size, int(*compare)(int x, int y)) {
	int i;
	int temp;
	int swapped = 1;
	if (x == NULL) {
		return -1;
	}

	while (swapped) {
		swapped = 0;
		for (i = 0;i<size-1;i++) {
			if ((*compare)(x[i],x[i+1])) {
				temp = x[i];
				x[i] = x[i+1];
				x[i+1] = temp;
				swapped = 1;
			}
		}
	}
	return 0;
}

int lt(int x, int y) {
	if (x < y) {
		return 1;
	}
	return 0;
}
int gt(int x, int y) {
	if (x > y) {
		return 1;
	}
	return 0;
}

int main(void) {
	int i = 0;
	int vals[10];
	for (i = 0;i<10;i = i + 1) {
		vals[i] = 100 - i;
	}
	for (i = 0;i<10;i++) {
		printf("in[%d]=%d\n", i, vals[i]);
	}
	/* HERE: call bs() with the appropriate comparison function */
	int (*funcyL)(int, int) = lt;
	int (*funcyG)(int, int) = gt;
	bs(vals,10,funcyG);
	for (i = 0;i<10;i++) {
		printf("out[%d]=%d\n", i, vals[i]);
	}
	while(1){}
	return 0;
}