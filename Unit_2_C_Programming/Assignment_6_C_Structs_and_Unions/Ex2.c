#include <stdio.h>
#include <stdlib.h>

typedef struct Distance {
    int feet;
    float inch; 
}Distance;

void distance_sum(Distance d1, Distance d2){
    int feet = d1.feet+d2.feet;
    float inches = 0.0;
    if(d1.inch+d2.inch >= 12.0){
        inches = (d1.inch + d2.inch) - 12.0;
        feet++;
    }else{
        inches = d1.inch + d2.inch;
    }
    printf("Sum of distances = %d' - %.2f\"\n",feet,inches);   
}

void distance_read(Distance *s1){
    float inch;
    printf("Enter feet: ");
    scanf("%d",&(s1->feet));
    printf("Enter inch: ");
    scanf("%f",&inch);
    while(inch >= 12.0){
        s1->feet++;
        inch -= 12.0;
    }
    s1->inch = inch;
}

int main()
{
    Distance d1;
    Distance d2;
    printf("Enter information for 1st Distance :\n");
    distance_read(&d1);
    printf("Enter information for 2nd Distance :\n");
    distance_read(&d2);
    distance_sum(d1,d2);
    system("pause");
    return 0;
}