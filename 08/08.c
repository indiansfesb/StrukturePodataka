#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
//n-ary tree
//                     R
//                     |
//                     B -- C -- D
//                     |         |
//                     E -- F    G
//
//
//
//
//



typedef struct node* pos;
typedef struct node {
	char* name;
	pos firstC; //first child
	pos nextS; //next sibling
} node;

typedef struct stack* posS;
typedef struct stack {
	pos node;
	posS next; 
} stack;


posS allocateDataS();
pos push(posS stack, pos node);
pos pop(posS stack);

pos allocateData(char* name);
pos add_child(pos, char*);
pos add_sibling(pos, char*);
//kada se radi novi "dir", tad uvijek ide add child, add_sibling je iskljucivo helper tu koji ako postoji 1 child dodaje "siblinga"
//stack je za cd "dir"; kad se cd u neki dir to ide na stog; pr. root:\a\fesb\racunarstvo\strukture | a->fesb->racunarstvo->strukture ; 
//i sad kada se udara mkdir, stog se poppa i to ide u funkciju add_child(pop, dirName), ali bi se valjda trebalo i pushat natrag jer smo jos uvijek u istom dir, osim 

//wip
pos changeDir(pos node, char* name);

int main(void) {
	pos currentDir = NULL;
	char dirName[N] = "C";
	pos root = NULL;
	posS stack = allocateDataS();
	root = allocateData("root"); //             // zove se samo add_child za dodavanje novog dira
	currentDir = root;
	add_child(currentDir, "prvi_dir"); //             // i onda moram cd u taj dir, i prilikom cd-a se se pusha na stack, a prilikom cd.. se popa
	add_child(currentDir, "drugi dir");
	add_child(currentDir, "treci dir");
	currentDir = push(stack, changeDir(currentDir, "treci dir")); // cd "treci dir" ->
	add_child(currentDir, "cetvrti dir u trecem");
	return 0;
}


pos changeDir(pos currentDir, char* name) {
	int flag = 0;
	while (strcmp(currentDir->name, name) != 0)  { //?
		if (!flag) {
			currentDir = currentDir->firstC;
			flag = 1;
		}
		else {
			currentDir = currentDir->nextS;
		}
	}
	return currentDir;
}


pos allocateData(char* name) {
	pos temp = NULL;
	temp = (pos)malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("mem err, returning null...");
		return NULL;
	}
	temp->name = name;
	temp->firstC = NULL;
	temp->nextS = NULL;
	return temp;
}

pos add_child(pos node, char* name) {
	if (node == NULL)
		return NULL;

	if (node->firstC)
		return add_sibling(node->firstC, name);
	else
		return (node->firstC = allocateData(name));
}

pos add_sibling(pos node, char* name) {
	if (node == NULL)
		return NULL;

	while (node->nextS)
		node = node->nextS;

	return (node->nextS = allocateData(name));
}

pos push(posS stack, pos node) {
	posS temp = NULL;
	temp = allocateDataS();

	if (temp == NULL)
		return NULL;
	else
		temp->node = node;
	if (stack->next == NULL) {
		stack->next = temp;
		return node;
	}
	while (stack->next != NULL) {
		stack = stack->next;
	}
	stack->next = temp;

	return node;
}

pos pop(posS stack) {
	pos rtrn = NULL;
	if (stack->next == NULL)
		return NULL;

	while (stack->next->next != NULL) {
		stack = stack->next;
	}
	rtrn = stack->next->node;
	free(stack->next);
	stack->next = NULL;
	return rtrn;
}


posS allocateDataS() {
	posS temp = NULL;
	temp = (posS)malloc(sizeof(stack));
	if (temp == NULL) {
		printf("mem err, returning null...");
		return NULL;
	}
	temp->next = NULL;
	return temp;
}
