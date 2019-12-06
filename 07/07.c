#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



typedef struct node* pos;

typedef struct node {
	int value;
	struct node* next;
} node;


pos allocateData();

int calcResult(pos head);
int isItValid(char);

int main(void) {
	pos head = allocateData();
	int result = -1;
	result = calcResult(pos);
	if(result != 0) {
		printf("err with calcResult, wrong input");
		return -1;
	}
	
	
	return 0;
}

pos allocateData() {
	pos node = NULL;
	node = (pos)malloc(sizeof(pos));
	node->next = NULL;
	if(node == NULL)
		return NULL;
	else
		return node;
	
}

int calcResult(pos head) {
	
	FILE* fp = NULL;
	char c = NULL;
	fp = fopen("input.txt", "r");
	if(fp == NULL)
		return -1;
	while(c=fgetc(fp) != '\0') {
		if(!isItValid)
			return -1;
		switch(c) {
			case '+':
				push(head, plus(pop(head), pop(head)));
				break;
			
			case '-':
				push(head, minus(pop(head), pop(head)));
				break;
				
			case '*':
				push(head, mup(pop(head), pop(head)));
				break;
			
			case '/':
				push(head, div(pop(head), pop(head)));
				break;
			
			default:
				push(head, atoi(c));
		}
	}
	fclose(fp);
	return 0;
}

int isItValid(char c) {
	if(isalpha(c) || c != '+' || c != '-' || c != '/' || c != '*' )
		return -1;
	else
		return 1;
}