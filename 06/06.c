#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef struct node* pos;

typedef struct node {
	int value;
	pos next;
} node;

int push(pos);
int pop(pos);
int pushQ(pos);
int popQ(pos);

pos allocateData();

int main(void) {
	srand(time(NULL));
	
	pos stack = NULL;
	pos queue = NULL;
	stack = allocateData();
	queue = allocateData();

	int choice = -1;
	int rtrn = 0;

	printf("--stack--\n");
	printf("1. push random int (10-100)\n");
	printf("2. pop\n");
	printf("----\n");
	printf("--kveve--\n");
	printf("3. push random int (10-100)\n");
	printf("4. pop\n");
	printf("----\n");
	printf("0. exit\n");

	while (choice != 0) {
		scanf("%d", &choice);
		switch (choice){
		case 1:
			rtrn = push(stack);
			if (rtrn == -1) 
				printf("mem err...");
			else
				printf("el: %d pushed added to the stack\n", rtrn);
			rtrn = 0;
			break;
		case 2:
			rtrn = pop(stack);
			if (rtrn == -1)
				printf("the stack was empty\n");
			else
				printf("el: %d removed from the queue\n", rtrn);
			break;
		case 3:
			rtrn = pushQ(queue);
			if (rtrn == -1)
				printf("mem err...");
			else
				printf("el: %d pushed added to the queue\n", rtrn);
			rtrn = 0;
			break;
		case 4:
			rtrn = pop(queue);
			if (rtrn == -1)
				printf("the queue was empty\n");
			else
				printf("el: %d removed from the queue\n", rtrn);
			break;
		case 0:
			break;
		default:
			printf("input err, try again... \n");
		}
	}
	

}

pos allocateData() {
	pos temp = NULL;
	temp = (pos)malloc(sizeof(node));
	if (temp == NULL) {
		printf("mem err, returning null...");
		return NULL;
	}
	temp->next = NULL;
	return temp;
}

int push(pos head) {
	pos temp = NULL;
	temp = allocateData();

	if (temp == NULL)
		return -1;
	else
		temp->value = rand()%91+10;
	if (head->next == NULL) {
		head->next = temp;
		return temp->value;
	}
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = temp;

	return temp->value;
}

int pop(pos head) {
	int rtrn = -1;
	if (head->next == NULL) 
		return -1;
	
	while (head->next->next != NULL) {
		head = head->next;
	}
	rtrn = head->next->value;
	free(head->next);
	head->next = NULL;
	return rtrn;
}

int pushQ(pos head) {
	pos temp = NULL;
	pos headPlaceholder = NULL;
	temp = allocateData();
	if (temp == NULL)
		return -1;
	else
		temp->value = rand() % 91 + 10;

	if (head->next == NULL) {
		head->next = temp;
		return temp->value;
	}
	headPlaceholder = head->next->next;
	temp->next = head->next;
	head->next = temp;
	return temp->value;

}
