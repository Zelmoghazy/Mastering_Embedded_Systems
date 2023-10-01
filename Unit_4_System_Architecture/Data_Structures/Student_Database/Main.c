#include "Database.h"
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
    /* Load Previously Saved database state */
    s_db_load_file(db,"./data/saved.csv",'s');

    int id;
    float height;
    char name[NAME_SIZE];

    for(;;)
    {
        print_frame("Student database",50,FRAME_SYM,User_choice);
        
        switch(choice)
        {
            /* Insert a single student into the database */
            case '1':
                printf("Enter Student id : ");
                scanf("%d",&id);

                printf("Enter Student name : ");
                GET_STRING(name,NAME_SIZE);

                printf("Enter Student height : ");
                scanf("%f",&height);

                s_db_push_front(db,id,height,name);
                break;

            /* Remove a student using an id  */    
            case '2':
                printf("Enter Student id : ");
                scanf("%d",&id);

                s_db_remove_id(db,id);
                break;

            /* Find a student in the database */
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

            /* Delete all students */
            case '4':
                s_db_delete_all(db);
                break;

            /* Load students from a file, save current state first
               if file loads successfully done, if not reload previous state */
            case '5':
                bool contains = s_db_save_file(db,"./data/saved.csv",'s');
                if(s_db_load_file(db,"./data/students.csv",'n')){
                    printf("Students Loaded Sucessfully\n");
                }else{
                    printf("Error Couldnt Load Students !!\n");
                    s_db_delete_all(db);
                    if(contains){
                        s_db_load_file(db,"./data/saved.csv",'s');
                    }
                }
                break;

            /* Print all students in a database  */
            case '6':
                s_db_print(db);
                break;

            /* Save Current state of the database */
            case '7':
                if(s_db_save_file(db,"./data/out.csv",'n')){
                    printf("Students saved Sucessfully\n");
                }else{
                    printf("Error Couldnt Save Students !!\n");
                }
                break;

            /* Exit, Option to save the current state of the database  */
            case '8':
                char save;
                printf("Do you want to save current state of the database ? y/n : ");
                scanf(" %c",&save);
                if(save == 'y'){
                    if(s_db_save_file(db,"./data/saved.csv",'n')){
                        printf("Students saved Sucessfully\n");
                    }else{
                        printf("Error Couldnt Save Students !!\n");
                    }
                }
                exit(EXIT_SUCCESS);
                break;

            default: printf("Illegal choice\n");
        }
    }
}