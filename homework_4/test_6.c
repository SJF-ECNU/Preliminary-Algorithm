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
#define radix 1024                   //以1024作为基数，即2^10，二进制每10位进行一次排序
int depart[] = {0, 10, 20, 30};      //int 类型为-2^31~2^31-1，因此30位的位移足矣覆盖绝大部分int类型数值
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
    if(max>=1073741824||max<=-1073741824) t=4;
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
void randNumsCreate(int *nums, int size, int min, int max, int type)
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
void CardinalSort(int *nums, int size)
{
    int max=nums[0];
    int i=0;
    for(i=0;i<size;i++)
        if(nums[i]>max) 
            max=nums[i];
    int*returnNums=(int*)malloc(sizeof(int)*size);
    int index=1;
    while(max/index>0)
    {
        int bucket[10]={0};
        for(i=0;i<size;i++) bucket[nums[i]/index%10]++;
        for(i=1;i<10;i++) bucket[i]+=bucket[i-1];
        for(i=size-1;i>=0;i--) returnNums[--bucket[nums[i]/index%10]]=nums[i];
        index*=10;
        for(i=0;i<size;i++) nums[i]=returnNums[i];
    }
    free(returnNums);
    returnNums=NULL;
}
int main()
{
    int size, type, max, min;
    LARGE_INTEGER start_count_sort,end_count_sort,start_cardinal_sort,end_cardinal_sort,start_quicksort,end_quicksort,tc;
    printf("请依次输入数组大小，数据最小值，数据最大值，数据类型（我们规定，1为顺序数组，-1为逆序数组，0为乱序数组）：\n");
    scanf("%d%d%d%d", &size, &min, &max, &type);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1, size, min, max, type);
    copy(nums1,nums2,size);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_cardinal_sort);
    RadixSort(nums1, size);
    QueryPerformanceCounter(&end_cardinal_sort);
    printf("time_radixsort= %f second\n",(double)(end_cardinal_sort.QuadPart-start_cardinal_sort.QuadPart)/(double)tc.QuadPart);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_cardinal_sort);
    CardinalSort(nums2, size);
    QueryPerformanceCounter(&end_cardinal_sort);
    printf("time_cardinalsort= %f second\n",(double)(end_cardinal_sort.QuadPart-start_cardinal_sort.QuadPart)/(double)tc.QuadPart);
    free(nums1);
    free(nums2);
}