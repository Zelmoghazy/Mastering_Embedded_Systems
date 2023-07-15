/* Function to Clear/Set/Toggle a specified bit in a given number */

int count_binary_digits(int n)
{
    int count = 0;
    while (n != 0){
        n /= 2;
        count++;
    }
    return count;
}

int modify_bit(int num,int n,char ch){
    if(count_binary_digits(num) < n){
        return num;
    }
    switch (ch)
    {
        case 'c':
        case 'C':
            num &= ~(1 << n);
            break;
        case 's':
        case 'S':
            num |= (1 << n);
            break;
        case 't':
        case 'T':
            num ^= (1 << n);
            break;
        default:
            return num;
            break;
    }
    return num;
}