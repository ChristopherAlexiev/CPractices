#include<stdlib.h>
#include<stdio.h>

struct llnode {
	int val;
	llnode *nextNode;
};
typedef struct llnode llnode;

int add(llnode **nody, int val) {
	if (nody == NULL){
		return -1;
	}
	else if (*nody == NULL) {
		*nody = (llnode*)malloc(sizeof(llnode));
		(*nody)->val == val;
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
	printf(nody->val);
	return printList(nody->nextNode);
}

int main(void) {
	llnode * nody = NULL;
	add(&nody, 5);
	add(&nody, 7);
	printList(nody);
}

