// TestyStuff.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>

int mallocy(int**val) {
	(*val) = (int)malloc(sizeof(int));
	//(val) = (int**)malloc(sizeof(int*));
	(**val) = 3;
}


int main()
{
	char * a = (char *)malloc(sizeof(char)*100);
	int**A = (int**)malloc(sizeof(int*));
	mallocy(A);
	printf("%d", **A);
	scanf("%s", a);
	printf("%s", a);
	while (1) {};
	return 0;
}

