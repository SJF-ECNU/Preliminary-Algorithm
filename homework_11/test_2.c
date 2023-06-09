#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    int a;
}node;
void swap(node**A,node**B)
{
    node*exchange = *A;
    *A = *B;
    *B = exchange;
}

int main()
{
    node*arr[10];
    node*x=(node*)malloc(sizeof(node));
    node*y=(node*)malloc(sizeof(node));
    x->a=1;
    y->a=0;
    arr[0]=x;
    arr[1]=y;
    int a=0;
    scanf("%d",&a);
    swap(&arr[0],&arr[1]);
    printf("%d\n",arr[0]->a);
    char str[10]={'\0'};
    strncat(str,"0",1);
    printf("%s--\n",str);
    return 0;
}