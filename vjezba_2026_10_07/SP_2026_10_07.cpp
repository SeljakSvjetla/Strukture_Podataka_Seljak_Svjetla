#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximum_points 100

typedef struct student{
	char name[20];
	char surname[20];
	int points;
} _student;

int numberOfStudents(char*);  
int readingStudentData(char*, _student*); 
double calculatingRelativePoints(int);
int printout(_student*);

int main() {
	int br_stud=0; 
	int i=0;

	br_stud = numberOfStudents("./datoteka.txt");

	_student* students = (_student*)malloc(br_stud * sizeof(_student));
	if (students == NULL) {
		return -1;
	}

	readingStudentData("./datoteka.txt", students);

	for (i = 0; i < br_stud; i++) {
		printout(students+i);
	}
	putc('\n',stdout);
	free(students);

	return 0;
}

int numberOfStudents(char* path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		fclose(file);
		return -1;
	}

	int i = 0;
	while (!feof(file)) {
		if(fgetc(file)=='\n') i++;
	}
	
	fclose(file);

	return i;
}

int readingStudentData(char* path, _student* students) {
	FILE* file = fopen(path, "r");
	int i=0;

	if (file == NULL) {
		fclose(file);
		return -1;
	}

	while (!feof(file)) {
		fscanf(file, "%s %s %d ", students[i].name, students[i].surname, &students[i].points);
		i++;
	}

	fclose(file);

	return 0;
}

double calculatingRelativePoints(int score) {
	return (double)score / maximum_points * 100;
}

int printout(_student* s) {
	printf("%s %s %d/100 %.2f%%\n", s->name, s->surname, s->points, calculatingRelativePoints(s->points));

	return 0;
}