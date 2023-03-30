#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *valor;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
    Node *rear;
} List;

typedef struct student
{
    char nome[21];
    float n1, n2, average;
} Student;

List *CreateList();
void InsertAtStart(List *list, void *valor);
void InsertAtEnd(List *list, void *valor);
void InsertAtPosition(List *list, void *valor, int pos);
Student *CreateStudent(char nome[], float n1, float n2);
void PrintStudents(List *list);
void *GetAtPosition(List *list, int pos);
void *GetAtStart(List *list);
void *GetAtEnd(List *list);

List *CreateList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->rear = NULL;
    return list;
}

void InsertAtStart(List *list, void *valor)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->valor = valor;
    if (list->head == NULL)
    {
        newNode->next = NULL;
        list->head = newNode;
        list->rear = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head = newNode;
    }
}

void InsertAtEnd(List *list, void *valor)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->valor = valor;
    newNode->next = NULL;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->rear = newNode;
    }
    else
    {
        list->rear->next = newNode;
        list->rear = newNode;
    }
}

void InsertAtPosition(List *list, void *valor, int pos)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->valor = valor;
    if (list->head == NULL)
    {
        newNode->next = NULL;
        list->head = newNode;
        list->rear = newNode;
    }
    else
    {
        Node *current = list->head;
        int i = 1;
        while (i < pos)
        {
            current = current->next;
            i++;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Student *CreateStudent(char nome[], float n1, float n2)
{
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->nome, nome);
    student->n1 = n1;
    student->n2 = n2;
    student->average = (n1 + n2) / 2;
    return student;
}

void PrintStudents(List *list)
{
    if (list->head != NULL)
    {
        Node *current = list->head;
        while (current != NULL)
        {
            Student *student = (Student *)current->valor;
            printf("Nome: %s \t Nota 1: %.2f \t Nota 2: %.2f \t Media: %.2f \n", student->nome, student->n1, student->n2, student->average);
            current = current->next;
        }
    }
}

void *GetAtPosition(List *list, int pos)
{
    if (list->head != NULL)
    {
        Node *current = list->head;
        int i = 1;
        while (i < pos)
        {
            current = current->next;
            i++;
        }
        return current->valor;
    }
    else
    {
        return NULL;
    }
}

void *GetAtStart(List *list)
{
    if (list->head != NULL)
    {
        return list->head->valor;
    }
    else
    {
        return NULL;
    }
}

void *GetAtEnd(List *list)
{
    if (list->rear != NULL)
    {
        return list->rear->valor;
    }
    else
    {
        return NULL;
    }
}

int main()
{
    List *list = CreateList();
    Student *student;

    student = CreateStudent("Maria", 7.5, 8.5);
    InsertAtStart(list, student);

    student = CreateStudent("Pedro", 10, 10);
    InsertAtStart(list, student);

    student = CreateStudent("Jao", 9.5, 10);
    InsertAtEnd(list, student);

    student = CreateStudent("Bastiao", 8.5, 9.5);
    InsertAtEnd(list, student);

    student = CreateStudent("Wesley", 9, 9);
    InsertAtPosition(list, student, 3);

    student = CreateStudent("Batata", 8, 8);
    InsertAtPosition(list, student, 4);

    PrintStudents(list);
}