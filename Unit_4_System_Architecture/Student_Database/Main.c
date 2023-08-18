#include "LinkedList.h"
#include "Utilities.h"

int main(void)
{
    
    student_database *db = s_db_new();

    int id;
    float height;
    char name[NAME_SIZE];

    char choice;
    char *MessageBox = 
"*******************************************************\n\
    Choose one of the following Options :               \n\
        1: Add a student                                \n\
        2: Delete a student                             \n\
        3: View a student                               \n\
        4: Delete all                                   \n\
********************************************************\n";

    for(;;)
    {
        printf("%s\n",MessageBox);
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

            case '3':
                printf("Enter Student id : ");
                scanf("%d",&id);
                student *s = s_db_search(db,id);
                if(s == NULL){
                    printf("ID not found in database\n");
                }else{
                    s_db_print(db);
                }
        }

    }

}