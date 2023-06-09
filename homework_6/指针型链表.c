#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void merge(int nums[], int min, int max, int type)
{
    if (type == 1)
    {
        int mid = (min + max) / 2;
        int *tmp = (int *)malloc(sizeof(int) * (max - min + 1));
        int i = min, j = mid + 1, index = 0;
        while (i <= mid && j <= max)
        {
            if (nums[i] <= nums[j])
                tmp[index++] = nums[i++];
            else
                tmp[index++] = nums[j++];
        }
        while (i <= mid)
            tmp[index++] = nums[i++];
        while (j <= max)
            tmp[index++] = nums[j++];
        i = min, index = 0;
        while (i <= max)
        {
            nums[i++] = tmp[index++];
        }
        free(tmp);
        tmp = NULL;
    }
    else
        return;
}
void merge_run(int nums[], int min, int max, int type)
{
    if (min >= max || nums == NULL)
        return;
    int mid = (min + max) / 2;
    merge_run(nums, min, mid, type);
    merge_run(nums, mid + 1, max, type);
    merge(nums, min, max, type);
    return;
}


typedef struct node
{
    int num;
    struct node *pre;
    struct node *next;
} node;
int count = 0;
void insert(node *head)
{
    int key, location;
    scanf("%d%d", &location, &key);
    if (location >= count)
    {
        node *tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        node *newNode = (node *)malloc(sizeof(node));
        newNode->next = NULL;
        newNode->pre = tmp;
        newNode->num = key;
        tmp->next = newNode;
        count++;
        return;
    }
    else
    {
        node *tmp = head;
        int i = 0;
        for (i = 0; i <= location; i++)
        {
            tmp = tmp->next;
        }
        node *newNode = (node *)malloc(sizeof(node));
        newNode->next = tmp;
        newNode->pre = tmp->pre;
        newNode->num = key;
        tmp->pre->next = newNode;
        tmp->pre = newNode;
        count++;
    }
}
void delete(node *head)
{
    int location = 0;
    scanf("%d", &location);
    int i = 0;
    node *tmp = head;
    for (i = 0; i <= location; i++)
    {
        tmp = tmp->next;
    }
    if (location < count - 1)
    {
        tmp->pre->next = tmp->next;
        tmp->next->pre = tmp->pre;
        free(tmp);
        tmp = NULL;
        count--;
    }
    else
    {
        tmp->pre->next=NULL;
        free(tmp);
        tmp=NULL;
        count--;
    }
}
void print(node*head)
{
    if(count==0)
    {
        printf("\n");
        return;
    }
    node*tmp=head->next;
    int i=0;
    for(i=0;i<count;i++)
    {
        printf("%d ",tmp->num);
        tmp=tmp->next;
    }
    printf("\n");
}
void search(node*head)
{
    int location,i;
    scanf("%d",&location);
    node*tmp=head;
    for(i=0;i<=location;i++)
    {
        tmp=tmp->next;
    }
    printf("%d\n",tmp->num);
}
void sort(node*head)
{
    int*sort_nums=(int*)malloc(sizeof(int)*count);
    node*tmp=head->next;
    int i=0;
    for(i=0;i<count;i++)
    {
        sort_nums[i]=tmp->num;
        tmp=tmp->next;
    }
    merge_run(sort_nums,0,count-1,1);
    for(i=0,tmp=head->next;i<count;i++)
    {
        tmp->num=sort_nums[i];
    }
    free(sort_nums);
    sort_nums=NULL;
    return;
}
void change(node*head)
{
    int location=0,key=0;
    scanf("%d%d",&location,&key);
    node*tmp=head->next;
    for(int i=0;i<location;i++)
    {
        tmp=tmp->next;
    }
    tmp->num=key;
    return;
}
int main()
{
    node*head=(node*)malloc(sizeof(node));
    int size,i;
    scanf("%d",&size);
    for(i=0;i<size;i++)
    {
        int type=0;
        scanf("%d",&type);
        switch (type)
        {
        case 0:
            insert(head);
            print(head);
            break;
        
        case 1:
            delete (head);
            print(head);
            break;
        case 2:
            search(head);
            break;
        case 3:
            change(head);
            print(head);
            break;
        case 4:
            sort(head);
            print(head);
            break;
        default:
            break;
        }
    }
    node*tmp=head;
    while(tmp->next!=NULL)
    {
        node*F=tmp;
        tmp=tmp->next;
        free(F);
        F=NULL;
    }
    free(tmp);
    tmp=NULL;
    return 0;
}