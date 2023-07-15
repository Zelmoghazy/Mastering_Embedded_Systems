/* Write a function to convert ASCII array to unsigned integer */

unsigned int arraytoint(char *A)
{
    unsigned int num = 0;
    while(*A){
        num = num * 10 + ((*A)-0x30);
        A++;
    }
    return num;
}