#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
const static int radix = 1024;
static int p[] = {0, 10, 20, 30};

int get_part(int n, int i)
{
    return n >> p[i] & (radix - 1);
}

void radix_sort(int *a, int n)
{
    int *bucket = (int *)malloc(sizeof(int) * n);
    int count[radix];

    for (int i = 0; i < 2; ++i)
    {
        memset(count, 0, sizeof(int) * radix);

        for (int j = 0; j < n; ++j)
        {
            count[get_part(a[j], i)]++;
        }

        for (int j = 1; j < radix; ++j)
        {
            count[j] += count[j - 1];
        }

        for (int j = n - 1; j >= 0; --j)
        {
            int k = get_part(a[j], i);
            bucket[count[k] - 1] = a[j];
            count[k]--;
        }

        memcpy(a, bucket, sizeof(int) * n);
    }

    free(bucket);
}
void randNumsCreate(int *nums, int size, int min,int max,int type)
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = (double)rand() / RAND_MAX * max + min;
    if(type==0) return;
    if(type==1) radix_sort(nums,size);
}
void CountSort(int *nums, int size)
{
    int max = nums[0], min = nums[0];
    int i = 0;
    for (i = 1; i < size; i++)
    {
        if (nums[i] > max)
            max = nums[i];
        if (nums[i] < min)
            min = nums[i];
    }
    int length=max-min+1;
    int *help = (int *)malloc(sizeof(int) * length);
    memset(help, 0, sizeof(int) * length);
    for (i = 0; i < size; i++)
    {
        help[nums[i] - min]++;
    }
    int j = 0;
    i = 0;
    while (j < max)
    {
        int t = 0;
        while (t < help[j])
        {
            nums[i++] = j + min;
            t++;
        }
        j++;
    }
    free(help);
    help = NULL;
}
int main()
{
    int size, type, max, i,min;
    time_t start_count_sort, end_count_sort, start_cardinal_sort, end_cardinal_sort;
    printf("请依次输入数组大小，数据最小值，数据最大值，数据类型（我们规定，1为顺序数组，-1为逆序数组，0为乱序数组）：\n");
    scanf("%d%d%d", &size,&min,&max,&type);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1, size, min, max,type);
    for (i = 0; i < size; i++)
        nums2[i] = nums1[i];
    //for (i = 0; i < size; i++)
    //    scanf("%d", &nums1[i]);
    start_count_sort = clock();
    CountSort(nums1, size);
    end_count_sort = clock();
    //for (i = 0; i < size; i++)
    //    printf("%d ", nums1[i]);
    free(nums1);
    nums1=NULL;
    //printf("\n");
    printf("计数排序所用时间= %f 秒\n", (double)(end_count_sort - start_count_sort) / CLOCKS_PER_SEC);
    start_cardinal_sort = clock();
    radix_sort(nums2, size);
    end_cardinal_sort = clock();
    //for (i = 0; i < size; i++)
    //    printf("%d ", nums2[i]);
    free(nums2);
    nums2=NULL;
    //printf("\n");
    printf("基数排序所用时间= %f 秒\n", (double)(end_cardinal_sort - start_cardinal_sort) / CLOCKS_PER_SEC);
    return 0;
}