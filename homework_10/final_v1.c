#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
int Max(int x, int y)
{
    if (x >= y)
        return x;
    return y;
}
int DynamicStyle(int nums_input[], int length)
{
    int maximum = 1;
    int *MaxSize = (int *)malloc(sizeof(int) * length);
    int i = 0, j = 0;
    for (i = 0; i < length; i++)
        MaxSize[i] = 1;
    // MaxSize[0]=1;
    for (i = 1; i < length; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (MaxSize[i] == maximum)
            {
                MaxSize[i]++;
                maximum++;
                break;
            }
            if (nums_input[j] < nums_input[i])
            {
                MaxSize[i] = Max(MaxSize[i], MaxSize[j] + 1);
            }
        }
    }
    int returnnum = 1;
    for (i = 0; i < length; i++)
    {
        if (returnnum < MaxSize[i])
            returnnum = MaxSize[i];
    }
    free(MaxSize);
    return returnnum;
}
int search(int nums[], int left, int right, int target)
{
    if (left == right)
        return left;
    int mid = (left + right) / 2;
    if (nums[mid] < target)
    {
        if (nums[mid + 1] > target)
            return mid + 1;
        return search(nums, mid + 1, right, target);
    }
    else
    {
        if (mid == 0)
            return mid;
        if (nums[mid - 1] < target)
            return mid;
        return search(nums, left, mid - 1, target);
    }
}
int Greedy(int nums_input[], int length)
{
    int *MinNum = (int *)malloc(sizeof(int) * length);
    // memset(MinNum,0,length);
    MinNum[0] = nums_input[0];
    int MaxSize = 0;
    int i = 0;
    for (i = 1; i < length; i++)
    {
        if (nums_input[i] > MinNum[MaxSize])
        {
            MinNum[++MaxSize] = nums_input[i];
        }
        else
        {
            MinNum[search(MinNum, 0, MaxSize, nums_input[i])] = nums_input[i];
        }
    }
    free(MinNum);
    return MaxSize + 1;
}
void randomnums(int N, int nums[])
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < N; i++)
    {
        nums[i] = ((rand() << 16) | (rand() << 1) | (rand() & 1));
    }
}
int main()
{
    int K = 0;
    scanf("%d", &K);
    int i = 0;
    int *nums = (int *)malloc(sizeof(int) * K);
    randomnums(K, nums);
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    printf("%d\n", Greedy(nums, K));
    QueryPerformanceCounter(&t2);
    printf("time_greedy = %.7f second\n", (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
    QueryPerformanceCounter(&t1);
    printf("%d\n", DynamicStyle(nums, K));
    QueryPerformanceCounter(&t2);
    printf("time_dynamic = %.7f second\n", (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
    free(nums);
    return 0;
}