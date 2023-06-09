#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
typedef struct HashTable
{
    int count;
    int arr[100000];
    int flag[100000];
}hash;
void randomKeyCreate(int N, int * methods)
{
    srand((unsigned)time(NULL)+rand());
    int i=0;
    for(i=0;i<N;i++)
    {
        methods[i]=rand()%2;
    }
}
void randomNums(int N,int *root)
{
    srand((unsigned)time(NULL)+rand());
    int i=0,change,t;
    for (i=0;i<N;i++)
		root[i]=i+100000;
	for (i=0;i<N;i++)
	{
		change = rand()%N;
	 	t = root[i];
		root[i] = root[change];
		root[change] = t;
	}
    for(i=0;i<N;i++)
    {
        if(rand()%2==0)
            root[i]=-root[i];
    }
}
void insert(hash*hashtable,int key,int N)
{
    int tmp = key;
    if (key < 0)
        tmp = -tmp;
    int location = (tmp+666) % N;
    int i = 0;
    for (i = 0; i <=hashtable->count; i++)
    {
        if (hashtable->flag[location] == 0)
        {
            hashtable->flag[location] = 1;
            hashtable->arr[location] = key;
			hashtable->count++;
            return;
        }
        location++;
        if (location == N)
            location = 0;
    }
}
void search(hash*hashtable,int key,int N)
{
    int tmp = key;
    if (key < 0)
        tmp = -tmp;
    int location = (tmp + 666)% N;
    int i = 0;
    for (i = 0;hashtable->flag[location]!=0; i++)
    {
        if (hashtable->flag[location]==1 && hashtable->arr[location] == key)
		{
			// printf("Yes\n");
			return;
		}
        location++;
        if (location == N)
            location = 0;
    }
	// printf("No\n");
    return ;
}
//顺序访问
typedef struct array
{
    int count;
    int arr[100000];
}array;
void arry_insert(array*nums,int key)
{
    nums->arr[nums->count++]=key;
}
void arry_search(array*nums,int key)
{
    int i=0;
    for(i=0;i<nums->count;i++)
    {
        if(nums->arr[i]==key)
        {
            // printf("Yes\n");
            return;
        }
    }
    // printf("No\n");
    return;
}
int main()
{
    hash*hashtable=(hash*)malloc(sizeof(hash));
    int N;
    scanf("%d",&N);
    int*keys_1=(int*)malloc(sizeof(int)*N);
    int*keys_2=(int*)malloc(sizeof(int)*N);
    int*methods=(int*)malloc(sizeof(int)*N);
    randomNums(N,keys_1);
    randomNums(N,keys_2);
    randomKeyCreate(N,methods);
    int i=0;
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(i=0;i<N;i++)
    {
        char method;
        if(methods[i]) method='I';
        else method='Q';
        switch(method)
        {
            case 'I':
                insert(hashtable,keys_1[i],100000);
                break;
            case 'Q':
                search(hashtable,keys_2[i],100000);
                break;
            default:
                break;
        }
    }
    QueryPerformanceCounter(&t2);
    printf("t_hash = %f second\n",(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart);
    array*nums=(array*)malloc(sizeof(array));
    nums->count=0;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(i=0;i<N;i++)
    {
        char method;
        if(methods[i]) method='I';
        else method='Q';
        switch(method)
        {
            case 'I':
                arry_insert(nums,keys_1[i]);
                break;
            case 'Q':
                // if(arry_search(nums,key))printf("Yes\n");
                // else printf("No\n");
                arry_search(nums,keys_2[i]);
                break;
            default:
                break;
        }
    }
    QueryPerformanceCounter(&t2);
    printf("t_arry = %f second\n",(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart);
    return 0;
}