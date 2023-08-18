#include "LinkedList.h"
#include "Utilities.h"

int main(void)
{
    student_database *db = s_db_new();

    int id;
    float height;
    char name[NAME_SIZE];

    char choice;

    for(;;)
    {
        printf("%s\n",MESSAGE_BOX);
        printf("Enter a choice :");
        scanf(" %c",&choice);
        switch(choice){
            case '1':
                printf("Enter Student id : ");
                scanf("%d",&id);

                printf("Enter Student name : ");
                GET_STRING(name,NAME_SIZE);

                printf("Enter Student height : ");
                scanf("%f",&height);

                s_db_pushfront(db,id,height,name);

                break;
            case '2':
                printf("Enter Student id : ");
                scanf("%d",&id);

                s_db_removeid(db,id);
                break;

            case '3':
                printf("Enter Student id : ");
                scanf("%d",&id);
                student *s = s_db_search(db,id);
                if(s == NULL){
                    printf("ID not found in database\n");
                }else{
                    s_db_formatstudent(s,true);
                }
                break;

            case '4':
                s_db_deleteall(student_database *DB);
                break;

            default: printf("Illegal choice\n");
        }

    }

}