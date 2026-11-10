#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct stog{
	int number;
	struct stog *next;
}stog;

int push(int, stog *);
int pop(stog *);
int calkulator(int, int, char);
int citanjeDatoteke(char *, stog *);

int main(){

	stog head = {0, NULL};

	printf("Rezultat je %d\n", citanjeDatoteke("./file.txt", &head));

	return 0;
}


int push(int x, stog *p){

	stog *novi = (stog *)malloc(sizeof(stog));
	if (novi == NULL) return -1;

	novi->number = x;
	novi->next = p->next;
	p->next = novi;

	return 0;
}

int pop(stog *p){

	stog *temp = p->next;
	if (temp == NULL) return 1;

	int stog = temp->number;

	p->next = temp->next;
	free(temp);
	return stog;
}

int calkulator(int a, int b, char o){

	int rez = 0;
	switch (o)
	{
	case '+':
		rez = a + b;
		break;
	case '-':
		rez = a - b;
		break;
	case '*':
		rez = a * b;
		break;
	case '/':
		rez = a / b;
		break;
	}

	return rez;
}

int citanjeDatoteke(char *path, stog *p){

	char buffer[10], *end;
	int a = 0, b = 0;

	FILE *f = fopen(path, "r");
	if (f == NULL)
		return -1;

	while (!feof(f))
	{
		fscanf(f, "%s ", buffer);

		switch (buffer[0])
		{
		case '+':
		case '-':
		case '*':
		case '/':	
			b = pop(p);	
			a = pop(p);	
			push(calkulator(a, b, buffer[0]), p);
			break;
		default:
			push(strtol(buffer, &end, 10), p);
		}
	}

	fclose(f);
	return pop(p);
}