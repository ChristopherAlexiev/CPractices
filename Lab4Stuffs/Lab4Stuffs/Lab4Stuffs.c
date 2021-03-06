// Lab4Stuffs.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *store;
	unsigned int size;
	unsigned int end;
} HeapType;

int initHeap(HeapType *pHeap, int size);
int inorder(HeapType *pHeap, int **output, int *o_size);
int inorderHelper(HeapType pHeap, int index, int *output, int *outputPos, int o_size);
int preorder(HeapType *pHeap, int **output, int *o_size);
int postorder(HeapType *pHeap, int **output, int *o_size);
int addHeap(HeapType *pHeap, int key);
int findHeap(HeapType *pHeap, int key);
int delHeap(HeapType *pHeap, int *key);
int maximum(int a, int b);
/*helpers:*/
int switchUp(HeapType *pHeap, unsigned int index);
int switchDown(HeapType *pHeap, unsigned int index);

int initHeap(HeapType *pHeap, int size) {
	if (pHeap == NULL) {
		return -1;
	}
	pHeap->store = (int *)malloc(size*sizeof(int));
	pHeap->size = size;
	pHeap->end = 0;
	return 0;
}

/*insertion functions:*/
int addHeap(HeapType *pHeap, int key) {
	if (pHeap == NULL) {
		return -1;
	} else if (pHeap->size == pHeap->end) {
		return -1; /*CHECK WITH LE NEBU IF NEEDED*/
	}
	pHeap->store[pHeap->end] = key;
	pHeap->end = (pHeap->end) + 1;
	switchUp(pHeap, (pHeap->end)-1);
	return 0;
}

int switchUp(HeapType *pHeap, unsigned int index) {
	if (pHeap == NULL) {
		return -1;
	}
	int temp = 0;
	if (index * 2 + 1 < pHeap->end && pHeap->store[index*2 + 1] >pHeap->store[index]) {
		temp = pHeap->store[index * 2 + 1];
		pHeap->store[index * 2 + 1] = pHeap->store[index];
		pHeap->store[index] = temp;
	} else if (index * 2 + 2 < pHeap->end && pHeap->store[index * 2 + 2] >pHeap->store[index]) {
		temp = pHeap->store[index * 2 + 2];
		pHeap->store[index * 2 + 2] = pHeap->store[index];
		pHeap->store[index] = temp;
	} else if (index * 2 + 1 < pHeap->end || index * 2 + 2 < pHeap->end) {
		/*if there were children but they weren't bigger finish the function*/
		return 0;
	}

	if (index == 0) {
		return 0;
	}

	if ((index-1)/2 >= 0) {
		return switchUp(pHeap, (index - 1) / 2);
	}
	return 0;
}

/*deletion functions:*/
int delHeap(HeapType *pHeap, int *key) {
	if (pHeap == NULL) {
		return -1;
	}
	else if (pHeap->end == 0) {
		return -1; /*CHECK WITH LE NEBU IF NEEDED*/
	}
	*key = pHeap->store[0];
	switchDown(pHeap, 0);
	return 0;
}

int switchDown(HeapType *pHeap, unsigned int index) {
	int temp = 0;
	int *tempArr = NULL;
	int i = 0;
	int counter = 0;
	if (pHeap == NULL) {
		return -1;
	}
	/*technically less cases than below are needed but whatevs*/
	if (index * 2 + 1 < pHeap->end && index * 2 + 2 < pHeap->end){
		/*if 2 children*/
		pHeap->store[index] = maximum(pHeap->store[index * 2 + 2], pHeap->store[index * 2 + 1]);
		if (pHeap->store[index * 2 + 2] > pHeap->store[index * 2 + 1]) {
			return switchDown(pHeap, index * 2 + 2);
		} else {
			return switchDown(pHeap, index * 2 + 1);
		}
	} else if (index * 2 + 1 < pHeap->end && index * 2 + 2 >= pHeap->end) {
		pHeap->store[index] = pHeap->store[index * 2 + 1];
		return switchDown(pHeap, index * 2 + 1);
	} else if (index * 2 + 1 >= pHeap->end && index * 2 + 2 < pHeap->end) {
		pHeap->store[index] = pHeap->store[index * 2 + 2];
		return switchDown(pHeap, index * 2 + 2);
	} else {
		/*if no children resift down the end parts of the heap to fill in all gaps*/
		temp = pHeap->end;
		tempArr = (int *)malloc(sizeof(int)*(temp -index -1));
		for (i = index +1; i < temp; i++) {
			tempArr[counter] = pHeap->store[i];
			counter++;
		}
		pHeap->end = index;
		for (counter = 0; counter < (temp - index - 1); counter++) {
			addHeap(pHeap, tempArr[counter]);
		}
		return 0;
	}
}

/*traversals*/
int inorder(HeapType *pHeap, int **output, int *o_size) {
	int outputPos = 0;
	if (output == NULL || pHeap == NULL || o_size == NULL) {
		return -1;
	}
	
	*output = (int *)malloc(sizeof(int) * pHeap->end);
	*o_size = pHeap->end;
	return inorderHelper(*pHeap, 0, *output, &outputPos, *o_size);
}

int inorderHelper(HeapType pHeap, int index, int *output, int *outputPos, int o_size) {
	if (output == NULL || outputPos == NULL) {
		return -1;
	}
	if (index*2+1 < pHeap.end) {
		inorderHelper(pHeap, index*2+1, output, outputPos, o_size);
	}
	output[*outputPos] = pHeap.store[index];
	*outputPos = *outputPos + 1;
	if (index*2+2 < pHeap.end) {
		inorderHelper(pHeap, index*2+2, output, outputPos, o_size);
	}
	return 0;
}

int preorder(HeapType *pHeap, int **output, int *o_size) {
	int outputPos = 0;
	if (output == NULL || pHeap == NULL || o_size == NULL) {
		return -1;
	}

	*output = (int *)malloc(sizeof(int) * pHeap->end);
	*o_size = pHeap->end;
	return preorderHelper(*pHeap, 0, *output, &outputPos, *o_size);
}

int preorderHelper(HeapType pHeap, int index, int *output, int *outputPos, int o_size) {
	if (output == NULL || outputPos == NULL) {
		return -1;
	}
	output[*outputPos] = pHeap.store[index];
	*outputPos = *outputPos + 1;
	if (index * 2 + 1 < pHeap.end) {
		preorderHelper(pHeap, index * 2 + 1, output, outputPos, o_size);
	}
	if (index * 2 + 2 < pHeap.end) {
		preorderHelper(pHeap, index * 2 + 2, output, outputPos, o_size);
	}
	return 0;
}

int postorder(HeapType *pHeap, int **output, int *o_size) {
	int outputPos = 0;
	if (output == NULL || pHeap == NULL || o_size == NULL) {
		return -1;
	}

	*output = (int *)malloc(sizeof(int) * pHeap->end);
	*o_size = pHeap->end;
	return postorderHelper(*pHeap, 0, *output, &outputPos, *o_size);
}

int postorderHelper(HeapType pHeap, int index, int *output, int *outputPos, int o_size) {
	if (output == NULL || outputPos == NULL) {
		return -1;
	}
	if (index * 2 + 1 < pHeap.end) {
		postorderHelper(pHeap, index * 2 + 1, output, outputPos, o_size);
	}
	if (index * 2 + 2 < pHeap.end) {
		postorderHelper(pHeap, index * 2 + 2, output, outputPos, o_size);
	}
	output[*outputPos] = pHeap.store[index];
	*outputPos = *outputPos + 1;
	return 0;
}

int findHeap(HeapType *pHeap, int key) {
	int i = 0;
	if (pHeap == NULL) {
		return -1;
	}
	for (i = 0; i < pHeap->end; i++) {
		if (pHeap->store[i] == key) {
			return 1; /*found*/
		}
	}
	return 0;
}

int maximum(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int main(void){
	int i = 0;
	int size = 0;
	int *output = NULL;
	int *key = (int *)malloc(sizeof(int));
	HeapType *pHeap = (HeapType *)malloc(sizeof(HeapType));
	initHeap(pHeap, 7);
	addHeap(pHeap, 10);
	addHeap(pHeap, 5);
	addHeap(pHeap, 6);
	addHeap(pHeap, 7);
	addHeap(pHeap, 1);
	delHeap(pHeap, key);
	inorder(pHeap, &output, &size);
	
	for (i = 0; i < size; i++) {
		printf("%d\n", output[i]);
	}

	/*
	printf("key:%d\n",delHeap(pHeap, key));
	printf("%d\n", pHeap->store[0]);
	printf("%d\n", pHeap->store[1]);
	printf("%d\n", pHeap->store[2]);
	*/


	while(1){}
}

