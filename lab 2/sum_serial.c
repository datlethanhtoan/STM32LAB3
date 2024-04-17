#include<stdio.h>
#include<stdlib.h>

unsigned long long sum_serial(int n)
{
     unsigned long long sum = 0;
     for (int i = 1; i <= n; i++)
     {
        sum += i;
     }
     return sum;
}
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s n\n", argv[0]);
    }
    int n = atoi(argv[1]);
    if (n <= 0)
    {
        printf("n must be > 0\n");
    }
    unsigned long long result = sum_serial(n);
    printf("Sum from 1 to %d is %llu\n", n, result);
    return 0;
}
