#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
void copy(int *arr1,int *arr2,int size)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        arr2[i]=arr1[i];
    }
}
int pow_my(int num, int index)
{
    int i = 0;
    int j = 1;
    for (i = 0; i < index; i++)
        j = j * num;
    return j;
}
void randNumsCreate(int *nums, int size, int max)
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = ((rand() << 15 | rand() << 1 | rand() & 1) % max + 1);
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
void CountSort(int*nums,int size,int max)
{
    int i=0;
    int*help=(int*)malloc(sizeof(int)*max);
    for(i=0;i<max;i++) help[i]=0;
    for(i=0;i<size;i++)
    {
        help[nums[i]-1]++;
    }
    int j=0;
    i=0;
    while(j<max)
    {
        int t=0;
        while(t<help[j])
        {
            nums[i++]=j+1;
            t++;
        }
        j++;
    }
    free(help);
    help=NULL;
}
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
void swap( int *A, int *B)
{
    int exchange=*(A);
    *(A)=*(B);
    *(B)=exchange;
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

int main()
{
    LARGE_INTEGER start_count_sort,end_count_sort,start_cardinal_sort,end_cardinal_sort,start_quicksort,end_quicksort,tc;
    int size, index,max,i;
    printf("please input size and index:\n");
    scanf("%d%d", &size,&index);
    max=pow_my(10,index);
    int *nums1 = (int *)malloc(sizeof(int) * size);
    int *nums2 = (int *)malloc(sizeof(int) * size);
    int *nums3 = (int *)malloc(sizeof(int) * size);
    randNumsCreate(nums1,size,max);
    copy(nums1,nums2,size);
    copy(nums1,nums3,size);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_count_sort);
    CountSort(nums1,size,max);
    QueryPerformanceCounter(&end_count_sort);
    printf("time_countsort= %f second\n",(double)(end_count_sort.QuadPart-start_count_sort.QuadPart)/(double)tc.QuadPart);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_cardinal_sort);
    CardinalSort(nums2, size);
    QueryPerformanceCounter(&end_cardinal_sort);
    printf("time_cardinalsort= %f second\n",(double)(end_cardinal_sort.QuadPart-start_cardinal_sort.QuadPart)/tc.QuadPart);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start_quicksort);
    quicksort(nums3,0,size-1);
    QueryPerformanceCounter(&end_quicksort);
    //for(i=0;i<size;i++) printf("%d ",nums3[i]);
    printf("time_quicksort= %f second\n",(double)(end_quicksort.QuadPart-start_quicksort.QuadPart)/tc.QuadPart);
    free(nums1);
    free(nums2);
    free(nums3);
    return 0;
}