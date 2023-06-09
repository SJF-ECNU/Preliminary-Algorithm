#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//链表
int count = 0;
int L = -1;
int F = 0;
void insert(int *List_key, int *List_next, int *List_pre)//插入
{
    int key, location;
    scanf("%d%d", &location, &key);
    if (L == -1)
    {
        L = F;
        F = List_next[F];
        List_next[L] = -1;
        List_key[L] = key;
        List_pre[L] = -1;
        count++;
        return;
    }
    else if (location > count - 1)
    {
        int i = 0;
        int tmp = L;
        for (i = 0; i < count - 1; i++)
        {
            tmp = List_next[tmp];
        }
        List_key[F] = key;
        List_pre[F] = tmp;
        List_next[tmp] = F;
        F = List_next[F];
        List_pre[F] = -1;
        List_next[List_next[tmp]] = -1;
        count++;
        return;
    }
    else if(location>0)
    {
        int i = 0, tmp = L;
        for (i = 0; i < location; i++)
        {
            tmp = List_next[tmp];
        }
        List_key[F] = key;
        int F_next = List_next[F];
        List_next[F] = tmp;
        List_pre[F] = List_pre[tmp];
        List_pre[tmp]=F;
        List_next[List_pre[F]]=F;
        F=F_next;
        count++;
        return;
    }
    else
    {
        int i = 0, tmp = L;
        List_key[F] = key;
        int F_next = List_next[F];
        List_next[F] = L;
        List_pre[F] = -1;
        List_pre[L] = F;
        L = F;
        F = F_next;
        count++;
        return;
    }
}
void delete (int *List_key, int *List_next, int *List_pre)//删除
{
    int location = -1;
    scanf("%d", &location);
    int tmp = L, i = 0;
    for (i = 0; i < location; i++)
    {
        tmp = List_next[tmp];
    }
    if (location>0&&location<count-1)
    {
        List_next[List_pre[tmp]] = List_next[tmp];
        List_pre[List_next[tmp]] = List_pre[tmp];
        List_pre[tmp] = -1;
        List_next[tmp] = F;
        F = tmp;
        count--;
    }
    else if(location==0)
    {
        L=List_next[L];
        List_pre[L] = -1;
        List_next[tmp]=F;
        List_pre[F]=tmp;
        F=tmp;
        count--;
    }
    else if (location==count-1)
    {
        List_next[List_pre[tmp]]=-1;
        List_pre[tmp]=-1;
        List_next[tmp]=F;
        List_pre[F]=tmp;
        F=tmp;
        count--;
    }
    else
    {
        List_next[tmp]=F;
        List_pre[F]=tmp;
        F=tmp;
        count--;
    }
}
void print(int *List_key, int *List_next, int *List_pre)//遍历
{
    if(L==-1) return;
    int tmp = L, i = 0;
    for (i = 0; i < count; i++)
    {
        printf("%d ", List_key[tmp]);
        tmp = List_next[tmp];
    }
    printf("\n");
    return;
}
void search(int *List_key, int *List_next)//寻找
{
    if(L==-1) return;
    int target=0;
    scanf("%d",&target);
    int tmp=L;
    int i=0;
    for(i=0;i<count;i++)
    {
        if(i==target) break;
        tmp=List_next[tmp];
    }
    printf("%d\n",List_key[tmp]);
    return ;
}
void sort(int *List_key, int *List_next)
{
    if(L==-1) return;
    int*sort_nums=(int*)malloc(sizeof(int)*count);
    int i=0,tmp=L;
    for(i=0;i<count;i++)
    {
        sort_nums[i]=List_key[tmp];
        tmp=List_next[tmp];
    }
    merge_run(sort_nums,0,count-1,1);
    for (i = 0,tmp=L; i < count; i++)
    {
        List_key[tmp]=sort_nums[i];
        tmp = List_next[tmp];
    }
    free(sort_nums);
}
void change(int *List_key, int *List_next)
{
    int location=0,tmp=L,i=0,new_key=0;
    scanf("%d%d",&location,&new_key);
    for (i = 0; i < location; i++)
    {
        tmp = List_next[tmp];
    }
    List_key[tmp]=new_key;
    return ;
}
int main()
{
    int size = 0, i = 0;
    scanf("%d", &size);
    int *List_key = (int *)malloc(sizeof(int) * size);
    int *List_next = (int *)malloc(sizeof(int) * size);
    int *List_pre = (int *)malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
    {
        List_pre[i] = i - 1;
        List_next[i] = i + 1;
    }
    List_next[size - 1] = -1;
    for(i=0;i<size;i++)
    {
        int type=0;
        scanf("%d",&type);
        switch (type)
        {
        case 0:
            insert(List_key,List_next,List_pre);
            print(List_key, List_next, List_pre);
            break;
        
        case 1:
            delete (List_key, List_next, List_pre);
            print(List_key, List_next, List_pre);
            break;
        case 2:
            search(List_key, List_next);
            break;
        case 3:
            change(List_key, List_next);
            print(List_key, List_next, List_pre);
            break;
        case 4:
            sort(List_key,List_next);
            print(List_key, List_next, List_pre);
            break;
        default:
            break;
        }
    }
    return 0;
}