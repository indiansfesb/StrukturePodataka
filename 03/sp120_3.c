
//Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
//a) dinamièki dodaje novi element na poèetak liste, +
//b) ispisuje listu, +
//c) dinamièki dodaje novi element na kraj liste, +
//d) pronalazi element u listi (po prezimenu), +
//e) briše odreðeni element iz liste, +


//Prethodnom zadatku dodati funkcije:
//a) dinamièki dodaje novi element iza odreðenog elementa, + 
//b) dinamièki dodaje novi element ispred odreðenog elementa, + 
//c) sortira listu po prezimenima osoba,
//d) upisuje listu u datoteku, +
//e) èita listu iz datoteke. +




#define MAX_N 20
#define MAX_S 30

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char name[MAX_N];
	char surname[MAX_S];
	int YOB;
	struct node* next;
} node;

typedef struct node* pos;


//v3
void addAfterNode(pos);
void addBeforeNode(pos);
void saveToFile(pos);
void addToListFF(pos, int); //za readFromFie, prakticki addToListEnd ali za fp
void sortBySurname(pos);

pos readFromFile();



void addToListStart(pos);
void addToListEnd(pos);
void printList(pos);
void deleteElement(pos);

pos createEmptyList();
pos allocateStudentData();
pos findBySurname(pos);

int returnListCount(pos);


int main(void) {
	node head;
	head.next=NULL;
	
//	addToListStart(&head);
//	addToListEnd(&head);
//	addToListStart(&head);
//	addToListStart(&head);
//	addToListEnd(&head);
	pos	head2 = readFromFile(); // ove je pos jer je readfromfile napravljen da vraca pointer, pa se dosta toga ovdje zamjenjuje, salje se samo head2 umjesot head, i kod printa je -> a ne .; radi i kao node samo je lakse ovako ucitat sve
	printf("\n---\n");
	//printList(findBySurname(&head)); //printa od tog elementa, samo 4 testing
//	addAfterNode(&head);
//	deleteElement(&head);
	printList(head2->next);
//	printList(head.next);
	printf("\n---\n");
//	saveToFile(head.next);
//	pos head2=NULL;
	//head2 = readFromFile();
//	printList(head2->next);
	
//	addToListStart(&head);
//	addToListStart(&head);
//	addToListEnd(&head);
	
	sortBySurname(head2);
	printList(head2->next);
	printf("\n---\n");
	return 0;
}

int returnListCount(pos list) {
	int n=0;
	while(list->next != NULL) {
		n++;
		list = list->next;
	}
	return n;
}

pos createEmptyList(void) {
	pos head=NULL;
	head = (pos)malloc(sizeof(node)); //navodno je cast nepotreban i nepozeljan u c-u
	if(head) {
		head->next=NULL;
		return head;	
	} else {
		printf("err..");
		return ;
	}
}

pos allocateStudentData() {
	pos student=NULL;
	student = (pos)malloc(sizeof(node)); //cast thing
	if(student!=NULL)
		return student;
	else
		printf("err..");
		return ;
}

void addToListStart(pos list) {
	pos temp = NULL;
	temp = allocateStudentData();
	printf("Unesite ime prezime dob\n");
	scanf("%s %s %d", temp->name, temp->surname, &temp->YOB);
	temp->next = list->next;
	list->next = temp;
}

void addToListEnd(pos list) {
	pos curr=NULL;

	while(list->next!=NULL)
		list=list->next;
	
	pos temp = NULL;
	temp = allocateStudentData();
	printf("Unesite ime prezime dob\n");
	scanf("%s %s %d", temp->name, temp->surname, &temp->YOB);
	list->next=temp;
	temp->next=NULL;
}

void printList(pos list) {
	if(list==NULL)
		printf("Nema podataka.");
	else {
		int counter=1;
		while(list!=NULL) {
			printf("%d. %s %s %d\n", counter, list->name, list->surname, list->YOB);
			list=list->next;
			counter++;
		}		
	}
}

pos findBySurname(pos list) {
	if(list==NULL) {
		printf("Nema podataka.");
		return ;
	}
	char surname[MAX_S];
	printf("\nUnesite prezime: ");
	scanf("%s", surname);
	
	while(strcmpi(list->surname, surname)) //strmcpi nije case sensitive
		list=list->next;
		
	return list;
}

void deleteElement(pos list) {
	int n=0;
	int ln=0;
	
	pos prev = list;
		
	n = returnListCount(list);

	printList(list->next);
	printf("\nKoji element zelite obrisati?: ");
	
	while(ln==0) {
		scanf("%d", &ln);
		if(ln>n || ln<0) {
			printf("no h4x!!\n");
			ln=0;
		}
	}
	n=0;
	
	while(list!=NULL) {
		if(n==ln)
			break;
		prev=list;
		list=list->next;
		n++;
	}
	
	if(list==NULL)
		return ;
	prev->next = list->next;
	free(list);
	
}

void addAfterNode(pos list) {
	int n=0;
	int listCount=0;
	pos nextL = NULL;
	nextL = list;
	
	listCount = returnListCount(list);
	printList(list->next);
	printf("Nakon kojeg elementa zelite dodati novi?: ");
	
	while(n==0) {
		scanf("%d", &n);
		if(n>listCount) {
			printf("no h4x!!\n");
			n=0;
		}
	}
	
	listCount=0;
	
	while(list!=NULL) {
		if(n==listCount)
			break;
		nextL=list->next->next;
		list=list->next;
		listCount++;
	}
	
	pos temp = NULL;
	temp = allocateStudentData();
	scanf("%s %s %d", temp->name, temp->surname, &temp->YOB);

	list->next = temp;
	temp->next = nextL;
}

void addBeforeNode(pos list) {
	int n=0;
	int listCount=0;
	pos prev = NULL;
	prev = list;
	
	listCount = returnListCount(list);
	printList(list->next);
	printf("Prije kojeg elementa zelite dodati novi?: ");
	
	while(n==0) {
		scanf("%d", &n);
		if(n>listCount) {
			printf("no h4x!!\n");
			n=0;
		}
	}
	
	listCount=0;
	
	while(list!=NULL) {
		if(n==listCount)
			break;
		prev=list;
		list=list->next;
		listCount++;
	}
	
	pos temp = NULL;
	temp = allocateStudentData();
	scanf("%s %s %d", temp->name, temp->surname, &temp->YOB);
	temp->next = list;
	prev->next = temp;
}


void sortBySurname(pos list) { //bubble ali bi trebalo merge
	pos i, j, prev, temp, end;

	end = NULL;
	
	i = list;
	
	while (i->next != end) {
		prev = i;
		j = i->next;
		while(j->next!= end) {
			if(strcmp(j->surname, j->next->surname)>0) {
				temp = j->next;
				prev->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}

			prev=j;
			j = j->next;
		}
		end = j;
	}

}

void saveToFile(pos list) {
	FILE* fp=NULL;
	fp = fopen("student_list.txt", "w");
	while(list != NULL) {
		fprintf(fp, "%s %s - %d\n", list->name, list->surname, list->YOB);
		list = list->next;
	}
	fclose(fp);
}

pos readFromFile() {
	pos head=NULL;
	int i=0;
	int numberOfStudents=0;
	char buff[50]={"NULL"}; //krivo vjv
	head = createEmptyList();
	
	FILE* fp=NULL;
	fp = fopen("student_list.txt", "r");
	if(fp==NULL)
		return ;
	
	while(fgets(buff, sizeof(buff), fp)!=NULL)
		numberOfStudents++;
	for(i=1; i<=numberOfStudents; i++)
			addToListFF(head, i);
	
	fclose(fp);
	return head;
}

void addToListFF(pos list, int position) {
	pos curr=NULL;
	FILE* fp=NULL;
	char buff[50]={"NULL"};
	int posCounter=1;
	fp = fopen("student_list.txt", "r");
	
	if(fp==NULL)
		return ;
		
	while(list->next!=NULL)
		list=list->next;
	while(posCounter!=position) {
		fgets(buff, sizeof(buff), fp);
		posCounter++;
	}
	
	pos temp = NULL;
	temp = allocateStudentData();
	fscanf(fp, "%s %s %d", temp->name, temp->surname, &temp->YOB);
	list->next=temp;
	temp->next=NULL;
	fclose(fp);
}
