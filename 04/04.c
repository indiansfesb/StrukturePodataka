#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#define N 1024

typedef struct node* pos;


typedef struct node {
	int koef;
	int eksp;
	pos next;
} node;

int addToList(pos, pos);
int readFromList(pos, const char*);
int addToListEnd(pos, pos);
int mulPolyHelper(pos, pos);
int printResult(pos, pos, pos);

pos allocateData();
pos createEmptyList();
pos sumPoly(pos, pos);
pos mulPoly(pos, pos);

int main(void) {
	pos poly1 = createEmptyList();
	pos poly2 = createEmptyList();
	if (!readFromList(poly1, "input.txt"))
		return -1;
	if (!readFromList(poly2, "input2.txt"))
		return -1;

	pos sumResult = sumPoly(poly1, poly2);
	if (sumResult == NULL) {
		printf("err...");
		return -1;
	}

	pos mulResult = mulPoly(poly1, poly2);
	if (mulResult == NULL) {
		printf("err...");
		return -1;
	}
	printResult(poly1, poly2, sumResult);
	printResult(poly1, poly2, mulResult);


	return 1;
}
//5x^2 + 2x^1 + 2


pos allocateData() {
	pos temp = 0;
	temp = (pos)malloc(sizeof(node));
	if (temp == NULL) {
		printf("out of mem, data not allocated");
		return NULL;
	}
	return temp;
}

int readFromList(pos head, const char* filename) {
	pos temp = NULL;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if(fp == NULL)
		return 0;
	temp = allocateData();
		while (fscanf(fp, "%d %d", &temp->koef, &temp->eksp) != EOF) {
			addToList(head, temp);
			temp = allocateData();
		}
	
	if (fp)
		fclose(fp);
	free(temp);
	return 1;

}

pos createEmptyList(void) {
	pos head = NULL;
	head = (pos)malloc(sizeof(node));
	if (head) {
		head->next = NULL;
		return head;
	}
	else {
		printf("err..");
		return NULL;
	}
}

int addToList(pos head, pos temp) {
	pos next = allocateData();
	temp->next = NULL;
	if (head->next == NULL) {
		head->next = temp;
		return 1;
	}
	
	while (head->next != NULL && head->next->eksp < temp->eksp) { // 2 *4* 5 *1* 4 *3* 8 *2* 7 *5* 
		head = head->next;
		next = head->next;
	}
		
	if (head->next != NULL && head->eksp < head->next->eksp) {
		next = head->next;
		head->next = temp;
		temp->next = next;
	} //check for add before
	head->next = temp;
	temp->next = next;
	

	return 1;

}

pos sumPoly(pos poly1, pos poly2) {
	poly1 = poly1->next; //head removal
	poly2 = poly2->next;
	pos sumResult = createEmptyList();
	pos temp[N] = {NULL};
	int i =0,
		j = 0;
	pos next = NULL;
	if (poly1->next != NULL && poly2->next != NULL) {
		while (poly1 != NULL) { //diff size fix
			if (poly1->eksp == poly2->eksp) {
				temp[i] = allocateData();
				temp[i]->eksp = poly1->eksp;
				temp[i]->koef = poly1->koef + poly2->koef;
				temp[i]->next = NULL;
				addToListEnd(sumResult, temp[i]);
			} else if(poly1->eksp != poly2->eksp) {
				temp[i] = poly2;
				addToListEnd(sumResult, temp[i]);
				i++;
				temp[i] = poly1;
				addToListEnd(sumResult, temp[i]);
			}
			
			i++;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
	}
	return sumResult;
}

pos mulPoly(pos poly1, pos poly2) {
	pos mulResult = createEmptyList();
	poly1 = poly1->next;
	poly2 = poly2->next;
	pos temp = NULL;
	pos reset = poly2;
	while (poly1 != NULL) {
		while (poly2 != NULL) {
			temp = allocateData();
			temp->eksp = poly1->eksp + poly2->eksp;
			temp->koef = poly1->koef * poly2->koef;
			if (mulPolyHelper(mulResult, temp) == -1) {
				printf("err...");
				return NULL;
			}
			
			poly2 = poly2->next;
		}
		poly2 = reset;
		poly1 = poly1->next;
	}

	return mulResult;
}

int addToListEnd(pos sumResult, pos temp) {
	if (!sumResult && !temp)
		return -1;
	while (sumResult->next != NULL)
		sumResult = sumResult->next;
	sumResult->next = temp;
	return 1;
}

int mulPolyHelper(pos mulResult, pos temp) {
	if (temp == NULL)
		return -1;
	if (mulResult->next == NULL) {
		mulResult->next = temp;
		temp->next = NULL;
		return 1;
	}
	while (mulResult->next != NULL) {
		if (mulResult->eksp == temp->eksp) {
			mulResult->koef = mulResult->koef + temp->koef;
			return 1;
		}
		if(mulResult->next != NULL)
			mulResult = mulResult->next;
	}
	if (mulResult->eksp == temp->eksp) {
		mulResult->koef = mulResult->koef + temp->koef;
		return 1;
	}
	mulResult->next = temp;
	temp->next = NULL;

	return 1;
		
}

int printResult(pos poly1, pos poly2, pos result) {
	poly1 = poly1->next;
	poly2 = poly2->next;
	result = result->next;
	pos polyTemp = poly1;
	int polyTempC = 0;
	pos resultTemp = result;
	int resultTempC = 0;
	while (polyTemp != NULL) {
		polyTempC++;
		polyTemp = polyTemp->next;
	}
	while (resultTemp != NULL) {
		resultTempC++;
		resultTemp = resultTemp->next;
	}
	printf("(");
	while (poly1 != NULL) {
		if (poly1->next == NULL) {
			printf(" %dx^%d", poly1->koef, poly1->eksp);
			poly1 = poly1->next;
		}
		else {
			printf(" %dx^%d +", poly1->koef, poly1->eksp);
			poly1 = poly1->next;
		}
	}
	if (resultTempC > polyTempC)
		printf(") * (");
	else
		printf(") + (");
	while (poly2 != NULL) {
		if (poly2->next == NULL) {
			printf(" %dx^%d", poly2->koef, poly2->eksp);
			poly2 = poly2->next;
		}
		else {
			printf(" %dx^%d +", poly2->koef, poly2->eksp);
			poly2 = poly2->next;
		}

	}
	printf(") = ");
	while (result != NULL) {
		if (result->next == NULL) {
			printf(" %dx^%d", result->koef, result->eksp);
			result = result->next;
		}
		else {
			printf(" %dx^%d +", result->koef, result->eksp);
			result = result->next;
		}
	}
	printf("\n-----------------------------------\n");
	return 1;
}
