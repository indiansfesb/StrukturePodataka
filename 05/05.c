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
int printResult(pos, pos, pos, pos);

int main(void) {
	int i = 0,
		count = 0;
	pos head1 = NULL;
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

	printResult(head1, head2, unijaResult, presjekResult);
	return 1;
	
}

pos allocateData() {
	pos temp = NULL;
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
	pos result = NULL;
	l1 = l1->next;
	l2 = l2->next;
	result = allocateData();
	if (result == NULL) {
		printf("mem err...");
		return NULL;
	}
	while (l1 != NULL) {
		addToList(result, l1->value);
		l1 = l1->next;
	}
	while (l2 != NULL) {
		addToList(result, l2->value);
		l2 = l2->next;
	}
	return result;
}

pos findPresjek(pos l1, pos l2) {
	l1 = l1->next;
	l2 = l2->next;
	pos result = NULL,
		start = NULL;
	result = allocateData();
	if (result == NULL) {
		printf("mem err, exiting....");
		return NULL;
	}
	start = l1;
	while (l2 != NULL) {
		while (l1 != NULL) {
			if (l1->value == l2->value) {
				//add l2->value to the list
				addToList(result, l1->value);
			}
			l1 = l1->next;
		}

		l1 = start;
		l2 = l2->next;
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
	while (result->next != NULL) {
		if (result->next->value == value) //:SSSSSSS
			return 2; //2 == duplicate code
		result = result->next;
	}
		
	result->next = temp;
	return 1;
}


int printResult(pos l1, pos l2, pos unija, pos presjek) {
	l1 = l1->next;
	l2 = l2->next;
	pos l1Ref, l2Ref = NULL;
	l1Ref = l1;
	l2Ref = l2;
	unija = unija->next;
	presjek = presjek->next;
	while (l1 != NULL) {
		printf("%d ", l1->value);
		l1 = l1->next;
	}
	printf(" justU ");
	while (l2 != NULL) {
		printf("%d ", l2->value);
		l2 = l2->next;
	}
	printf(" = ");
	while (unija != NULL){
		printf("%d, ", unija->value);
		unija = unija->next;
	}
	printf("\n");
	l1 = l1Ref;
	l2 = l2Ref;
	
	while (l1 != NULL) {
		printf("%d ", l1->value);
		l1 = l1->next;
	}
	printf(" upsidedownU ");
	while (l2 != NULL) {
		printf("%d, ", l2->value);
		l2 = l2->next;
	}
	printf(" = ");
	while (presjek != NULL) {
		printf("%d, ", presjek->value);
		presjek = presjek->next;
	}
	
	
	return 1;
}
