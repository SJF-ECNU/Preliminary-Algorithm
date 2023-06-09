#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int flag[52];//用于和取最小值函数配合，记录是否被插入哈夫曼树


typedef struct node
{
    struct node*left;
    struct node*right;
    struct node*parent;
    // int frequency;
    char key;
    int flag;
}node;



void frequency_counter(char string[],int frequencyTab[])
{
    int length=strlen(string);
    int i=0;
    for(i=0;i<length;i++)
    {
        int location=string[i];
        if(location>=65&&location<=90)
        {
            location-='A';
        }
        else
        {
            location-='a';
            location+=26;
        }
        frequencyTab[location]++;
    }
}



char getMin(int frequencyTab[])
{
    int location=0;
    int min=frequencyTab[0];
    int i=0;
    for(i=0;i<52;i++)
    {
        if(flag[i]==0)
        min=frequencyTab[i];
        location=i;
    }
    for(i=0;i<52;i++)
    {
        if(frequencyTab[i]<=min&&flag[i]==0)
        {
            location=i;
            min=frequencyTab[i];
        }
    }
    flag[location]=1;
    if(location>=26)
    {
        return('a'+location-26);
    }
    else
    {
        return('A'+location);
    }
}

int getfrequency(char target,int frequencyTab[])
{
    if(target>=65&&target<=90) return frequencyTab[target-'A'];
    return frequencyTab[target-'a'+26];
}

void Huffman(int frequencyTab[],node*root)
{
    int i=0;
    char x=getMin(frequencyTab);
    char y=getMin(frequencyTab);
    // int x_frequency=getfrequency(x,frequencyTab);
    // int y_frequency=getfrequency(y,frequencyTab);

    node*left=(node*)malloc(sizeof(node));
    left->parent=root;
    // left->frequency=x_frequency;
    left->key=x;
    left->left=NULL;
    left->right=NULL;
    left->flag=0;


    node*right=(node*)malloc(sizeof(node));
    right->parent=root;
    // right->frequency=y_frequency;
    right->key=y;
    right->left=NULL;
    right->right=NULL;
    right->flag=0;

    root->left=left;
    root->right=right;
    
    // root->frequency=x_frequency+y_frequency;
    for(i=2;i<52;i++)
    {



        char target_left=getMin(frequencyTab);
        int target__left_frequency=getfrequency(target_left,frequencyTab);



        node*newleft=(node*)malloc(sizeof(node));
        newleft->flag=0;
        newleft->key=target_left;
        // newleft->frequency=target__left_frequency;
        newleft->left=NULL;
        newleft->right=NULL;
        newleft->parent=root;



        node*newright=(node*)malloc(sizeof(node));
        newright->left=root->left;
        newright->right=root->right;
        newright->flag=1;
        newright->key='*';
        newright->parent=root;



        root->left->parent=newright;
        root->right->parent=newright;
        root->left=newleft;
        root->right=newright;
    }
}


int main()
{
    char string[5]={'a','b','a','a','a'};
    int frequencyTab[52];
    int i=0;
    for(i=0;i<52;i++)
    {
        frequencyTab[i]=0;
        flag[i]=0;
    }
    frequency_counter(string,frequencyTab);
    node*root=(node*)malloc(sizeof(node));
    root->parent=NULL;
    root->left=NULL;
    root->right=NULL;
    root->flag=1;
    root->key='*';
    Huffman(frequencyTab,root);
    return 0;
}

