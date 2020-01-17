/*
Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi hash tablicu sa zasebnim redovima.
Tablica ima 11 mjesta, a funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena
i zatim računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice.
Studenti s istim ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu
(naglasiti na kojem ključu se nalaze koji podaci) te ponuditi mogućnostda se za
određenog studenta (prezime i ime) ispiše njegov matični broj
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX (50)

typedef struct _node {
	struct _node* nextNode;
	char fname[MAX];
	char lname[MAX];
	int mnum;
}NODE;
typedef struct _node* Pos;

typedef struct hashT {
	int tableSize;
	Pos list;
}hashTable;
typedef struct hashT* ht;

ht createHT(int);
int hash(char*, int);
int addStudent(ht, char*, char*, int);
int printTable(ht);
int printNode(Pos, int);
int findMnum(ht table, char* fname, char* lname);
int main() {
	ht table = createHT(11);
	int opt = 0;
	char fname[25];
	char lname[25];
	int mnum;
	while (opt != '-1') {
		printf("do osmething\n1.add student\n2.find mnum\n3. print table\n0.exit\n");
		scanf("%d", &opt);
		switch (opt) {
		case 1:
			printf("tye in name, last name and mnum\n");
			scanf("%s %s %d", fname, lname, &mnum);
			addStudent(table, fname, lname, mnum);
			break;
		case 2:
			printf("enter name and last name\n");
			scanf("%s %s", fname, lname);
			printf("mnum is %d\n", findMnum(table, fname, lname));
			break;
		case 3:
			printTable(table);
			break;
		case 0:
			opt = '-1';
			break;
		default:
			break;


		}
	}

	system("pause");
	return 0;
}
ht createHT(int tblsize)
{
	int i = 0;
	ht table = (ht)malloc(sizeof(hashTable));
	if (table == NULL) {
		return NULL;
	}
	table->list = (Pos)malloc(sizeof(NODE) * tblsize);
	if (table->list == NULL) {
		return NULL;
	}
	for (i = 0; i < tblsize; i++) {
		Pos node = &table->list[i];
		node->nextNode = NULL;
	}
	table->tableSize = tblsize;
	return table;
}
int hash(char* str, int tabsize) {
	int hashV = 0;
	int counter = 0;
	while (*str != '\0' && counter < 5) {
		hashV += *str++;
		counter++;
	}
	return hashV % tabsize;
}
int addStudent(ht table, char* fname, char* lname, int mnum) {
	if (table == NULL)return -1;
	Pos hpos = &table->list[hash(lname, table->tableSize)];
	Pos nodeptr = hpos;
	Pos stu = (Pos)malloc(sizeof(NODE));
	if (stu == NULL)return -1;
	strcpy(stu->fname, fname);
	strcpy(stu->lname, lname);
	stu->mnum = mnum;
	stu->nextNode = NULL;
	while (nodeptr->nextNode) {
		if (strcmp(lname, nodeptr->nextNode->lname) < 0) {
			stu->nextNode = nodeptr->nextNode;
			nodeptr->nextNode = stu;
			return 0;
		}
		else if (strcmp(lname, nodeptr->nextNode->lname) == 0) {
			if (strcmp(fname, nodeptr->nextNode->fname) < 0) {
				stu->nextNode = nodeptr->nextNode;
				nodeptr->nextNode = stu;
				return 0;
			}
		}
		else {
			nodeptr = nodeptr->nextNode;
		}
	}
	if (nodeptr->nextNode == NULL) {
		nodeptr->nextNode = stu;
	}
	return 0;

}
int printTable(ht table) {
	int i = 0;
	Pos node = NULL;
	for (i = 0; i < table->tableSize; i++) {
		node = table->list[i].nextNode;
		while (node) {
			printNode(node, i);
			node = node->nextNode;
		}
	}
	return 0;
}
int printNode(Pos node, int index) {
	if (node) {
		printf("%d. %s %s %d\n", index, node->fname, node->lname, node->mnum);
		return 0;
	}
	return -1;
}
int findMnum(ht table, char* fname, char* lname) {
	Pos row = &table->list[hash(lname, table->tableSize)];
	Pos nodeptr = row->nextNode;
	while (nodeptr) {
		if (strcmp(lname, nodeptr->lname) == 0 && strcmp(fname, nodeptr->fname) == 0) {
			return nodeptr->mnum;
		}
		else {
			nodeptr = nodeptr->nextNode;
		}
	}
	return -1;
}