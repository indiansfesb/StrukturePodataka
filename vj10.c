/*
Napisati program koji iz datoteke čita postfiks izraz i zatimstvara stablo proračuna.
Iz gotovog stabla proračuna upisati u datoteku infiks izraz
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree_node* tnode;
typedef struct tree_node {
	char* el;
	tnode left;
	tnode right;
}treenode;

typedef struct stack_node* snode;

typedef struct stack_node {
	tnode node;
	snode next;
}stacknode;

snode createStack();
snode allocateSNode(tnode);
int push(snode,snode);
tnode pop(snode);
tnode addToTree(snode stack, char* tempElem);
void printTree(tnode root);
bool isLeaf(tnode node);
bool isNum(char* str);

int main(int argc, char* argv) {
	snode stack = createStack();
	tnode root = NULL;
	char fileName[25] = "potato.txt";
	int ret = 0;
	char tempElem[10] = {0};
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) return NULL;
	while (ret != -1) {
		ret = fscanf(fp, "%s", &tempElem);
		if (ret == 1) {
			root=addToTree(stack, tempElem);
		}
		if (ret == 0) {
			printf("ret is 0\n");
		}
	}
	printTree(root);
	fclose(fp);
	system("pause");
	return 0;
}
bool isNum(char* str) {
	int a = 0;
	return sscanf(str, "%d",&a) > 0 ? true:false;
}
snode allocateSNode(tnode tnode) {
	snode node = NULL;
	node = (snode)malloc(sizeof(stacknode));
	if (node) {
		if (tnode) {
			node->node = tnode;
			node->next = NULL;
			return node;
		}
		node->node = NULL;
		node->next = NULL;
		return node;
	}
	return NULL;
	
}
snode createStack() {
	snode node = NULL;
	node = allocateSNode(NULL);
	if (node) {
		return node;
	}
	return NULL;
}
int push(snode stack,snode node) {
	if (stack && node) {
		node->next = stack->next;
		stack->next = node;
		return 0;
	}
	return -1;
}
tnode pop(snode stack) {
	if (stack) {
		snode nodeToRemove = stack->next;
		tnode tnode = stack->next->node;

		stack->next = stack->next->next;
		free(nodeToRemove);
		return tnode;
	}
	return NULL;
}
tnode allocateTNode(char* el) {
	tnode temp = (tnode)malloc(sizeof(treenode));
	if (temp == NULL) return NULL;
	char* newEl=(char*)malloc(10);
	if (newEl) {
		strcpy(newEl, el);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->el = newEl;
	return temp;
}

tnode addToTree(snode stack,char* tempElem) {
	if (isNum(tempElem)) {
		push(stack, allocateSNode(allocateTNode(tempElem)));
		return NULL;
	}
	else {
		tnode el1 = pop(stack);
		tnode el2 = pop(stack);
		tnode newRoot = allocateTNode(tempElem);
		newRoot->left = el1;
		newRoot->right = el2;
		push(stack, allocateSNode(newRoot));
		return newRoot;
		
	}
}
void printTree(tnode root) {
	if (root != NULL) {
		if (isLeaf(root))
			printf("%s",root->el);
		else {
			printf("(");
			printTree(root->left);
			printf("%s", root->el);
			printTree(root->right);
			printf(")");
		}
	}

}
bool isLeaf(tnode node) {
	if ((node->left && node->right) == NULL) {
		return true;
	}
	return false;
}
