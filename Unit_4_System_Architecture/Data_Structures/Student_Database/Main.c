#include "LinkedList.h"
#include "Utilities.h"

char choice;

void User_choice(void)
{
    printf("%s\n",MESSAGE_BOX);
    printf("Enter a choice : ");
    scanf(" %c",&choice);
}

int main(void)
{
    student_database *db = s_db_new();

    int id;
    float height;
    char name[NAME_SIZE];

    for(;;)
    {
        print_frame("Student database",50,FRAME_SYM,User_choice);
        
        switch(choice){
            case '1':
                printf("Enter Student id : ");
                scanf("%d",&id);

                printf("Enter Student name : ");
                GET_STRING(name,NAME_SIZE);

                printf("Enter Student height : ");
                scanf("%f",&height);

                s_db_push_front(db,id,height,name);

                break;
            case '2':
                printf("Enter Student id : ");
                scanf("%d",&id);

                s_db_remove_id(db,id);
                break;

            case '3':
                printf("Enter Student id : ");
                scanf("%d",&id);
                student *s = s_db_search(db,id);
                if(s == NULL){
                    printf("ID not found in database\n");
                }else{
                    s_db_format_student(s,true);
                }
                break;

            case '4':
                s_db_delete_all(db);
                break;

            case '5':
                if(s_db_load_file(db,"./data/students.csv")){
                    printf("Students Loaded Sucessfully\n");
                }else{
                    printf("Error Couldnt Load Students !!\n");
                }
                break;
            
            case '6':
                s_db_print(db);
                break;

            case '7':
                if(s_db_save_file(db,"./data/out.csv")){
                    printf("Students saved Sucessfully\n");
                }else{
                    printf("Error Couldnt Save Students !!\n");
                }
                break;

            case '8':
                exit(EXIT_SUCCESS);
                break;

            default: printf("Illegal choice\n");
        }
    }
}