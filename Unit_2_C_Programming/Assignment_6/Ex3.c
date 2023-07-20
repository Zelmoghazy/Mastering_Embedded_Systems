#include <stdio.h>
#include <stdlib.h>

typedef struct Complex
{
    float re;
    float im;
}Complex;

Complex complex_sum(Complex c1, Complex c2){
    Complex res;
    res.re = c1.re + c2.re;
    res.im = c1.im + c2.im;
    return res;
}

void complex_print(Complex c1){
    printf("%.2f + %.2fi\n",c1.re,c1.im);
}

int main()
{
    Complex c1;
    Complex c2;
    Complex res;

    printf("For 1st complex number\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f",&c1.re);
    scanf("%f",&c1.im);

    printf("For 2nd complex number\n");
    printf("Enter real and imaginary respectively: ");
    scanf("%f",&c2.re);
    scanf("%f",&c2.im);

    res = complex_sum(c1,c2);
    complex_print(res);
    
    system("pause");
}