#include<stdio.h>
int main()
{
    int c=10;
    int b=3;
    int a=1/(1-(double)b/(double)c);
    printf("%d",a);
    return 0;
}