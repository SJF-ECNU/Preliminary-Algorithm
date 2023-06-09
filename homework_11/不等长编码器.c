#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    for (i; i >= 1; i--)
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
    for (i; i >= 0; i--)
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
// 平均长度
int meansize(node *tree[], int k)
{
    int i = 0;
    int length = 0;
    for (i = 0; i < k; i++)
    {
        node *tmp = tree[i];
        int size = 0;
        while (tmp != NULL)
        {
            size++;
            tmp = tmp->parent;
        }
        size--;
        size = size * tree[i]->frequency;
        length += size;
    }
    return length;
}

void codeTab_print(node *tree[], int k, char*codeTab[])
{
    int i = 0;
    for (i = 0; i < k; i++)
    {
        int code[100];
        int size = 0;
        int j = 0;
        printf("%c : ", tree[i]->key);
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
        printf("%s\n", string);
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

void print(node*tree[],char*codeTab[],char*str,int count)
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
        printf("%s",codeTab[j]);
    }
}
int main()
{

    int count = 0;
    int i = 0;
    char *str = (char *)malloc(sizeof(char) * 10000);
    char ch=getchar();
    while (ch!='\n')
    {
        str[i++]=ch;
        ch=getchar();
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
    // int size = 0;
    // for (i = 0; i < k; i++)
    // {
    //     size = tree_1[i]->frequency + size;
    // }
    // printf("%.2f\n", (double)meansize(tree_1, k) / (double)size);
    char*codeTab[150];
    printf("%d\n",count);
    codeTab_print(tree_1,i,codeTab);
    print(tree_1,codeTab,str,count);
    tmp=head;
    for(i=0;i<count;i++)
    {
        free(tree_1[i]);
        node*FreeLink=tmp;
        tmp=tmp->next;
        free(FreeLink);
        free(codeTab[i]);
    }
    return 0;
}