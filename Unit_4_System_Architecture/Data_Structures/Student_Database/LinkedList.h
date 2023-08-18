#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

void s_db_printheader();
void s_db_formatstudent(student *s, bool single);
void s_db_print(student_database *DB);

bool s_db_isempty(student_database *DB);

void s_db_pushfront(student_database *DB, int id, float height, char *name);
void s_db_pushback(student_database *DB, int id, float height, char *name);
void s_db_insertat(student_database *DB, int index, int id, float height, char *name);

void s_db_popfront(student_database *DB);
void s_db_popback(student_database *DB);
void s_db_removeat(student_database *DB, int index);
void s_db_removeid(student_database *DB, int id);


void s_db_reverse(student_database *DB);

student* s_db_search(student_database *DB, int id);

void s_db_deleteall(student_database *DB);
void s_db_free(student_database *DB);

static student *MergeLinkedListNodes(student *first, student *second);
static void MergeSortLinkedListNode(student **head);
void MergeSortLinkedList(student_database *L);

bool hasCycle (student_database *L);

#endif /* LINKED_LIST_H */