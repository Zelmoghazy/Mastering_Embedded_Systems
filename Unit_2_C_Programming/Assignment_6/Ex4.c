#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64
#define STUDENTS 5

#define get_string(str,MAX) fflush(stdin); \
                            fgets((str),MAX,stdin);\
                            (str)[strcspn((str),"\n")]=0;

typedef struct Student{
    char name[MAX_SIZE];
    int roll;
    float marks;
}Student;

void student_print(Student s1){
    printf("name: %s\n",s1.name);
    printf("roll: %d\n",s1.roll);
    printf("Marks: %.2f\n",s1.marks);
    printf("-------------------------\n");
}

int main()
{
    int i;
    Student s[STUDENTS];
    printf("Enter information of students:\n");
    for (i = 0; i < STUDENTS; i++){
        printf("For roll number %d\n",i+1);
        s[i].roll = i+1;

        printf("Enter name : ");
        get_string(s[i].name,MAX_SIZE);
        /*  
        fflush(stdin);
        fgets(s[i].name, MAX_SIZE, stdin);
        s[i].name[strcspn(s[i].name,"\n")] = 0;
        */
        printf("Enter marks: ");
        scanf("%f",&(s[i].marks));
    }

    printf("\nDisplaying Information :\n");
    printf("-------------------------\n");

    for (i = 0; i < STUDENTS; i++){
        student_print(s[i]);
    }

    system("pause");
    return 0;
}