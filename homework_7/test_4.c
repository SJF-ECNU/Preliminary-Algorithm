#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#define size 125000
double a=0.2;
typedef struct HashTable
{
    int count;
    int arr[size];
    int flag[size];
}hash;
// 1-insert 0-search
void randommethodCreate(int N, int * methods)
{
    int i=0;
    for(i=0;i<N;i++)
    {
        if(i<N*a) methods[i]=1;
        else methods[i]=0;
    }
}
void randomNums(int N,int *root)
{
    srand((unsigned)time(NULL)+rand());
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
//h1(k)=k%m_1,h2(k)=k%m_2+1
#define m_1 size
#define m_2 (size-3)
#define h_1(k) ((k)%(m_1))
#define h_2(k) ((k)%(m_2)+1)
void insert(hash*hashtable,int key)
{
    if(hashtable->count==size)
    {
        printf("full!\n");
        return;
    }
    int tmp=key;
    if(key<0) tmp=-key;
    int i=0;
    for(i=0;i<=hashtable->count;i++)
    {
        int location = (h_1(tmp) + i * h_2(tmp)) % size;
        if(hashtable->flag[location]==0)
        {
            hashtable->flag[location]=1;
            hashtable->count++;
            hashtable->arr[location]=key;
            return;
        }
    }
}
void search(hash*hashtable, int key)
{
    int i=0;
    int tmp=key;
    if(key<0) tmp=-key;
    int location = (h_1(tmp) + i * h_2(tmp)) % size;
    for(i=0;hashtable->flag[location]!=0;i++)
    {
        location = (h_1(tmp) + i * h_2(tmp)) % size;
        if(hashtable->flag[location]==1&&hashtable->arr[location]==key) 
        {
            //printf("yes\n");
            return;
        }
    }
    //printf("no\n");
    return;
}
//顺序访问
typedef struct array
{
    int count;
    int arr[size];
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
                //printf("yes\n");
                return;
            }
    }
    //printf("no\n");
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
    randommethodCreate(N,methods);
    int i=0;
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    //QueryPerformanceCounter(&t1);  
    for(i=0;i<(100+N*a);i++)
    {
        if(i==N*a)  QueryPerformanceCounter(&t1);       
        char method;
        if(methods[i]) method='I';
        else method='Q';
        switch(method)
        {
            case 'I':
                insert(hashtable,keys_1[i]);
                break;
            case 'Q':
                search(hashtable,keys_2[i]);
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
    for(i=0;i<(100+a*N);i++)
    {
        if(i==a*N) QueryPerformanceCounter(&t1); 
        char method;
        if(methods[i]) method='I';
        else method='Q';
        switch(method)
        {
            case 'I':
                arry_insert(nums,keys_1[i]);
                break;
            case 'Q':
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