#include <stdio.h>
#include <stdlib.h>
typedef struct node* pos;

struct node {
     int val;
     struct node* left;
     struct node* right;
};


pos searchBST(pos, int);
pos newNode(int);
pos insertIntoBST(pos, int);
pos minValueNode(pos);
pos deleteNode(pos, int);

void padding(char, int);
void structure(pos, int);

int main() {
	pos root = newNode(8);
	insertIntoBST(root, 3);
	insertIntoBST(root, 10);
	insertIntoBST(root, 12);
	insertIntoBST(root, 1);
	insertIntoBST(root, 4);
	insertIntoBST(root, 16);
	insertIntoBST(root, 1);
	searchBST(root, 5);
	deleteNode(root, 10);

	structure(root, 0);
	return 0;
}

pos newNode(int val) {
	pos temp = (pos)malloc(sizeof(struct node));
	if (temp == NULL) return NULL;
	temp->left = NULL;
	temp->right = NULL;
	temp->val = val;
	return temp;
}

pos searchBST(pos root, int val) {
	if (root) {
		if (root->val == val)
			return root;
		else if (root->val > val)
			return searchBST(root->left, val);
		else
			return searchBST(root->right, val);
	}
	return NULL;
}

pos insertIntoBST(pos root, int val) {

	if (root == NULL) return newNode(val);

	if (root->val > val) {
		root->left = insertIntoBST(root->left, val);
	}
	else {
		root->right = insertIntoBST(root->right, val);
	}

	return root;
}


pos minValueNode(pos node) {
	pos curr = node;

	while (curr->left != NULL) {
		curr = curr->left;
	}

	return curr;
}


pos deleteNode(pos root, int key) {
	if (root == NULL)
		return root;
	else {
		if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		} else {
			if (root->left == NULL) {
				pos temp = root->right;
				free(root);
				return temp;
			} else if (root->right == NULL) {
				pos temp = root->left;
				free(root);
				return temp;
			}

			pos temp = minValueNode(root->right);
			root->val = temp->val;
			root->right = deleteNode(root->right, temp->val);
		}

	}

	return root;
}

void padding(char ch, int n) {
	int i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void structure(pos root, int level) { //s gita

	if (root == NULL) {
		padding('\t', level);
		puts("~");
	}
	else {
		structure(root->right, level + 1);
		padding('\t', level);
		printf("%d\n", root->val);
		structure(root->left, level + 1);
	}
}
