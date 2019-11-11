#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996) //sscanf warning
#pragma warning(disable:6031) //scanf return value ignore warning
#define _CRT_SECURE_NO_WARNINGS

typedef struct data* pos;

typedef struct data {
	int value;
	pos next;
} data;

pos allocateData();
pos findUnija(pos, pos);
pos findPresjek(pos, pos);

int sortedEntry(pos);
int addToList(pos, int);

int main(void) {
	int i = 0,
		count = 0;
	pos head1= NULL;
	head1 = allocateData();
	pos head2 = NULL;
	head2 = allocateData();


	pos unijaResult = NULL;
	pos presjekResult = NULL;

	while (count <= 0 && count < INT_MAX) {
		printf("How many elements in L1? ");
		scanf("%d", &count);
	}

	for (i = 0; i < count; i++) {
		sortedEntry(head1);
	}
	count = 0;
	while (count <= 0 && count < INT_MAX) {
		printf("How many elements in L2? ");
		scanf("%d", &count);
	}
	for (i = 0; i < count; i++) {
		sortedEntry(head2);
	}

	unijaResult = findUnija(head1, head2);

	presjekResult = findPresjek(head1, head2);

	return 1;
}

pos allocateData() {
	pos temp = 0;
	temp = (pos)malloc(sizeof(data));
	if (temp == NULL) {
		printf("out of mem, data not allocated");
		return NULL;
	}
	temp->next = NULL;
	return temp;
}

int sortedEntry(pos head) {
	pos temp = NULL,
		next = NULL,
		prev = NULL;
	temp = allocateData();
	if (temp == NULL) {
		printf("no memory, exiting...");
		return -1;
	}

	prev = head;
	
	printf("Enter a value: ");
	scanf("%d", &temp->value);
	
	if (head->next == NULL) {
		head->next = temp;
		return 1;
	}

	while (head->next != NULL) {
		if (temp->value < head->next->value && temp->value != head->value) {
			next = head->next;
			prev->next = temp;
			temp->next = next;
			return 1;
		}
		prev = head;
		head = head->next;
	}
	head->next = temp;

	return 1;
}

pos findUnija(pos l1, pos l2) {
	pos result = NULL,
		start = NULL;
	int flag = 0;
	result = allocateData();
	if (result == NULL) {
		printf("mem err, exiting....");
		return NULL;
	}
	start = l1;
	l1 = l1->next;
	while (l1 != NULL) {
		addToList(result, l1->value);
		l1 = l1->next;
	}
	l1 = start;
	while (l2 != NULL) {
		while (l1 != NULL) {
			if (l2->value == l1->value && flag == 0) {
				//add l2->value to the list
				addToList(result, l2->value);
				flag = 1;
			}
			l1 = l1->next;
		}
		flag = 0;
		
		l1 = start;
		l2 = l2->next;
	}


	return result;
}

pos findPresjek(pos l1, pos l2) {
	pos result = NULL;
	if (result = allocateData() == NULL) {
		printf("err...");
		return NULL;
	}



	return result;
}


int addToList(pos result, int value) {
	pos temp = NULL;
	temp = allocateData();
	if (temp == NULL) {
		printf("mem err, exiting...");
		return -1;
	}
	temp->value = value;
	while (result->next != NULL)
		result = result->next;
	result->next = temp;
	return 1;
}
