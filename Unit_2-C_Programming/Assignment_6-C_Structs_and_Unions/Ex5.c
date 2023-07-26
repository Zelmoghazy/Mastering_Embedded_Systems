#include <stdio.h>
#include <stdlib.h>

#define PI 3.14
#define area_circle(a, r) (a)=(r)*(r)*PI 

int main()
{
    float area = 0;
    float radius;
    printf("Enter the radius : ");
    scanf("%f",&radius);
    printf("Area of circle = %.2f\n",area_circle(area,radius));
    system("pause");
    return 0;
}