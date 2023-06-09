#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int exponential(int num, int index)
{
    int i = 0;
    int j = 1;
    for (i = 0; i < index; i++)
        j = j * num;
    return j;
}
int randomNum(int max)
{
    return ((rand() << 15 | rand() << 1 | rand() & 1) % max + 1);
}
void randNumsCreate(int *nums, int size, int max)
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = (double)rand() / RAND_MAX * max + 1;
}
void CardinalSort(int *nums, int size)
{
    int max = nums[0];
    int i = 0;
    for (i = 0; i < size; i++)
        if (nums[i] > max)
            max = nums[i];
    int *returnNums = (int *)malloc(sizeof(int) * size);
    int index = 1;
    while (max / index > 0)
    {
        int bucket[10] = {0};
        for (i = 0; i < size; i++)
            bucket[nums[i] / index % 10]++;
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = size - 1; i >= 0; i--)
            returnNums[--bucket[nums[i] / index % 10]] = nums[i];
        index *= 10;
        for (i = 0; i < size; i++)
            nums[i] = returnNums[i];
    }
    free(returnNums);
    returnNums = NULL;
}
void CountSort(int *nums, int size, int max)
{
    int i = 0;
    int *help = (int *)malloc(sizeof(int) * max);
    for (i = 0; i < max; i++)
        help[i] = 0;
    for (i = 0; i < size; i++)
    {
        help[nums[i] - 1]++;
    }
    int j = 0;
    i = 0;
    while (j < max)
    {
        int t = 0;
        while (t < help[j])
        {
            nums[i++] = j + 1;
            t++;
        }
        j++;
    }
    free(help);
    help = NULL;
}
int main()
{
    int size, index, max, i;
    time_t start_count_sort, end_count_sort, start_cardinal_sort, end_cardinal_sort;
    printf("please input size and index:\n");
    scanf("%d%d", &size, &index);
    max = exponential(10, max);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1, size, exponential(10, max));
    for (i = 0; i < size; i++)
        nums2 = nums1;
    //for (i = 0; i < size; i++)
    //    scanf("%d", &nums[i]);
    start_count_sort = clock();
    CountSort(nums1, size, exponential(10, max));
    end_count_sort = clock();
    //for(i=0;i<size;i++) printf("%d ",nums1[i]);
    //printf("\n");
    printf("time_count_sort= %f second\n", (double)(end_count_sort - start_count_sort) / CLOCKS_PER_SEC);
    start_cardinal_sort = clock();
    CardinalSort(nums2, size);
    end_cardinal_sort = clock();
    //for(i=0;i<size;i++) printf("%d ",nums2[i]);
    //printf("\n");
    printf("time_cardinal_count_sort= %f second\n", (double)(end_cardinal_sort - start_cardinal_sort) / CLOCKS_PER_SEC);
    return 0;
}