#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
void randomNums(int N, int *root)
{
    srand((unsigned)time(NULL) + rand());
    int *arr = (int *)calloc(1000000000, sizeof(int));
    int i = 0, j = 0;
    for (i = 0; i < N;)
    {
        int num = ((rand() << 16) | (rand() << 1) | (rand() & 1));
        if (num < 0)
            num = -num;
        num = num % 1000000000;
        if (arr[num] == 0)
        {
            arr[num] = 1;
            root[i++] = num;
        }
    }
}
typedef struct BRtree
{
    int color; // 1 black 0 red
    int key;
    struct BRtree *parent;
    struct BRtree *left;
    struct BRtree *right;
} BRtree;
void left_rotate(BRtree *node, int flag)
{
    BRtree *parent = node->parent;
    parent->right = node->left;
    if (node->left != NULL)
        node->left->parent = parent;
    node->left = parent;
    node->parent = parent->parent;
    parent->parent = node;
    if (flag == 1)
        node->parent->right = node;
    else if (flag == -1)
        node->parent->left = node;
}
void right_rotate(BRtree *node, int flag)
{
    BRtree *parent = node->parent;
    parent->left = node->right;
    if (node->right != NULL)
        node->right->parent = parent;
    node->right = parent;
    node->parent = parent->parent;
    parent->parent = node;
    if (flag == 1)
        node->parent->right = node;
    else if (flag == -1)
        node->parent->left = node;
}
BRtree *BRtree_Fix(BRtree *newNode, BRtree *root)
{
    if (newNode->parent == NULL)
    {
        newNode->color = 1;
        return newNode;
    }
    else if (newNode->parent->parent == NULL)
    {
        newNode->parent->color = 1;
        return newNode->parent;
    }
    else if (newNode->parent->color == 1)
    {
        return root;
    }
    else
    {
        BRtree *parent = newNode->parent;
        BRtree *grand = parent->parent;
        if (grand->left != NULL && grand->right != NULL && grand->left->color == 0 && grand->right->color == 0)
        {
            // if (grand->left->color == 0 && grand->right->color == 0)
            //{
            grand->color = 0;
            grand->left->color = 1;
            grand->right->color = 1;
            return BRtree_Fix(grand, root);
            //}
        }
        else if (grand->left == parent && parent->right == newNode)
        {
            left_rotate(newNode, -1);
            BRtree *tmp = root;
            while (tmp->parent != NULL)
                tmp = tmp->parent;
            return BRtree_Fix(parent, tmp);
        }
        else if (grand->right == parent && parent->left == newNode)
        {
            right_rotate(newNode, 1);
            BRtree *tmp = root;
            while (tmp->parent != NULL)
                tmp = tmp->parent;
            return BRtree_Fix(parent, tmp);
        }
        else if (grand->left == parent && parent->left == newNode)
        {
            int flag = 0;
            if (grand->parent == NULL)
                flag = 0;
            else if (grand->parent->right == grand)
                flag = 1;
            else
                flag = -1;
            right_rotate(parent, flag);
            parent->color = 1;
            grand->color = 0;
        }
        else
        {
            int flag = 0;
            if (grand->parent == NULL)
                flag = 0;
            else if (grand->parent->right == grand)
                flag = 1;
            else
                flag = -1;
            left_rotate(parent, flag);
            parent->color = 1;
            grand->color = 0;
        }
        BRtree *tmp = root;
        while (tmp->parent != NULL)
        {
            tmp = tmp->parent;
        }
        return tmp;
    }
}
BRtree *insert(BRtree *root, int key)
{
    BRtree *tmp = root;
    BRtree *prve = NULL;
    while (tmp != NULL)
    {
        prve = tmp;
        if (key >= tmp->key)
            tmp = tmp->right;
        else
            tmp = tmp->left;
    }
    BRtree *newNode = (BRtree *)malloc(sizeof(BRtree));
    newNode->parent = prve;
    newNode->key = key;
    newNode->color = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    if (prve != NULL)
    {
        if (key >= prve->key)
            prve->right = newNode;
        else
            prve->left = newNode;
    }
    if (root == NULL)
        root = newNode;
    return BRtree_Fix(newNode, root);
}
void BRtree_search(BRtree *root, int key)
{
    BRtree *tmp = root;
    while (tmp != NULL)
    {
        if (key == tmp->key)
        {
            // printf("Yes\n");
            return;
        }
        else if (key >= tmp->key)
            tmp = tmp->right;
        else
            tmp = tmp->left;
    }
    // if (tmp == NULL)printf("No\n");
    return;
}
void mid_print(BRtree *root)
{
    if (root == NULL)
        return;
    mid_print(root->left);
    if (root->color == 1)
        printf("B");
    else
        printf("R");
    mid_print(root->right);
}
// 二叉搜索树
typedef struct Tree
{
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

// 树的插入
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
void tree_search(Tree *root, int target)
{
    Tree *x = root;
    while (x != NULL)
    {
        if (x->key == target)
            {
                //printf("Yes");
                return;
            }
        else if (target > x->key)
            x = x->right;
        else
            x = x->left;
    }
    //if(x==NULL) printf("No");
    return;
}
int main()
{
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    BRtree *root = NULL;
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int i = 0;
    int *nums = (int *)malloc(sizeof(int) * n);
    randomNums(n, nums);
    for (i = 0; i < n; i++)
    {
        root = insert(root, nums[i]);
    }
    Tree *root_1 = (Tree *)malloc(sizeof(Tree));
    root_1->key = nums[0];
    root_1->left = NULL;
    root_1->right = NULL;
    root_1->parent = NULL;
    for (i = 1; i < n; i++)
    {
        tree_insert(root_1, nums[i]);
    }
    randomNums(m, nums);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < m; i++)
    {
        BRtree_search(root, nums[i]);
    }
    QueryPerformanceCounter(&t2);
    printf("time_BRtree = %f\n", (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
    QueryPerformanceCounter(&t1);
    for (i = 0; i < m; i++)
    {
        tree_search(root_1, nums[i]);
    }
    QueryPerformanceCounter(&t2);
    printf("time_tree = %f\n", (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
    return 0;
}