#include "Database.h"
#include "Utilities.h"
#include "include/Utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    char    choice;
    char    tmp[NAME_SIZE];
    char    *endptr;

    int     id;
    float   height;
    char    name[NAME_SIZE];

    int index = 0;

    /* Create a new Student Database */
    student_database *db = s_db_new();

    /* Load Previously Saved Database State */
    s_db_load_file(db,"./data/saved.csv",'s');

    for(;;)
    {
        /* User Choice Dialog Box */
        print_frame("Student database",50,FRAME_SYM,&choice);
        
        switch(choice)
        {
            /* Insert a single student into the database */
            case '1':
                printf("Enter Student id : ");
                GET_STRING(tmp,NAME_SIZE);
                errno = 0;
                id = (int)strtol(tmp, &endptr, 10);  // Base 10 integer
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid integer input for ID.\n");
                    continue;
                }
                
                printf("Enter Student name : ");
                GET_STRING(name,NAME_SIZE);

                printf("Enter Student height : ");
                GET_STRING(tmp, NAME_SIZE);
                errno = 0;
                height = strtof(tmp, &endptr);
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid float input for height.\n");
                    continue;
                }

                s_db_push_front(db, id, height, name);
                break;

            /* Insert a single student into the database at a particular position */
            case '2':
                index = 0;

                printf("Enter required index : ");
                scanf("%d",&index);

                printf("Enter Student id : ");
                GET_STRING(tmp,NAME_SIZE);
                errno = 0;
                id = (int)strtol(tmp, &endptr, 10);  // Base 10 integer
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid integer input for ID.\n");
                    continue;
                }

                printf("Enter Student name : ");
                GET_STRING(name,NAME_SIZE);

                printf("Enter Student height : ");
                GET_STRING(tmp, NAME_SIZE);
                errno = 0;
                height = strtof(tmp, &endptr);
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid float input for height.\n");
                    continue;
                }

                s_db_insert_at(db, index, id, height, name);
                break;

            /* Remove a student using an id  */    
            case '3':
                printf("Enter Student id : ");
                GET_STRING(tmp,NAME_SIZE);
                errno = 0;
                id = (int)strtol(tmp, &endptr, 10);  // Base 10 integer
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid integer input for ID.\n");
                    continue;
                }

                student *s1 = s_db_search(db,id);
                if(s1 == NULL){
                    printf("\nID not found in database\n");
                }else{
                    printf("Deleting student : \n");
                    s_db_format_student(s1,true);
                }
                s_db_remove_id(db,id);
                printf("\nStudent Deleted Successfully\n");

                break;

            /* Remove a student using an index  */    
            case '4':
                index = 0;

                printf("Enter required index : ");
                scanf("%d",&index);

                student *s2 = s_db_search_index(db,index);
                if(s2 == NULL){
                    printf("\nIndex not found in database\n");
                }else{
                    printf("\nDeleting student : \n");
                    s_db_format_student(s2,true);
                }

                s_db_remove_at(db,index);
                printf("\nStudent Deleted Successfully\n");

                break;

            /* Find a student in the database */
            case '5':
                printf("Enter Student id : ");
                GET_STRING(tmp,NAME_SIZE);
                errno = 0;
                id = (int)strtol(tmp, &endptr, 10);  // Base 10 integer
                if (errno != 0 || *endptr != '\0') {
                    printf("Invalid integer input for ID.\n");
                    continue;
                }

                student *s3 = s_db_search(db,id);
                if(s3 == NULL){
                    printf("\nID not found in database\n");
                }else{
                    s_db_format_student(s3,true);
                }
                break;

            /* Delete all students */
            case '6':
                s_db_delete_all(db);
                printf("All entries deleted successfully \n");
                break;

            /* Load students from a file, save current state first
               if file loads successfully done, if not reload previous state */
            case '7':
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
            case '8':
                s_db_print(db);
                break;

            /* Save Current state of the database */
            case '9':
                if(s_db_save_file(db,"./data/out.csv",'n')){
                    printf("Students saved Sucessfully\n");
                }else{
                    printf("Error Couldnt Save Students !!\n");
                }
                break;

            /* Clear Screen */
            case 'c':
                clear_screen();
                break;

            /* Exit, Option to save the current state of the database  */
            case 'e':
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