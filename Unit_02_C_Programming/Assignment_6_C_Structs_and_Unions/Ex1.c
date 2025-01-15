#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64

typedef struct Student{
    char name[MAX_SIZE];
    int roll;
    float marks;
}Student;

void student_print(Student s1){
    printf("name: %s\n",s1.name);
    printf("roll: %d\n",s1.roll);
    printf("Marks: %.2f\n",s1.marks);
}

int main()
{
    Student s1;
    printf("Enter information of students:\n");
    printf("Enter name: ");
    fgets(s1.name, MAX_SIZE, stdin);
    s1.name[strcspn(s1.name,"\n")] = 0;
    printf("Enter roll number: ");
    scanf("%d",&s1.roll);
    printf("Enter marks: ");
    scanf("%f",&s1.marks);
    printf("\nDisplaying Information :\n");
    student_print(s1);
    system("pause");
    return 0;
}