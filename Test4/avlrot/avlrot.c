#include <stdio.h>
#include <stdlib.h>
/*//////STRUCTS//////e*/
struct avlNode;
struct qNode;

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

/*//////FUNCTION DECLARATIONS//////e*/
int add_bst(avlNode **root, int val);
int printTreeInOrder(avlNode *root);
int printLevelOrder(avlNode *root);
int isAVL(avlNode **root);
int findDepth(avlNode *root);
int rotate(avlNode **root, unsigned int Left0_Right1);
int dblrotate(avlNode **root, unsigned int MajLMinR0_MajRMinL1);
int enqueue(qNode **current, avlNode *addition);
avlNode* dequeue(qNode **current);
avlNode* peek(qNode *current);

/*//////AVLTREE FUNCTIONS//////e*/
int isAVL(avlNode **root) {
	int depthLeft = 0;
	int depthRight = 0;
	if (root == NULL) {
		return -1;
	} else if (*root == NULL) {
		return 0;
	}
	depthLeft = findDepth((*root)->l);
	depthRight = findDepth((*root)->r);
	if (abs(depthLeft - depthRight) <= 1 && isAVL(&((*root)->r))==0 && isAVL(&((*root)->l)) == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

int findDepth(avlNode *root) {
	int leftSize = 0;
	int rightSize = 0;
	if (root == NULL) {
		return 0;
	} else {
		leftSize = findDepth(root->l) + 1;
		rightSize = findDepth(root->r) + 1;
		if (leftSize > rightSize) {
			return leftSize;
		} else {
			return rightSize;
		}
	}
}

int rotate(avlNode **root, unsigned int Left0_Right1) {
	avlNode *newRoot = NULL;
	avlNode *newRootChild = NULL;
	avlNode *newRootChildChild = NULL;
	if (root == NULL) {
		return -1;
	} else if ((*root) == NULL) {
		return -1;
	}
	
	if (Left0_Right1 == 0) {
		/*pivot => new root, old roots => new roots left, pivot's left => new root's right*/
		if ((*root)->r == NULL) {
			return -1;
		} else {
			/*prepare the new pointers*/
			newRoot = (*root)->r;
			newRootChild = (*root);
			newRootChildChild = (*root)->r->l;
			/*remove unbalanced pointers*/
			(*root)->r->l = NULL;
			(*root)->r = NULL;
			/*set pointers to balanced tree*/
			*root = newRoot;
			(*root)->l = newRootChild;
			(*root)->l->r = newRootChildChild;
			return 0;
		}
	} else if (Left0_Right1 == 1) {
		/*pivot => new root, old roots => new roots left, pivot's left => new root's right*/
		if ((*root)->l == NULL) {
			return -1;
		}
		else {
			/*prepare the new pointers*/
			newRoot = (*root)->l;
			newRootChild = (*root);
			newRootChildChild = (*root)->l->r;
			/*remove unbalanced pointers*/
			(*root)->l->r = NULL;
			(*root)->l = NULL;
			/*set pointers to balanced tree*/
			*root = newRoot;
			(*root)->r = newRootChild;
			(*root)->r->l = newRootChildChild;
			return 0;
		}
	} else {
		return -1;
	}
}

int dblrotate(avlNode **root, unsigned int MajLMinR0_MajRMinL1) {
	int success = 0;
	if (root == NULL) {
		return -1;
	} else if ((*root) == NULL) {
		return -1;
	}
	if (MajLMinR0_MajRMinL1 == 0) {
		if ((*root)->r == NULL) {
			return -1;
		} else if ((*root)->r->l == NULL){
			return -1;
		} else {

			success = rotate(&((*root)->r), 1);
			if (success == -1) {
				return -1;
			}
			return rotate(root,0);
		}
	} else if (MajLMinR0_MajRMinL1 == 1) {
		if ((*root)->l == NULL) {
			return -1;
		} else if ((*root)->l->r == NULL) {
			return -1;
		} else {
			success = rotate(&((*root)->l), 0);
			if (success == -1) {
				return -1;
			}
			return rotate(root, 1);
		}
	} else {
		return -1;
	}

}

int add_bst(avlNode **root, int val) {
	if (root == NULL) {
		return -1;

	}
	else if (*root == NULL) {
		*root = (avlNode*)malloc(sizeof(avlNode));
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

int printTreeInOrder(avlNode *root) {
	if (root == NULL) {
	}
	else {
		printTreeInOrder(root->l);
		printf("%d\n", root->val);
		printTreeInOrder(root->r);
	}
	return 0;
}

int printLevelOrder(avlNode *root) {
	avlNode *temp = NULL;
	qNode *queuey = NULL;
	enqueue(&queuey, root);
	while (peek(queuey) != NULL) {
		temp = dequeue(&queuey);
		printf("%d ", temp->val);
		if (temp->l != NULL) {
			enqueue(&queuey, temp->l);
		}
		if (temp->r != NULL) {
			enqueue(&queuey, temp->r);
		}
	}
	printf("\n");
	return 0;
}

/*//////BQUEUE FUNCTIONS/////////e*/
int enqueue(qNode **current, avlNode *addition) {
	qNode *temp = NULL;
	if (current == NULL) {
		return -1;
	}
	else if (*current == NULL) {/*if first node*/
		*current = (qNode*)malloc(sizeof(qNode));
		(*current)->pval = addition;
		(*current)->nxt = NULL;
		return 0;
	}
	else {
		temp = *current;
		*current = (qNode*)malloc(sizeof(qNode));
		(*current)->pval = addition;
		(*current)->nxt = temp;
		return 0;
	}
}

avlNode* dequeue(qNode **current) {
	avlNode *temp = NULL;
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
		return dequeue(&((*current)->nxt));
	}
}

avlNode* peek(qNode *current) {
	if (current == NULL) {
		return NULL;
	}
	else if (current->nxt == NULL) {
		return current->pval;
	}
	else {
		return peek(current->nxt);
	}
}

/*/////////MAIN//////////e*/
int main(void) {
	int b = 0;
	int value = 0;

	avlNode *input_tree = NULL;
	/*
	#pragma warning(disable : 4996)
	while ((b = scanf("%d", &value)) != 0) {
	add_bst(&input_tree, value);
	}

	printTreeInOrder(input_tree);
	printLevelOrder(input_tree);
	*/
	add_bst(&input_tree, 5);
	add_bst(&input_tree, 3);
	add_bst(&input_tree, 4);
	b = isAVL(&input_tree);
	printf("%d\n", b);
	dblrotate(&input_tree, 1);
	b = isAVL(&input_tree);
	printf("%d\n", b);
	printf("\n");
	printTreeInOrder(input_tree);
	printLevelOrder(input_tree);
	while (1) {};
	return 0;
}


