#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node
{
    struct node *left;
    struct node *right;
    //struct node *parent;
    int frequency;
    char key;
    int flag;
    int ifempty;
    int ifprint;
} node;

void judge_exchange(node *heap[], int locate,int count)
{
    int left = locate * 2+1, right = locate * 2 + 2, minimum = locate;
    if (left <= count - 1 && heap[left]->frequency == heap[minimum]->frequency)
    {
        if(heap[left]->ifempty==1) 
            minimum=left;
        else if (heap[minimum]->key > heap[left]->key)
            minimum = left;
    }
    if (right <= count - 1 && heap[right]->frequency == heap[minimum]->frequency)
    {
        if(heap[right]->ifempty==1) 
            minimum=right;
        if (heap[minimum]->key > heap[right]->key)
            minimum = right;
    }
    if (right <= count - 1 && heap[right]->frequency < heap[minimum]->frequency)
        minimum = right;
    if (left <= count - 1 && heap[left]->frequency < heap[minimum]->frequency)
        minimum = left;
    if (minimum == locate)
        return;
    //swap(&(heap[largest]), &(heap[locate]));
    node *tmp = heap[minimum];
    heap[minimum] = heap[locate];
    heap[locate] = tmp;
    judge_exchange(heap,minimum,count);
}




void heap_sort(node *heap[],int count)
{
    int i = count - 1;
    for (i; i >= 2;)
    {
        //swap(&heap[1], &heap[i]);
        node*tmp=heap[0];
        heap[0]=heap[i];
        heap[i]=tmp;
        i--;
        judge_exchange(heap, 0, i);
    }
}

void heap_create(node *heap[],int count) // small root
{
    int i = count / 2-1;
    for (i; i >= 1; i--)
    {
        judge_exchange(heap, i, count);
    }
}


void insert(node *tree[], node *newnode,int count)
{
    tree[count] = newnode;
    judge_exchange(tree,(count-1)/2,count+1);
}

void Haffman(node *tree[],int k, int count)
{
    int i = 0;
    for (i = 0; i < k - 1; i++)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 1;
        //newnode->parent=NULL;
        newnode->ifprint = 0;
        newnode->left = tree[--count];
        newnode->right = tree[--count];
        newnode->left->flag = 0;
        newnode->right->flag = 1;
        newnode->frequency = newnode->left->frequency + newnode->right->frequency;
        insert(tree, newnode,count);
        count++;
        heap_sort(tree,count);
    }
}
void print(node *root)
{
    if (root == NULL)
        return;
    node *tmp = root;
    char str[1000] = {'\0'};
    while (1)
    {
        if (tmp == NULL)
            break;
        if (tmp->left != NULL)
        {
            tmp = tmp->left;
            strncat(str, "0", 1);
        }
        else if (tmp->right != NULL)
        {
            tmp = tmp->right;
            strncat(str, "1", 1);
        }
        else
        {
            free(tmp);
            tmp = NULL;
            break;
        }
        if (tmp->ifempty != 0)
        {
            printf("%c:%s", tmp->key, str);
            free(tmp);
            tmp = NULL;
            break;
        }
    }
    print(root);
}
int main()
{
    int count = 0, k=0;
    scanf("%d", &k);
    int i = 0;
    scanf("%d", &k);
    node *tree[150];
    for (i = 0; i < 150; i++)
    {
        tree[i] = NULL;
    }
    for (i = 0; i < k; i++)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 0;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->ifprint = 0;
        getchar();
        scanf("%c", &newnode->key);
        scanf("%d", &newnode->frequency);
        tree[count++] = newnode;
    }
    Haffman(tree,k,count);
    // print(tree[0]);
    return 0;
}