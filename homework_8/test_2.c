#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void randomNums(int N, int *root)
{
    srand((unsigned)time(NULL) + rand());
    int *arr = (int *)calloc(10000000, sizeof(int));
    int i = 0, j = 0;
    for (i = 0; i < N;)
    {
        int num = ((rand() << 16) | (rand() << 1) | (rand() & 1));
        if (num < 0)
            num = -num;
        num = num % 10000000;
        if (arr[num] == 0)
        {
            arr[num] = 1;
            root[i++] = num;
        }
    }
}

//二叉搜索树
typedef struct Tree
{
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

//树的插入
void tree_insert(Tree *root, int key)
{
    int num = key;
    Tree *x = root;
    Tree *tmp = NULL;
    int i = 0;
    while (x != NULL)
    {
        tmp = x;
        if (num >= x->key)
            x = x->right;
        else
            x = x->left;
    }
    Tree *new_branch = (Tree *)malloc(sizeof(Tree));
    new_branch->key = num;
    new_branch->left = NULL;
    new_branch->right = NULL;
    new_branch->parent = tmp;
    if (tmp->key <= num)
        tmp->right = new_branch;
    else
        tmp->left = new_branch;
}

//搜索
Tree *tree_search(Tree *root, int target)
{
    Tree *x = root;
    while (x != NULL)
    {
        if (x->key == target)
            return x;
        else if (target > x->key)
            x = x->right;
        else
            x = x->left;
    }
    return x;
}

void Max(Tree *root)
{
    if (root == NULL)
        return;
    Tree *tmp = root;
    while (tmp->right != NULL)
    {
        tmp = tmp->right;
    }
    printf("%d\n", tmp->key);
}

void Min(Tree *root)
{
    if (root == NULL)
        return;
    Tree *tmp = root;
    while (tmp->left != NULL)
    {
        tmp = tmp->left;
    }
    printf("%d\n", tmp->key);
}

void successor(Tree *root, int key)
{
    Tree *tmp = tree_search(root, key);
    if (tmp->right != NULL)
        Min(tmp->right);
    else
    {
        Tree *par = tmp->parent;
        while (par != NULL && tmp == par->right)
        {
            tmp = par;
            par = par->parent;
        }
        if (par != NULL)
            printf("%d\n", par->key);
    }
}

void predecessor(Tree *root, int key)
{
    Tree *tmp = tree_search(root, key);
    if (tmp->left != NULL)
        Max(tmp->left);
    else
    {
        Tree *par = tmp->parent;
        while (par != NULL && par->left == tmp)
        {
            tmp = par;
            par = par->parent;
        }
        if (par != NULL)
            printf("%d\n", par->key);
    }
}

void print_pre(Tree *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->key);
    print_pre(root->left);
    print_pre(root->right);
}
void print_mid(Tree *root)
{
    if (root == NULL)
        return;
    print_pre(root->left);
    printf("%d ", root->key);
    print_pre(root->right);
}
void print_aft(Tree *root)
{
    if (root == NULL)
        return;
    print_pre(root->left);
    print_pre(root->right);
    printf("%d ", root->key);
}
//散列表
#define size 200000
typedef struct HashTable
{
    int count;
    int arr[size];
    int flag[size];
} hash;
// h1(k)=k%m_1,h2(k)=k%m_2+1
#define m_1 size
#define m_2 (size - 3)
#define h_1(k) ((k) % (m_1))
#define h_2(k) ((k) % (m_2) + 1)
void hash_insert(hash *hashtable, int key)
{
    if (hashtable->count == size)
    {
        printf("full!\n");
        return;
    }
    int tmp = key;
    if (key < 0)
        tmp = -key;
    int i = 0;
    for (i = 0; i <= hashtable->count; i++)
    {
        int location = (h_1(tmp) + i * h_2(tmp)) % size;
        if (hashtable->flag[location] == 0)
        {
            hashtable->flag[location] = 1;
            hashtable->count++;
            hashtable->arr[location] = key;
            return;
        }
    }
}

void hash_search(hash *hashtable, int key)
{
    int i = 0;
    int tmp = key;
    if (key < 0)
        tmp = -key;
    int location = (h_1(tmp) + i * h_2(tmp)) % size;
    for (i = 0; hashtable->flag[location] != 0; i++)
    {
        location = (h_1(tmp) + i * h_2(tmp)) % size;
        if (hashtable->flag[location] == 1 && hashtable->arr[location] == key)
        {
            // printf("yes\n");
            return;
        }
    }
    // printf("no\n");
    return;
}

// 顺序访问
typedef struct array
{
    int count;
    int arr[size];
} array;
void array_insert(array *nums, int key)
{
    nums->arr[nums->count++] = key;
}
void array_search(array *nums, int key)
{
    int i = 0;
    for (i = 0; i < nums->count; i++)
    {
        if (nums->arr[i] == key)
        {
            // printf("yes\n");
            return;
        }
    }
    // printf("no\n");
    return;
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    int *input = (int *)malloc(sizeof(int) * N);
    Tree *root = (Tree *)malloc(sizeof(Tree));
    hash *hashtable = (hash *)malloc(sizeof(hash));
    array *nums = (array *)malloc(sizeof(array));
    nums->count = 0;
    randomNums(N, input);
    root->key = input[0];
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    int i = 1;
    for (i = 1; i < N; i++)
    {
        tree_insert(root, input[i]);
        hash_insert(hashtable, input[i]);
        array_insert(nums, input[i]);
    }
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    int m;
    scanf("%d", &m);
    int *searchKeys = (int *)malloc(sizeof(int) * m);
    randomNums(m, searchKeys);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < m; i++)
    {
        Tree *tmp = tree_search(root, searchKeys[i]);
    }
    QueryPerformanceCounter(&t2);
    printf("time_tree_search_ %d times = %f\n", m, ((double)t2.QuadPart - (double)t1.QuadPart) / (double)tc.QuadPart);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < m; i++)
    {
        hash_search(hashtable, searchKeys[i]);
    }
    QueryPerformanceCounter(&t2);
    printf("time_hash_search_ %d times = %f\n", m, ((double)t2.QuadPart - (double)t1.QuadPart) / (double)tc.QuadPart);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < m; i++)
    {
        array_search(nums, searchKeys[i]);
    }
    QueryPerformanceCounter(&t2);
    printf("time_array_search_ %d times = %f\n", m, ((double)t2.QuadPart - (double)t1.QuadPart) / (double)tc.QuadPart);
    return 0;
}