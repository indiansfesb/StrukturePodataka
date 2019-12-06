#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

typedef struct node* pos;

typedef struct node {
	float value;
	struct node* next;
} node;


pos allocateData();

int calcResult(pos);
int isItValid(char);
int push(pos, float);
float pop(pos);

float plus(float, float);
float minus(float, float);
float mup(float, float);
float divi(float, float);

int main(void) {
	pos head = allocateData();
	int result = -1;
	result = calcResult(head);
	if (result != 0) {
		printf("err with calcResult, wrong input");
		return -1;
	}


	return 0;
}

pos allocateData() {
	pos node = NULL;
	node = (pos)malloc(sizeof(pos));
	node->next = NULL;
	if (node == NULL)
		return NULL;
	else
		return node;

}

int calcResult(pos head) {

	FILE* fp = NULL;
	char c = 0;
	fp = fopen("input.txt", "r");
	if (fp == NULL)
		return -1;
	while (c  != EOF) {
		//if (!isItValid)
			//return -1;
		c = fgetc(fp);
		
		switch (c) {
		case ' ':
			break;
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
			push(head, divi(pop(head), pop(head)));
			break;

		default:
			push(head, c - '0');
		}
	}
	fclose(fp);
	return 0;
}
/*
int isItValid(char c) {
	if (!isdigit(atoi(c)) || c != '+' || c != '-' || c != '/' || c != '*')
		return -1;
	else
		return 1;
}
*/

int push(pos head, float val) {
	pos temp = allocateData();
	if (temp == NULL)
		return -1;
	temp->value = val;
	temp->next = head->next;
	head->next = temp;
	return 1;
}


float pop(pos head) {
	float a = 0;
	a = head->next->value;
	pos temp = head->next;
	head->next = head->next->next;
	free(temp);
	return a;
} // 2 4 -


float plus(float a, float b) {
	return a+b;
}
float minus(float a, float b) {
	return a - b;
}
float mup(float a, float b) {
	return a * b;
}
float divi(float a, float b) {
	return a / b;
}
