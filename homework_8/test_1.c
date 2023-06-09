#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define size 20
typedef struct tree
{
    int key;
    struct tree*left;
    struct tree*right;
    struct tree*parent;
}tree;
void insert(tree*root,char*key)
{
    if(strcmp(key,"null")==0) return;
    int num=atoi(key);
    tree *x=root;
    tree *tmp=NULL;
    int i=0;
    while(x!=NULL)
    {
        tmp=x;
        if(num>=x->key) x=x->right;
        else x=x->left;
    }
    tree*new_branch=(tree*)malloc(sizeof(tree));
    new_branch->key=num;
    new_branch->left=NULL;
    new_branch->right=NULL;
    new_branch->parent=tmp;
}
tree* search(tree*root,char*key)
{
    if(strcmp(key,"null")==0) return;
    int target=atoi(key);
    tree*x=root;
    while(x!=NULL)
    {
        int x_num=x->key;
        if(x_num==target) return x;
        else if(target>=x_num) x=x->right;
        else x=x->left;
    }
    return x;
}
void max(tree*root)
{
    if(root==NULL) return;
    tree*tmp=root;
    while(tmp->right!=NULL)
    {
        tmp=tmp->right;
    }
    printf("%d\n",tmp->key);
}min(tree*root)
{
void 
    if(root==NULL) return;
    tree*tmp=root;
    while(tmp->left!=NULL)
    {
        tmp=tmp->left;
    }
    printf("%d\n",tmp->key);
}
void successor(tree*root,char*key)
{
    tree*tmp=search(root,key);
    min(tmp->right);
}
void predecessor(tree*root,char*key)
{
    tree*tmp=search(root,key);
    max(tmp->left);
}
void print_pre(tree*root)
{
    if(root->left!=NULL)
    {
        print_pre(root->left);
    }
    printf("%d ",root->key);
    if(root->right!=NULL)
    {
        print_pre(root->right);
    }
}
int main()
{
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    char*input=(char*)malloc(sizeof(char)*10000);
    scanf("%s",input);
    tree*root=(tree*)malloc(sizeof(tree));
    root->key = num;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    int keys[10000];
    int i=0;
    for(i=0;i<10000;i++)
    {
        insert(root,keys[i]);
    }
    return 0;
}