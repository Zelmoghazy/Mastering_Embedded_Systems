#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "Platform_Types.h"
#include "Config.h"


typedef struct student_data
{
    int ID;
    float height;
    char name[NAME_SIZE];
}student_data;

typedef struct student
{
    student_data data;
    struct student *next; 
} student;

typedef struct student_database
{
    student *first; 
    size_t size;
} student_database;

student_database *s_db_new();

void s_db_print_header();
void s_db_format_student(student *s, bool single);
void s_db_print(student_database *DB);

bool s_db_is_empty(student_database *DB);

void s_db_push_front(student_database *DB, int id, float height, char *name);
void s_db_push_back(student_database *DB, int id, float height, char *name);
void s_db_insert_at(student_database *DB, int index, int id, float height, char *name);

void s_db_pop_front(student_database *DB);
void s_db_pop_back(student_database *DB);
void s_db_remove_at(student_database *DB, int index);
void s_db_remove_id(student_database *DB, int id);


void s_db_reverse(student_database *DB);

student* s_db_search(student_database *DB, int id);
student* s_db_search_index(student_database *DB, int index);
student* s_db_search_index_end(student_database *DB, int index);
student* s_db_search_middle(student_database *DB);

void s_db_update(student_database *DB,int index, int id,float height,char *name);


int s_db_count(student_database *DB);

void s_db_delete_all(student_database *DB);
void s_db_free(student_database *DB);

static student *s_db_merge_nodes(student *first, student *second);
static void s_db_sort_node(student **head);
void s_db_sort(student_database *L);


bool s_db_has_loop (student_database *DB);

#endif /* LINKED_LIST_H */