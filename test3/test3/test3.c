#include<stdio.h>
#include<stdlib.h>

/*START LIST*/
struct llnode {
	int val;
	struct llnode *nextNode;
};
typedef struct llnode llnode;

int add(llnode **nody, int val) {
	if (nody == NULL) {
		return -1;
	}
	else if (*nody == NULL) {
		(*nody) = (llnode*)malloc(sizeof(llnode));
		(*nody)->val = val;
		(*nody)->nextNode = NULL;
		return 0;
	}
	else {
		return add(&((*nody)->nextNode), val);
	}
}

int printList(llnode *nody) {
	if (nody == NULL) {
		return 0;
	}
	printf("%d\n", nody->val);
	return printList(nody->nextNode);
}
/*END LIST*/
/*START FUNCTION_POINTERS*/
int sq(int x) {
	return x * x;
}
int driver(int(*f)(int), int x) {
	return (*f)(x);
}
/*END FUNCTION_POINTERS*/

int main(void) {
	/*LIST
	llnode * nody = NULL;
	add(&nody, 5);
	add(&nody, 7);
	printList(nody);
	while (1) {}
	*/
	/*function pointers
	int(*g)(int) = sq;
	int i;
	printf("function address of sq: %p\n", sq);
	printf("address pointed at by g: %p\n", g);
	for (i = 0; i < 0xa;i++) {
		printf("%d squared: ... %d ... %d ... %d\n", i, driver(sq,i), (*g)(i), driver(g, i));
	}
	/*STRING
	char stringy[100];
	scanf("%s", stringy);
	printf("%s\n", stringy);
	stringy[0] = 'b';
	printf("%s\n", stringy);
	*/
	unsigned int num = 0xb << 4;
	unsigned int temp = 0x111111 << 8 + 0x0 << 4 + 0x1;
	num = temp & num;
	num = num | 0xa<<4;

	printf("%x",num);
	

	while(1){}
}

