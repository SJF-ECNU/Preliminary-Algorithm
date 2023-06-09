#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    int frequency;
    char key;
    int flag;
    int ifempty;
    int ifprint;
} node;

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

void Haffman(node *tree[], int k, int count)
{
    int i = 0;
    for (i = 0; i < k - 1; i++)
    {
        heap_sort(tree, count);
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 1;
        newnode->ifprint = 0;
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
void print(node*tree[],int k)
{

}
int main()
{
    int count = 0, k = 0;
    int i = 0;
    scanf("%d", &k);
    node *tree[150];
    node *tree_1[150];
    for (i = 0; i < 150; i++)
    {
        tree[i] = NULL;
        tree_1[i] = NULL;
    }
    for (i = 0; i < k; i++)
    {
        node *newnode = (node *)malloc(sizeof(node));
        newnode->ifempty = 0;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->ifprint = 0;
        newnode->parent = NULL;
        getchar();
        scanf("%c", &newnode->key);
        scanf("%d", &newnode->frequency);
        tree[count++] = newnode;
        tree_1[i] = newnode;
    }
    heap_create(tree, count);
    Haffman(tree, k, count);
    int size = 0;
    for (i = 0; i < k; i++)
    {
        size = tree_1[i]->frequency + size;
    }
    printf("%.2f", (double)meansize(tree_1, k) / (double)size);
    heap_create(tree_1,k);
    heap_sort(tree_1,k);
    return 0;
}