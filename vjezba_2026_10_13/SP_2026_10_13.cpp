#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osoba {
	char* name;
	char* surname;
	int birth_year;

	struct osoba* next;
};

int addToStart(char*, char*, int, osoba*);
int addToEnd(char*, char*, int, osoba*);
osoba* findBySurname(char*, osoba*);
int printout(osoba*);
int erase(char*, osoba*);

int main() {
	int value = 0;

	osoba* head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	char a[] = "aaaa";
	char b[] = "ba";
	char c[] = "c";
	//C++ argument of type const char* is incompatible with parameter of type  char* 
	//if u care find other solutiuon

	value = addToStart(a, a, 1939, head);
	if (value) return value;
	value = addToStart(b, b, 2001, head);
	if (value) return value;
	value = addToEnd(c, c, 2077, head);
	if (value) return value;

	printout(head->next);

	char surnameToFind[10];
	printf("\nUnesite prezime koje trazite: ");
	char scanArguments = scanf("%s", surnameToFind);
	getc(stdin);

	osoba* temp = findBySurname(surnameToFind, head->next);
	if (!temp) {
		printf("Nepostoji osoba s tim prezimenom.\n");
	}
	else {
		printf("Podudaranost pronadena:%s %s, rodena %d. godine\n", temp->name, temp->surname, temp->birth_year);
	}

	value = erase(surnameToFind, head);
	if (value) return value;
	printf("Izbrisana je osoba sa pretrazenim prezimenom.\n");
	printout(head->next);

	printf("\n");
	free(head);
	getchar();
	return 0;
}

int addToStart(char* fname, char* lname, int birth_year, osoba* p) {
	osoba* novo = (osoba*)malloc(sizeof(osoba));
	if (!novo) return -1;

	novo->name = fname;
	novo->surname = lname;
	novo->birth_year = birth_year;
	novo->next = p->next;

	p->next = novo;

	return 0;
}

int printout(osoba* p) {
	printf("\n");
	while (p) {
		printf("%s %s %d\n", p->name, p->surname, p->birth_year);
		p = p->next;
	}

	return 0;
}

int addToEnd(char* fname, char* lname, int birth_year, osoba* p) {
	while (p->next) {
		p = p->next;
	}

	addToStart(fname, lname, birth_year, p);

	return 0;
}

osoba* findBySurname(char* lname, osoba* p) {
	while (p) {
		if (!strcmp(p->surname, lname)) break;
		p = p->next;
	}

	return p;
}

int erase(char* lname, osoba* p) {
	if (!p->next) return -1;

	while (p->next) {
		if (!strcmp(p->next->surname, lname)) break;
		p = p->next;
	}

	osoba* temp = p->next;
	p->next = temp->next;
	free(temp);

	return 0;
}