#include "LinkedList.h"

student_database *s_db_new()
{
    student_database *DB = malloc(sizeof(student_database));
    if(DB == NULL){
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    DB->first = NULL;
    DB->size = 0;
    return DB;
}

void s_db_printheader()
{
    printf("%-*s ",SPACES,"ID");
    printf("%-*s ",SPACES,"Name");
    printf("%-*s ",SPACES,"Height");
    printf("\n");
    for (size_t i = 0; i < SPACES*3; i++)
        printf("-");
    printf("\n");
}

void s_db_formatstudent(student *s, bool single)
{
    if(single){
        s_db_printheader();
    }
    printf("%-*d ",SPACES,s->data.ID);
    printf("%-*s ",SPACES,s->data.name);
    printf("%-*f ",SPACES,s->data.height);
    printf("\n");
}
void s_db_print(student_database *DB)
{
    s_db_printheader();
    student *current = DB->first;
    while (current->next != NULL){
        s_db_formatstudent(current,false);
        current = current->next;
    }
    s_db_formatstudent(current,false);
}

bool s_db_isempty(student_database *DB)
{
    return (DB->first == NULL);
}

void s_db_setdata(student *s, int id, float height, char *name)
{
    s->data.ID = id;  
    s->data.height = height;
    strcpy(s->data.name,name);  
}

void s_db_pushfront(student_database *DB, int id, float height, char *name)
{
    student *new_student = malloc(sizeof(student));
    if(new_student == NULL){
        printf("PushFront Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    s_db_setdata(new_student,id,height,name);
    new_student->next = DB->first;
    DB->first = new_student;
    DB->size++;
}

void s_db_pushback(student_database *DB, int id,float height,char *name)
{
    if (s_db_isempty(DB)){
        s_db_pushfront(DB, id,height,name);
    }else{
        student *last_student = DB->first;
        while (last_student->next != NULL){
            last_student = last_student->next;
        }
        student *new_student = malloc(sizeof(student));
        s_db_setdata(new_student,id,height,name);
        new_student->next = NULL;
        last_student->next = new_student;
        DB->size++;
    }
}

void s_db_insertat(student_database *DB,int index, int id,float height,char *name)
{
    if (s_db_isempty(DB)){
        s_db_pushfront(DB, id,height,name);
    }
    if (index == 1){ // insert at first position
        s_db_pushfront(DB, id,height,name);
        return;
    }
    else if (index > DB->size){
        s_db_pushback(DB, id,height,name);
        return;
    }

    student *req_student = DB->first;

    for (int i = 0; i < index - 2; i++){ 
        req_student = req_student->next;
    }
    student *new_student = malloc(sizeof(student));
    s_db_setdata(new_student,id,height,name);
    new_student->next = req_student->next;
    req_student->next = new_student;
    DB->size++;
}

void s_db_popfront(student_database *DB)
{
    if (s_db_isempty(DB)){
        return;
    }
    student *first_student = DB->first;
    DB->first = first_student->next;
    free(first_student);
    DB->size--;
}

void s_db_popback(student_database *DB)
{
    if (s_db_isempty(DB)){
        return;
    }
    if (DB->first->next == NULL){
        free(DB->first);
        DB->first = NULL;
        return;
    }

    student *last_student = DB->first;
    student *prev_student = DB->first;
    while (last_student->next != NULL){
        prev_student = last_student;       
        last_student = last_student->next; 
    }
    prev_student->next = NULL;
    free(last_student);
    last_student = NULL;
    DB->size--;
}

void s_db_removeat(student_database *DB, int index)
{
    if (s_db_isempty(DB)){
        return;
    }
    if (DB->first->next == NULL){
        free(DB->first);
        DB->first = NULL;
        return;
    }
    if (index == 1){
        s_db_popfront(DB);
        return;
    }
    else if (index >= DB->size){
        s_db_popback(DB);
        return;
    }
    student *prev_student = DB->first;
    for (int i = 0; i < index - 2; i++){
        prev_student = prev_student->next;
    }
    student *deleted_student = prev_student->next; 
    prev_student->next = deleted_student->next; 
    free(deleted_student);
}
void s_db_removeid(student_database *DB, int id)
{
    if (s_db_isempty(DB)){
        return;
    }
    if (DB->first->next == NULL &&
        DB->first->data.ID == id){
        free(DB->first);
        DB->first = NULL;
        return;
    }else{
        printf("Student not found\n");
    }
    student *iterator = DB->first;
    while (iterator != NULL){
        if (iterator->data.ID == id){
            student *deleted_student = iterator->next; 
            iterator->next = deleted_student->next; 
            free(deleted_student);
            return;
        }
        iterator = iterator->next;
    }
    printf("Student Not found\n");
}

void s_db_reverse(student_database *DB)
{
    if (DB->first == NULL || DB->first->next == NULL){
        return;
    }
    student *current = DB->first;
    student *prev = NULL;
    student *next = NULL;
    while (current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    DB->first = prev;
}

student* s_db_search(student_database *DB, int id)
{
    student *iterator = DB->first;
    while (iterator != NULL){
        if (iterator->data.ID == id){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void s_db_deleteall(student_database *DB)
{
    while (!s_db_isempty(DB)){
        s_db_popfront(DB);
    }
}

void s_db_free(student_database *DB)
{
    s_db_deleteall(DB);
    free(DB);
}

static student *MergeLinkedListNodes(student *first, student *second)
{
    student *result = NULL;
    if (first == NULL){
        return second;
    }
    if (second == NULL){
        return first;
    }

    if (first->data.ID <= second->data.ID){
        result = first;
        result->next = MergeLinkedListNodes(first->next, second);
    }else{
        result = second;
        result->next = MergeLinkedListNodes(first, second->next);
    }
    return result;
}

static void MergeSortLinkedListNode(student **head)
{
    if ((*head) == NULL || (*head)->next == NULL){
        return;
    }
    student *curr = *head;
    student *slow = curr;
    student *fast = curr->next;

    while (fast != NULL){
        fast = fast->next;
        if (fast != NULL){
            fast = fast->next;
            slow = slow->next;
        }
    }
    student *l1 = curr;
    student *l2 = slow->next;
    slow->next = NULL;
    MergeSortLinkedListNode(&l1);
    MergeSortLinkedListNode(&l2);
    *head = MergeLinkedListNodes(l1, l2);
}

void MergeSortLinkedList(student_database *L)
{
    MergeSortLinkedListNode(&(L->first));
}

bool hasCycle (student_database *DB){
    if(DB->first == NULL || DB->first->next == NULL){
        return false;
    }
    student *slow = DB->first;
    student *fast = DB->first->next;
    while(fast!= NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow){
            return true;
        }
    }
    return false;
}