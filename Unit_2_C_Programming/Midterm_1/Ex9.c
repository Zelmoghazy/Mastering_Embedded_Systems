#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <string.h>

void reverse(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverseWords(char* s) {
    int length = strlen(s);
    /* Reverse Array */
    reverse(s, s + length - 1);
    int i = 0;
    int start = 0;
    int end = 0;

    /* Reverse Each Word -> Normal */
    while (i < length) {
        while (i < length && s[i] != ' ') {
            s[start++] = s[i++];
        }

        if (end < start) {
            reverse(s + end, s + start - 1);
            if (start == length)
                break;
            s[start++] = ' ';
            end = start;
        }
        i++;
    }
    while (start > 0 && s[start - 1] == ' ')
        start--;
    s[start] = '\0';
}

int main() {
    char input[] = "mohamed gamal";
    reverseWords(input);
    printf("%s\n",input);
    system("pause");
    return 0;
}
