/* Write a c function that checks if a given number is power of another */

bool is_power_of(int a, int n){
    if(a==0 || a == 1)
        return false;
    while (a % n == 0) {
        a /= n;
    }
    return (a == 1);
}