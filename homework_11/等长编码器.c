#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
//编码
typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    char key;
    int flag;
} node;

void code_create(node *tree[], int count)
{
    if (count % 2 != 0)
    {
        tree[count++] = NULL;
    }
    int i = 0;
    while (1)
    {
        int locate=0;
        for (i = 0; i < count;)
        {
            node *newnode = (node *)malloc(sizeof(node));
            newnode->left = tree[i++];
            newnode->right = tree[i++];
            newnode->left->parent = newnode;
            newnode->left->flag = 0;
            if (newnode->right != NULL)
            {
                newnode->right->parent = newnode;
                newnode->right->flag = 1;
            }
            newnode->parent = NULL;
            tree[locate++] = newnode;
        }
        if (locate==1)
            break;
        if (locate % 2 != 0)
        {
            tree[locate++] = NULL;
        }
        count=locate;
    }
}

//用链表统计字符个数
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

void codeTab_print(node *tree[], int k, char*codeTab[],FILE*pf_w)
{
    int i = 0;
    for (i = 0; i < k; i++)
    {
        int code[1000];
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
    FILE*pf_r=fopen("D:\\Code\\CODE_C\\homework_11\\normal\\input.txt","r");
    FILE*pf_w=fopen("D:\\Code\\CODE_C\\homework_11\\decode\\normal.txt","w");
    if(pf_r==NULL||pf_w==NULL)
    {
        printf("Failed to open file!!!\n");
        return 0;
    }
    node *tree[150];
    node *tree_1[150];
    int i=0;
    char *str = (char *)malloc(sizeof(char) * 1000000);
    char ch;
    fscanf(pf_r,"%c",&ch);
    while (ch!='\n')
    {
        str[i++]=ch;
        fscanf(pf_r,"%c",&ch);
    }
    str[i]='\0';
    for(i=0;i<150;i++)
    {
        tree[i]=NULL;
        tree_1[i]=NULL;
    }
    link *head = frequencyCounter(str);
    link *tmp = head;
    i=0;
    while (tmp != NULL)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->parent = NULL;
        newnode->key = tmp->key;
        tree[i] = newnode;
        tree_1[i] = newnode;
        tmp=tmp->next;
        i++;
    }
    code_create(tree, i);
    char*codeTab[150];
    fprintf(pf_w,"%d\n",i);
    codeTab_print(tree_1, i,codeTab,pf_w);
    print(tree_1,codeTab,str,i,pf_w);
    int j=0;
    QueryPerformanceCounter(&t2);
    fclose(pf_r);
    fclose(pf_w);
    printf("Normal finished!\ntime_cost= %.7f second, length_average = %.8f\n",(double)(t2.QuadPart - t1.QuadPart) / ((double)tc.QuadPart),(double)strlen(codeTab[0]));
    tmp=head;
    for(j=0;j<i;j++)
    {
        link*FreeLink=tmp;
        tmp=tmp->next;
        free(FreeLink);
        free(tree_1[j]);
        free(codeTab[j]);
    }
    return 0;
}