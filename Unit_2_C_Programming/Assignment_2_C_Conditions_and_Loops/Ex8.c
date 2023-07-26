#include <stdio.h>
#include <stdlib.h>
int main()
{
    float a, b;
    char ch;
    printf("Enter operator either + or - or * or / : ");
    scanf(" %c",&ch);
    printf("Enter two operands : ");
    scanf("%f",&a);
    scanf("%f",&b);

    switch (ch)
    {
    case '+':
        printf("%.2f + %.2f = %.2f\n",a,b,a+b);
        break;
    case '-':
        printf("%.2f - %.2f = %.2f\n",a,b,a-b);
        break;
    case '*':
        printf("%.2f * %.2f = %.2f\n",a,b,a*b);
        break;
    case '/':
        printf("%.2f / %.2f = %.2f\n",a,b,a/b);
        break;
    default:
        printf("Wrong Operator!\n");
        break;
    }
    system("pause");
    return 0;
}