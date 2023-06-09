#include<stdio.h>
#include"First.h"
int main()
{
    FILE*tmp=fopen("C:\\Code\\test.txt","w");
    int N=1000000,min=0,max=10000,type=1;
    int*nums=RandomNums(N,min,max,type);
    if(tmp!=NULL)
    {
        int i=0;
        for(i;i<N;i++)
        {
            fprintf(tmp,"%d ",*(nums+i));
        }
        fclose(tmp);
        printf("successed!\n");
    }
    return 0;
}