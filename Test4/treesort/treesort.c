#include <stdio.h>
#include <stdlib.h>
/*//////STRUCTS//////*/
struct bstNode;
struct avlNode;
struct qNode;
struct bqNode;

struct bstNode {
	int val;
	struct bstNode *l;
	struct bstNode *r;
};
typedef struct bstNode bstNode;

struct avlNode {
	int balance; /* -1 Left, 0 balanced, +1 Right */
	int val;
	struct avlNode *l;
	struct avlNode *r;
};
typedef struct avlNode avlNode;

struct qNode {
	avlNode *pval;
	struct qNode *nxt;

};
typedef struct qNode qNode;

struct bqNode {
	bstNode *pval;
	struct bqNode *nxt;
};
typedef struct bqNode bqNode;

/*//////FUNCTION DECLARATIONS//////*/
int add_bst(bstNode **root, int val);
int printTreeInOrder(bstNode *root);
int printLevelOrder(bstNode *root);
int benqueue(bqNode **current, bstNode *addition);
bstNode* bdequeue(bqNode **current);
bstNode* bpeek(bqNode *current);

/*//////BST FUNCTIONS//////*/
int add_bst(bstNode **root, int val) {
	if (root == NULL) {
		return -1;

	}
	else if (*root == NULL) {
		*root = (bstNode*)malloc(sizeof(bstNode));
		(*root)->val = val;
		(*root)->l = NULL;
		(*root)->r = NULL;
		return 0;
	}
	else {
		if (val >= (*root)->val) {
			return add_bst(&((*root)->r), val);
		}
		else {
			return add_bst(&((*root)->l), val);
		}
	}
}

int printTreeInOrder(bstNode *root) {
	if (root == NULL) {
	}
	else {
		printTreeInOrder(root->l);
		printf("%d\n", root->val);
		printTreeInOrder(root->r);
	}
	return 0;
}

int printLevelOrder(bstNode *root) {
	bstNode *temp = NULL;
	bqNode *queuey = NULL;
	benqueue(&queuey, root);
	while (bpeek(queuey) != NULL) {
		temp = bdequeue(&queuey);
		printf("%d ", temp->val);
		if (temp->l != NULL) {
			benqueue(&queuey, temp->l);
		}
		if (temp->r != NULL) {
			benqueue(&queuey, temp->r);
		}
	}
	printf("\n");
	return 0;
}

/*//////BQUEUE FUNCTIONS/////////*/
int benqueue(bqNode **current, bstNode *addition) {
	bqNode *temp = NULL;
	if (current == NULL) {
		return -1;
	}
	else if (*current == NULL) {/*if first node*/
		*current = (bqNode*)malloc(sizeof(bqNode));
		(*current)->pval = addition;
		(*current)->nxt = NULL;
		return 0;
	}
	else {
		temp = *current;
		*current = (bqNode*)malloc(sizeof(bqNode));
		(*current)->pval = addition;
		(*current)->nxt = temp;
		return 0;
	}
}

bstNode* bdequeue(bqNode **current) {
	bstNode *temp = NULL;
	if (current == NULL) {
		return NULL;
	}
	else if (*current == NULL) {
		return NULL;
	}
	else if ((*current)->nxt == NULL) {
		temp = (*current)->pval;
		free(*current);
		*current = NULL;
		return temp;
	}
	else {
		return bdequeue(&((*current)->nxt));
	}
}

bstNode* bpeek(bqNode *current) {
	if (current == NULL) {
		return NULL;
	}
	else if (current->nxt == NULL) {
		return current->pval;
	}
	else {
		return bpeek(current->nxt);
	}
}

/*/////////MAIN//////////*/
int main(void) {
	int *x = 0;
	int b = 0;
	int value = 0;
	bstNode *input_tree = NULL;
	#pragma warning(disable : 4996)
	while ((b=scanf("%d", &value)) != 0) {
		add_bst(&input_tree, value);
	}
	printTreeInOrder(input_tree);

	while (1) {};
	return 0;
}