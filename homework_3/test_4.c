#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
void InsertionSort(int *nums, int left, int right);
void randomnumsCreate(int size, int *nums, int min, int max)
{
    srand((unsigned)time(NULL) + rand());
    int i = 1;
    for (i = 1; i <= size; i++)
    {
        nums[i] = (double)rand()/RAND_MAX*(max - min + 1) + min;
    }
}
void swap(int *A, int *B)
{
    int exchange = *(A);
    *(A) = *(B);
    *(B) = exchange;
}
void judge_exchange(int *nums, int size, int locate)
{
    int left = locate * 2;
    int right = locate * 2 + 1;
    int largest = locate;
    if (right <= size && nums[right] > nums[largest])
        largest = right;
    if (left <= size && nums[left] > nums[largest])
        largest = left;
    if (largest == locate)
        return;
    swap(&nums[largest], &nums[locate]);
    judge_exchange(nums, size, largest);
}
void heap_create(int *nums, int size) //big root
{
    int i = size / 2;
    for (i; i >= 1; i--)
    {
        judge_exchange(nums, size, i);
    }
}
void heap_sort(int *nums, int size)
{
    int i = size;
    for (i; i >= 2;)
    {
        swap(&nums[1], &nums[i]);
        i--;
        judge_exchange(nums, i, 1);
    }
}
void copy(int *arr1, int *arr2, int size)
{
    int i = 1;
    for (i = 1; i <= size; i++)
    {
        arr2[i] = arr1[i];
    }
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
int main()
{
    int size=0;
    //scanf("%d",&size);
    scanf("%d",&size);
    LARGE_INTEGER t1,t2,t3,t4,tc;
    int *nums1=(int*)malloc(sizeof(int)*(size+1));
    int *nums2=(int*)malloc(sizeof(int)*(size+1));
    randomnumsCreate(size,nums1,0,100000000);
    copy(nums1,nums2,size);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    heap_create(nums1,size);
    heap_sort(nums1,size);
    QueryPerformanceCounter(&t2);
    printf("time_heapsort= %f second\n",(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart);
    //int i;
    //for(i=1;i<=size;i++) printf("%d ",nums1[i]);
    //printf("\n");
    free(nums1);
    nums1=NULL;
    QueryPerformanceCounter(&t3);
    quicksort(nums2,1,size);
    QueryPerformanceCounter(&t4);
    //for(i=1;i<=size;i++) printf("%d ",nums2[i]);
    printf("time_quicksort= %f second\n",(double)(t4.QuadPart-t3.QuadPart)/(double)tc.QuadPart);
    free(nums2);
    nums2=NULL;
    return 0;
}