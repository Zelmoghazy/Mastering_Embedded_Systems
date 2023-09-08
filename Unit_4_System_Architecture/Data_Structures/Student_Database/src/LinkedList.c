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

void s_db_print_header()
{
    printf("\n");
    for (size_t i = 0; i < SPACES*3; i++)
        printf("*");
    printf("\n");
    printf("%-*s ",SPACES/2,"ID");
    printf("%-*s ",SPACES/2,"*");
    printf("%-*s ",SPACES/2,"Name");
    printf("%-*s ",SPACES/2,"*");
    printf("%-*s ",SPACES,"Height");
    printf("\n");
    for (size_t i = 0; i < SPACES*3; i++)
        printf("*");
    printf("\n");
}

void s_db_format_student(student *s, bool single)
{
    if(single){
        s_db_print_header();
    }
    printf("%-*d ",SPACES/2,s->data.ID);
    printf("%-*s ",SPACES/2,"*");
    printf("%-*s ",SPACES/2,s->data.name);
    printf("%-*s ",SPACES/2,"*");
    printf("%-*f ",SPACES,s->data.height);
    printf("\n");
}
void s_db_print(student_database *DB)
{
    s_db_print_header();
    student *current = DB->first;
    while (current->next != NULL){
        s_db_format_student(current,false);
        current = current->next;
    }
    s_db_format_student(current,false);
    for (size_t i = 0; i < SPACES*3; i++)
        printf("*");
    printf("\n");
}

bool s_db_is_empty(student_database *DB)
{
    return (DB->first == NULL);
}

void s_db_set_data(student *s, int id, float height, char *name)
{
    s->data.ID = id;  
    s->data.height = height;
    strcpy(s->data.name,name);  
}

void s_db_push_front(student_database *DB, int id, float height, char *name)
{
    student *new_student = malloc(sizeof(student));
    if(new_student == NULL){
        printf("PushFront Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    s_db_set_data(new_student,id,height,name);
    new_student->next = DB->first;
    DB->first = new_student;
    DB->size++;
}

void s_db_push_back(student_database *DB, int id,float height,char *name)
{
    if (s_db_is_empty(DB)){
        s_db_push_front(DB, id,height,name);
    }else{
        student *last_student = DB->first;
        while (last_student->next != NULL){
            last_student = last_student->next;
        }
        student *new_student = malloc(sizeof(student));
        s_db_set_data(new_student,id,height,name);
        new_student->next = NULL;
        last_student->next = new_student;
        DB->size++;
    }
}

void s_db_insert_at(student_database *DB,int index, int id,float height,char *name)
{
    if (s_db_is_empty(DB)){
        s_db_push_front(DB, id,height,name);
    }
    if (index == 1){ // insert at first position
        s_db_push_front(DB, id,height,name);
        return;
    }
    else if (index > DB->size){
        s_db_push_back(DB, id,height,name);
        return;
    }

    student *req_student = DB->first;

    for (int i = 0; i < index - 2; i++){ 
        req_student = req_student->next;
    }
    student *new_student = malloc(sizeof(student));
    s_db_set_data(new_student,id,height,name);
    new_student->next = req_student->next;
    req_student->next = new_student;
    DB->size++;
}

void s_db_pop_front(student_database *DB)
{
    if (s_db_is_empty(DB)){
        return;
    }
    student *first_student = DB->first;
    DB->first = first_student->next;
    free(first_student);
    DB->size--;
}

void s_db_pop_back(student_database *DB)
{
    if (s_db_is_empty(DB)){
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

void s_db_remove_at(student_database *DB, int index)
{
    if (s_db_is_empty(DB)){
        return;
    }
    if (DB->first->next == NULL){
        free(DB->first);
        DB->first = NULL;
        return;
    }
    if (index == 1){
        s_db_pop_front(DB);
        return;
    }
    else if (index >= DB->size){
        s_db_pop_back(DB);
        return;
    }
    student *prev_student = DB->first;
    for (int i = 0; i < index - 2; i++){
        prev_student = prev_student->next;
    }
    student *deleted_student = prev_student->next; 
    prev_student->next = deleted_student->next; 
    free(deleted_student);
    DB->size--;
}
void s_db_remove_id(student_database *DB, int id)
{
    if (s_db_is_empty(DB)){
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
            DB->size--;
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
    if(DB->first == NULL)
    {
        return NULL;
    }
    student *iterator = DB->first;
    while (iterator != NULL){
        if (iterator->data.ID == id){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

student* s_db_search_index(student_database *DB, int index)
{
    if(DB->first == NULL)
    {
        return NULL;
    }
    if(index > DB->size){
        printf("Index Exceed database size\n");
        return NULL;
    }
    student *iterator = DB->first;
    for (size_t i = 0; i < index-1; i++)
    {
        iterator = iterator->next;
    }    
    return iterator;
}
student* s_db_search_index_end(student_database *DB, int index)
{
    if(DB->first == NULL)
    {
        return NULL;
    }
    student *iterator = DB->first;
    student *reference = DB->first;
    for (size_t i = 0; i < index-1; i++)
    {
        reference = reference->next;
    }
    while(reference != NULL)
    {
        reference = reference->next;
        iterator = iterator->next;
    }    
    return iterator;
}
student* s_db_search_middle(student_database *DB)
{
    if(DB->first == NULL)
    {
        return NULL;
    }
    student *iterator = DB->first;
    student *reference = DB->first;
    while(reference!=NULL && reference->next != NULL)
    {
        reference = reference->next->next;
        iterator = iterator->next;
    }    
    return iterator;
}

int s_db_count(student_database *DB)
{
    if(DB->first == NULL)
    {
        return 0;
    }
    int count = 0;
    student *iterator = DB->first;
    while (iterator != NULL){
        iterator = iterator->next;
        count++;
    }
    assert(count == DB->size);
    return count;
}

void s_db_update(student_database *DB,int index, int id,float height,char *name)
{
    student *s = s_db_search(DB,id);
    assert(s);
    s->data.height = height;
    strcpy(s->data.name,name);  
}


void s_db_delete_all(student_database *DB)
{
    while (!s_db_is_empty(DB)){
        s_db_pop_front(DB);
    }
    DB->first = NULL;
    DB->size = 0;
}

void s_db_free(student_database *DB)
{
    s_db_delete_all(DB);
    free(DB);
}

bool s_db_has_loop (student_database *DB)
{
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
static student *s_db_merge_nodes(student *first, student *second)
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
        result->next = s_db_merge_nodes(first->next, second);
    }else{
        result = second;
        result->next = s_db_merge_nodes(first, second->next);
    }
    return result;
}

static void s_db_sort_node(student **head)
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
    s_db_sort_node(&l1);
    s_db_sort_node(&l2);
    *head = s_db_merge_nodes(l1, l2);
}

void s_db_sort(student_database *L)
{
    s_db_sort_node(&(L->first));
}

static char * s_db_read_file(char* path)
{
    int ch;
    int n = 0;

    FILE *file = fopen(path, "r");
    if (!file){
        fprintf(stderr, "Couldnt load file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *source = malloc(sizeof(char) * size + 1);


    while ((ch = fgetc(file)) != EOF) {
        source[n++] = (char)ch;
    }

    source[n] = '\0';

    fclose(file);
    return source;
}

bool s_db_validate(char *str,int line,char choice)
{
    switch (choice)
    {
    case 'i':
        if(!is_integer(str)){
            printf("Invalid Integer : %s at line : %d\n",str,line);
            return false;
        }else{
            return true;
        }
    case 'f':
        if(!is_float(str)){
            printf("Invalid Float : %s at line : %d\n",str,line);
            return false;
        }else{
            return true;
        }
    default:
        printf("Invalid Choice !\n");
        return false;
    }

}

bool s_db_load_students(student_database *DB,char *path)
{
    int line = 1;

    int id;
    float height;
    char name[NAME_SIZE];

    char *source = s_db_read_file(path);
    if(source == NULL){
        return false;
    }

    int buf_i=0;
    char buffer[NAME_SIZE];

    char* ptr = source;

    while(*ptr != '\0'){
        while(*ptr != '\n' && *ptr != '\0')
        {
            /* ID */
            while(*ptr != DELIMITER)
            {
                buffer[buf_i++]= *ptr;
                ptr++;
            }
            buffer[buf_i] = '\0';
            if(!s_db_validate(buffer,line,'i')){
                return false;
            };
            id = atoi(buffer);
            buf_i = 0;
            ptr++;

            /* Name */
            while(*ptr != DELIMITER)
            {
                buffer[buf_i++]= *ptr;
                ptr++;
            }
            buffer[buf_i] = '\0';
            strcpy(name,buffer);
            buf_i = 0;
            ptr++;
            
            /* Height */
            while(*ptr != DELIMITER)
            {
                buffer[buf_i++]= *ptr;
                ptr++;
            }
            buffer[buf_i] = '\0';
            if(!s_db_validate(buffer,line,'f')){
                return false;
            };
            height = atof(buffer);
            buf_i = 0;
            ptr++;
        }
        s_db_push_front(DB,id,height,name);
        if(*ptr == '\0') {break;}
        ptr++;
        line++;            
    }
    free(source);
    return true;
}