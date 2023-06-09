#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define radix 1024                   //以1024作为基数，即2^10，二进制每10位进行一次排序
int depart[] = {0, 10, 20, 30};      //int 类型为-2^31~2^31-1，因此30位的位移足矣覆盖绝大部分int类型数值
int get_location(int num, int index) //除法相当于去除需要进行运算的区间后面多余的部分，取模相当于去除需要区间前面多余的部分
{
    return num >> depart[index] & (radix - 1); //对于除法操作，可以通过右位移来实现，根据depart数组，四次分别移动0，10,20,30位，基本可以覆盖int类型，而对于取模操作，由于radix为1024，是2的10次方，可以通过按位与1024-1来进行
}
void randNumsCreate(int *nums, int size, int max)
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = (double)rand() / RAND_MAX * max + 1;
}
void RadixSort(int *nums, int size)
{
    int *bucket = (int *)malloc(sizeof(int) * size);
    int count[radix];
    int i = 0;
    for (i = 0; i < 2; i++) //i的上限可以根据数据范围改变
    {
        memset(count, 0, sizeof(int) * radix);
        int j = 0;
        for (j = 0; j < size; j++)
        {
            count[get_location(nums[j], i)]++;
        }
        for (j = 1; j < radix; j++)
        {
            count[j] += count[j - 1];
        }
        for (j = size - 1; j >= 0; j--)
        {
            bucket[--count[get_location(nums[j], i)]] = nums[j];
        }
        for (j = 0; j < size; j++)
            nums[j] = bucket[j];
    }
    free(bucket);
    bucket = NULL;
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
    max = pow(10, index);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1, size, max);
    for (i = 0; i < size; i++)
        nums2[i] = nums1[i];
    //for (i = 0; i < size; i++)
    //    scanf("%d", &nums[i]);
    start_count_sort = clock();
    CountSort(nums1, size, max);
    end_count_sort = clock();
    //for (i = 0; i < size; i++)
    //    printf("%d ", nums1[i]);
    //printf("\n");
    printf("time_count_sort= %f second\n", (double)(end_count_sort - start_count_sort) / CLOCKS_PER_SEC);
    start_cardinal_sort = clock();
    RadixSort(nums2, size);
    end_cardinal_sort = clock();
    //for (i = 0; i < size; i++)
    //    printf("%d ", nums2[i]);
    //printf("\n");
    printf("time_radix_count_sort= %f second\n", (double)(end_cardinal_sort - start_cardinal_sort) / CLOCKS_PER_SEC);
    return 0;
}