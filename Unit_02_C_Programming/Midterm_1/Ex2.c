#include <stdio.h>
#include <stdlib.h>

/* c function to take an integer number and calculate it's square root */
double squareRoot(int number, int precision)
{
    if (number < 0){
        printf("Error : square root of negative number doesnt exist!\n");
        return -1;
    }
    if (number == 0 || number == 1){
        return number;
    }
    int i;
    int start = 0;
    int end = number / 2; 
    double result = 0;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (mid * mid == number){
            return mid;
        }
        if (mid * mid < number){
            start = mid + 1;
            result = mid;
        }else{
            end = mid - 1;
        }
    }
    double increment = 0.1;
    for (i= 0; i < precision; i++)
    {
        while (result * result <= number){
            result += increment;
        }
        result = result - increment;
        increment = increment / 10;
    }
    return result;
}

int main(void){
    printf("%.3lf\n",squareRoot(4,3));
    printf("%.3lf\n",squareRoot(10,3));
    system("pause");
    return 0;
}