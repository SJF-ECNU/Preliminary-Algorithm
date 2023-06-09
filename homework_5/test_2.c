#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//srand((unsigned)time(NULL) + rand());
void randomnum(int i)
{
    srand((unsigned)time(NULL)+rand());
    if(i==0) return;
    printf("%d ",rand());
    randomnum(i-1);
}
int main()
{
    randomnum(10);
    return 0;
}