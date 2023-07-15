/* Write a C program takes string from the user and check if it the same USERNAME or not. */
int main()
{
    char *username = "Zelmoghazy";
    char input[MAX_SIZE];
    fgets(input, MAX_SIZE, stdin);
    input[strcspn(input, "\n")] = 0;
    if(!strcmp(input,username)){
        printf("Correct Username\n");
    }else{
        printf("Incorrect Username\n");
    }
    return 0;
}