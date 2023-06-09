#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void randomNums(int N,int *root)
{
    srand((unsigned)time(NULL)+rand());
    // int i=0,change,t;
    // for (i=0;i<N;i++)
	// 	root[i]=i+size;
	// for (i=0;i<N;i++)
	// {
	// 	change = rand()%N;
	//  	t = root[i];
	// 	root[i] = root[change];
	// 	root[change] = t;
	// }
    // for(i=0;i<N;i++)
    // {
    //     if(rand()%2==0)
    //         root[i]=-root[i];
    // }
    int*arr=(int*)calloc(10000000,sizeof(int));
    int i=0,j=0;
    for(i=0;i<N;)
    {
        int  num = ((rand() << 16) | (rand() << 1 )| (rand()& 1));
        if(num<0) num=-num;
        num=num% 10000000;
        if(arr[num]==0)
        {
            arr[num]=1;
            root[i++]=num;
        }
    }
}
int main()
{
    int arr[10];
    randomNums(10,arr);
    int i=0;
    for(i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}