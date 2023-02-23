#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
  char name[50];
  float n1;
  float n2;
  float average;
};

typedef struct Student Students;
void readStudents(Students *, int);
void calculateAverage(Students *, int);
void printStudents(Students *, int);

int main()
{
    int n;
    printf("\nHow many students do you want to enter? \n");
    scanf("%d", &n);

    Students *students;
    students = (Students*) malloc(n * sizeof(Students));

    if (students == NULL) {
        printf("Failed to allocate memory for students!\n");
        return -1;
    }

    readStudents(students, n);
    calculateAverage(students, n);
    printStudents(students, n);

    free(students);

    return 0;
}

void readStudents(Students *students, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter the name of the student %d: ", i + 1);
        scanf("%s", &students[i].name);
        printf("Enter the first grade: ");
        scanf("%f", &students[i].n1);
        printf("Enter the second grade: ");
        scanf("%f", &students[i].n2);
    }
    printf("\n");
}

void calculateAverage(Students *students, int n)
{
    for (int i = 0; i < n; i++)
    {
        students[i].average = (students[i].n1 + students[i].n2) / 2;
    }
}

void printStudents(Students *students, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Student %d %s has average %.2f \n", i+1, students[i].name, students[i].average);
        printf("Note 1: %.1f \n" , students[i].n1);
        printf("Note 2: %.1f \n" , students[i].n2);
        printf("\n");
    }
}