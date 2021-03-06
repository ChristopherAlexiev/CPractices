#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *store;
	unsigned int size;
	unsigned int end;
	int(*compare)(int x, int y);
} intHeap_T;

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


int store(intHeap_T * heap, int value) {
	if (heap == NULL) {
		return -1;
	}
	else if (heap->size == heap->end) {
		return -1; 
	}
	heap->store[heap->end] = value;
	heap->end = (heap->end) + 1;
	siftUp(heap, (heap->end) - 1);
	return 0;
}

int siftUp(intHeap_T *pHeap, unsigned int index) {
	if (pHeap == NULL) {
		return -1;
	}
	int temp = 0;
	if (index * 2 + 1 < pHeap->end && (*(pHeap->compare))(pHeap->store[index], pHeap->store[index * 2 + 1])) {
		temp = pHeap->store[index * 2 + 1];
		pHeap->store[index * 2 + 1] = pHeap->store[index];
		pHeap->store[index] = temp;
	}
	else if (index * 2 + 2 < pHeap->end && (*(pHeap->compare))(pHeap->store[index], pHeap->store[index * 2 + 2])) {
		temp = pHeap->store[index * 2 + 2];
		pHeap->store[index * 2 + 2] = pHeap->store[index];
		pHeap->store[index] = temp;
	}
	else if (index * 2 + 1 < pHeap->end || index * 2 + 2 < pHeap->end) {
		/*if there were children but they weren't bigger finish the function*/
		return 0;
	}

	if (index == 0) {
		return 0;
	}

	if ((index - 1) / 2 >= 0) {
		return siftUp(pHeap, (index - 1) / 2);
	}
	return 0;
}

/*deletion functions:*/
int retrieve(intHeap_T* heap, int *rvalue) {
	if (heap == NULL || rvalue == NULL) {
		return -1;
	}
	else if (heap->end == 0) {
		return -1;
	}
	*rvalue = heap->store[0];
	/*put last thing at top:*/
	heap->store[0] = heap->store[(heap->end) - 1];
	heap->end = (heap->end) - 1;
	if (heap->end != 0) {
		siftDown(heap, 0);
	}
	return 0;
}


int siftDown(intHeap_T *pHeap, unsigned int index) {
	int side = 1;
	if (pHeap == NULL) {
		return -1;
	}
	int temp = 0;
	if (index * 2 + 2 < pHeap->end){
		if ((*(pHeap->compare))(pHeap->store[index*2+1], pHeap->store[index * 2 + 2])) {
			temp = pHeap->store[index * 2 + 2];
			side = 2;
		}
		else {
			temp = pHeap->store[index * 2 + 1];
			side = 1;
		}
		if ((*(pHeap->compare))(pHeap->store[index], temp)) {
			pHeap->store[index * 2 + side] = pHeap->store[index];
			pHeap->store[index] = temp;
		}
		else {
			/*if there were children but they weren't bigger finish the function*/
			return 0;
		}
	}
	else if (index * 2 + 1 < pHeap->end && (*(pHeap->compare))(pHeap->store[index], pHeap->store[index * 2 + 1])) {
		temp = pHeap->store[index * 2 + 1];
		pHeap->store[index * 2 + 1] = pHeap->store[index];
		pHeap->store[index] = temp;
		side = 1;
	}
	else {
		/*if there were children but they weren't bigger finish the function*/
		return 0;
	}

	if (index *2 +side < pHeap -> end) {
		return siftDown(pHeap, index*2+side);
	}
	return 0;
}

int hs(int *x, int size, int(*compare)(int x, int y)) {
	/*set up heap*/
	int temp = 0;
	int i = 0;
	int *rvalue = NULL;
	rvalue = (int *)malloc(sizeof(int));
	intHeap_T heap;
	heap.store = (int *)malloc(size * sizeof(int));
	heap.size = size;
	heap.end = 0; /* empty heap condition; obey this spec */
	heap.compare = (*compare); /* assuming lt was defined as in part A */
	
	if (x == NULL) {
		return -1;
	}

	for (i = 0; i < size;i++) {
		store(&heap, x[i]);
	}

	/*perform sort*/
	while (heap.end > 1) {
		temp = heap.store[0];
		heap.store[0] = heap.store[(heap.end) - 1];
		heap.store[(heap.end) - 1] = temp;
		heap.end = heap.end - 1;
		siftDown(&heap, 0);
	}

	/*set up returned array*/
	for (i = 0; i < size;i++) {
		x[i] = heap.store[i];
	}

	return 0;
}

int main(void) {
	int i = 0;
	int arrSize = 10;
	int arr[10] = {4, 3, 2, 7, 5, 1, 0, -4, 10, 8};
	int *rvalue = NULL;
	int(*comp)(int, int) = gt;
	rvalue = (int *)malloc(sizeof(int));
	intHeap_T heap;
	heap.store = (int *)malloc(1000 * sizeof(int));
	heap.size = 1000;
	heap.end = 0; /* empty heap condition; obey this spec */
	heap.compare = lt; /* assuming lt was defined as in part A */

	store(&heap, 5);
	store(&heap, 6);
	store(&heap, 2);
	store(&heap, 9);
	retrieve(&heap, rvalue);
	for (i = 0; i < heap.end; i++) {
		printf("%d\n",heap.store[i]);
	}
	printf("%d\n", *rvalue);

	printf("AHHH\n");
	hs(arr, arrSize, comp);
	for (i = 0; i < arrSize; i++) {
		printf("%d\n", arr[i]);
	}
	while(1){}
}