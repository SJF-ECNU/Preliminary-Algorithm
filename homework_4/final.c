#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<windows.h>

void copy(int *arr1,int *arr2,int size)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        arr2[i]=arr1[i];
    }
}

void swap( int *A, int *B)
{
    int exchange=*(A);
    *(A)=*(B);
    *(B)=exchange;
}

#define radix 1024 
                  //以1024作为基数，即2^10，二进制每10位进行一次排序
int depart[] = {0, 10, 20, 30};      //int 类型为-2^31~2^31-1，因此30位的位移足矣覆盖大部分int类型数值
int get_location(int num, int index) //除法相当于去除需要进行运算的区间后面多余的部分，取模相当于去除需要区间前面多余的部分
{
    return num >> depart[index] & (radix - 1); //对于除法操作，可以通过右位移来实现，根据depart数组，四次分别移动0，10,20,30位，基本可以覆盖int类型，而对于取模操作，由于radix为1024，是2的10次方，可以通过按位与1024-1来进行
}

void RadixSort(int *nums, int size)
{
    int *bucket = (int *)malloc(sizeof(int) * size);
    int count[radix];
    int i = 0;
    int t,max=nums[0];
    for (i = 1; i < size; i++)
    {
        if (nums[i] > max)
            max = nums[i];
    }
    if(max>=1073741824||max<=-1073741824) t=4;//根据数据的范围决定循环次数
    else if(max>=1048576||max<=-1048576) t=3;
    else if(max>=1024||max<=-1024) t=2;
    else t=1;
    t=4;
    for (i = 0; i < t; i++) //i的上限可以根据数据范围改变
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
    int length = max - min + 1;
    int *help = (int *)malloc(sizeof(int) * length);
    memset(help, 0, sizeof(int) * length);
    for (i = 0; i < size; i++)
    {
        help[nums[i] - min]++;
    }
    int j = 0;
    i = 0;
    while (j <length)
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
void randNumsCreate(int *nums, int size, int min, int max, int type)//随机数生成
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = ((rand() << 15) | (rand() << 1 )| (rand()& 1)) % (max-min+1) + min;
    if (type == 0)
        return;
    RadixSort(nums, size);
    if (type == 1)
        return;
    else
    {
        for (i = 0; i < size / 2; i++)
        {
            int tmp = nums[i];
            nums[i] = nums[size - 1 - i];
            nums[size - 1 - i] = tmp;
        }
        return;
    }
}
//qsort
int split(int *a, int low, int high)
{
    int i = high + 1, j = high;
    for (j; j > low; j--)
    {
        if (a[j] > a[low])
        {
            if (a[j] > a[--i])
            {
                int exchange = a[j];
                a[j] = a[i];
                a[i] = exchange;
            }
        }
    }
    int exchange = a[low];
    a[low] = a[i - 1];
    a[i - 1] = exchange;
    return i - 1;
}
int returnmid(int *nums, int low, int high)
{
    int mid = (low + high) / 2;
    if (nums[low] > nums[mid])
    {
        if (nums[high] < nums[mid])
            return mid;
        else if (nums[high] > nums[low])
            return low;
        else
            return high;
    }
    else
    {
        if (nums[high] > nums[mid])
            return mid;
        else if (nums[high] < nums[low])
            return low;
        else
            return high;
    }
}
void InsertionSort(int *nums, int left, int right)
{
    int i = left;
    for (i = left; i <= right; i++)
    {
        int key = nums[i];
        int j = i - 1;
        for (j; j >= left; j--)
        {
            if (key >= nums[j])
            {
                nums[j + 1] = key;
                break;
            }
            nums[j + 1] = nums[j];
        }
        if (j == left - 1)
            nums[left] = key;
    }
}
void quicksort(int *a, int low, int high)
{
    if (high - low <= 8)
    {
        InsertionSort(a, low, high);
        return;
    }
    int index = returnmid(a, low, high);
    swap(a + low, a + index);
    int middle = split(a, low, high);
    quicksort(a, low, middle - 1);
    quicksort(a, middle + 1, high);
}
//
int main()
{
    int size, type, max, min;
    LARGE_INTEGER start_count_sort,end_count_sort,start_cardinal_sort,end_cardinal_sort,start_quicksort,end_quicksort,tc;
    printf("请依次输入数组大小，数据最小值，数据最大值，数据类型（我们规定，1为顺序数组，-1为逆序数组，0为乱序数组）：\n");
    scanf("%d%d%d%d", &size, &min, &max, &type);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    int *nums3 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1, size, min, max, type);
    copy(nums1,nums2,size);
    copy(nums1,nums3,size); 
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_count_sort);
    CountSort(nums1,size);
    QueryPerformanceCounter(&end_count_sort);
    printf("time_countsort= %f second\n",(double)(end_count_sort.QuadPart-start_count_sort.QuadPart)/(double)tc.QuadPart);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_cardinal_sort);
    RadixSort(nums2, size);
    QueryPerformanceCounter(&end_cardinal_sort);
    printf("time_radixsort= %f second\n",(double)(end_cardinal_sort.QuadPart-start_cardinal_sort.QuadPart)/(double)tc.QuadPart);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_quicksort);
    quicksort(nums3,0,size-1);
    QueryPerformanceCounter(&end_quicksort);
    //for(int i=0;i<size;i++) printf("%d ",nums1[i]);
    printf("time_quicksort= %f second\n",(double)(end_quicksort.QuadPart-start_quicksort.QuadPart)/(double)tc.QuadPart);
    free(nums1);
    free(nums2);
    free(nums3);
    return 0;
}