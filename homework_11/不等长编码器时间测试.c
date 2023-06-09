#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
// 编码
typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    int frequency;
    char key;
    int flag;
    int ifempty;
} node;
// 堆排序的调整
void judge_exchange(node *heap[], int locate, int count) // small root
{
    int left = locate * 2 + 1, right = locate * 2 + 2, minimum = locate;
    if (left <= count - 1 && heap[left]->frequency == heap[minimum]->frequency)
    {
        if (heap[left]->ifempty == 1)
            minimum = left;
        else if (heap[minimum]->key > heap[left]->key)
            minimum = left;
    }
    if (right <= count - 1 && heap[right]->frequency == heap[minimum]->frequency)
    {
        if (heap[right]->ifempty == 1)
            minimum = right;
        if (heap[minimum]->key > heap[right]->key)
            minimum = right;
    }
    if (right <= count - 1 && heap[right]->frequency < heap[minimum]->frequency)
        minimum = right;
    if (left <= count - 1 && heap[left]->frequency < heap[minimum]->frequency)
        minimum = left;
    if (minimum == locate)
        return;
    node *tmp = heap[minimum];
    heap[minimum] = heap[locate];
    heap[locate] = tmp;
    judge_exchange(heap, minimum, count);
}

void heap_sort(node *heap[], int count)
{
    int i = count - 1;
    for (; i >= 1; i--)
    {
        node *tmp = heap[0];
        heap[0] = heap[i];
        heap[i] = tmp;
        judge_exchange(heap, 0, i);
    }
}

void heap_create(node *heap[], int count) // small root
{
    int i = count / 2 - 1;
    for (; i >= 0; i--)
    {
        judge_exchange(heap, i, count);
    }
}
// 哈夫曼编码
void Haffman(node *tree[], int k, int count)
{
    int i = 0;
    for (i = 0; i < k - 1; i++)
    {
        heap_sort(tree, count);
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 1;
        newnode->left = tree[--count];
        newnode->right = tree[--count];
        newnode->left->flag = 0;
        newnode->right->flag = 1;
        newnode->frequency = newnode->left->frequency + newnode->right->frequency;
        newnode->parent = NULL;
        newnode->left->parent = newnode;
        newnode->right->parent = newnode;
        tree[count++] = newnode;
        heap_create(tree, count);
    }
}

void codeTab_print(node *tree[], int k, char*codeTab[],FILE*pf_w)
{
    int i = 0;
    for (i = 0; i < k; i++)
    {
        int code[100];
        int size = 0;
        int j = 0;
        fprintf(pf_w,"%c : ", tree[i]->key);
        node *tmp = tree[i];
        while (tmp->parent != NULL)
        {
            code[size++] = tmp->flag;
            tmp = tmp->parent;
        }
        char *string = (char *)malloc(sizeof(char) * (size + 1));
        for (j = 0; j < size; j++)
        {
            if (code[size - 1 - j] == 0)
            {
                string[j] = '0';
            }
            else
            {
                string[j] = '1';
            }
        }
        string[j] = '\0';
        codeTab[i]=string;
        fprintf(pf_w,"%s\n", string);  
    }
    // fclose(p);
}

// 用链表统计字符个数
typedef struct link
{
    struct link *next;
    char key;
    int frequency;
} link;
link *search(link *head, char target)
{
    link *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->key == target)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}
link *frequencyCounter(char *str)
{
    int size = strlen(str);
    link *head = (link *)malloc(sizeof(link));
    head->frequency = 1;
    head->key = str[0];
    head->next = NULL;
    int i = 1;
    for (i = 1; i < size; i++)
    {
        link *tmp = search(head, str[i]);
        if (tmp != NULL)
        {
            tmp->frequency++;
        }
        else
        {
            tmp = head;
            while (tmp->next != NULL)
                tmp = tmp->next;
            link *newlink = (link *)malloc(sizeof(link));
            newlink->frequency = 1;
            newlink->next = NULL;
            newlink->key = str[i];
            tmp->next = newlink;
        }
    }
    return head;
}

void print(node*tree[],char*codeTab[],char*str,int count,FILE*pf_w)
{
    int i=0;
    int size=strlen(str);
    for(i=0;i<size;i++)
    {
        char ch=str[i];
        int j=0;
        for(j=0;j<count;j++)
        {
            if(tree[j]->key==ch)
                break;
        }
        fprintf(pf_w,"%s",codeTab[j]);
    }
}
int main()
{
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    FILE*pf_r=fopen("D:\\Code\\CODE_C\\homework_11\\huffman\\input.txt","r");
    FILE*pf_w=fopen("D:\\Code\\CODE_C\\homework_11\\decode\\haffman.txt","w");
    if(pf_r==NULL||pf_w==NULL)
    {
        printf("Failed to open file!!!\n");
        return 0;
    }
    int count = 0;
    int i = 0;
    char *str = (char *)malloc(sizeof(char) * 1000000);
    char ch;
    fscanf(pf_r,"%c",&ch);
    while (ch!='\n')
    {
        str[i++]=ch;
        fscanf(pf_r,"%c",&ch);
    }
    str[i]='\0';
    node *tree[150];
    node *tree_1[150];
    for (i = 0; i < 150; i++)
    {
        tree[i] = NULL;
        tree_1[i] = NULL;
    }
    link *head = frequencyCounter(str);
    link *tmp = head;
    i = 0;
    while (tmp != NULL)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 0;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->parent = NULL;
        newnode->key = tmp->key;
        newnode->frequency = tmp->frequency;
        tree[count] = newnode;
        tree_1[count++] = newnode;
        i++;
        tmp = tmp->next;
    }
    heap_create(tree, count);
    Haffman(tree, i, count);
    char*codeTab[150];
    fprintf(pf_w,"%d\n",count);
    codeTab_print(tree_1,i,codeTab,pf_w);
    print(tree_1,codeTab,str,count,pf_w);
    fprintf(pf_w,"\n");
    QueryPerformanceCounter(&t2);
    fclose(pf_r);
    fclose(pf_w);    
    int size = 0,length=0;
    for (i = 0; i < count; i++)
    {
        size = tree_1[i]->frequency + size;
        length=strlen(codeTab[i])*tree_1[i]->frequency+length;
    }
    printf("Haffman finished!\ntime_cost= %.7f second, length_average = %.8f\n",(double)(t2.QuadPart - t1.QuadPart) / ((double)tc.QuadPart),(double)length/(double)size);
    tmp=head;
    for(i=0;i<count;i++)
    {
        free(tree_1[i]);
        link*FreeLink=tmp;
        tmp=tmp->next;
        free(FreeLink);
        free(codeTab[i]);
    }
    return 0;
}