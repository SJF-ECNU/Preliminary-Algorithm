#include <stdio.h>
#include <stdlib.h>
#include "First.h"
#include <time.h>
void bubble(int nums[],int N)
{
    int i=0,j;
    for(i=0;i<N;i++)
    {
        for(j=i+1;j<N;j++)
        {
            if(nums[i]>nums[j])
            {
                int exchange=nums[i];
                nums[j]=nums[i];
                nums[j]=exchange;
            }
        }
    }
    return;
}
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
        while (i <=max)
        {
            nums[i++] = tmp[index++];
        }
        free(tmp);
        tmp=NULL;
    }
    else return;
}
void merge_run(int nums[], int min, int max, int type)
{
    if (min >= max||nums==NULL)
        return;
    int mid=(min+max)/2;
    merge_run(nums,min,mid,type);
    merge_run(nums,mid+1,max,type);
    merge(nums,min,max,type);
    return;
}
void InsertionSort(int nums[], int N, int type)
{
    if (type == 1)
    {
        int i = 0;
        for (i = 1; i < N; i++)
        {
            int key = nums[i];
            int j = i - 1;
            for (j; j >= 0; j--)
            {
                if (key >= nums[j])
                {
                    nums[j + 1] = key;
                    break;
                }
                nums[j + 1] = nums[j];
            }
            if (j == -1)
                nums[0] = key;
        }
    }
    else
    {
        int i = N;
        for (i = 1; i < N; i++)
        {
            int key = nums[i];
            int j = i - 1;
            for (j; j >= 0; j--)
            {
                if (key <= nums[j])
                {
                    nums[j + 1] = key;
                    break;
                }
                nums[j + 1] = nums[j];
            }
            if (j == -1)
                nums[0] = key;
        }
    }
    return;
}
int *RandomNums(int N, int min, int max, int type)
{
    int i = 0;
    int *ReturnNums = (int *)malloc(sizeof(int) * N);
    srand((unsigned)time(NULL));
    for (i = 0; i < N; i++)
    {
        *(ReturnNums + i) = min + rand() % (max - min + 1);
    }
    if (type == 1)
        merge_run(ReturnNums,0, N-1, 1);
    else if (type == -1)
        merge_run(ReturnNums, 0,N-1, -1);
    return ReturnNums;
}