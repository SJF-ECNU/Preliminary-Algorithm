#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
//实验需要的外部函数 交换、复制、排序、生成
void copy(int *arr1, int *arr2, int size)
{
    int i = 1;
    for (i = 1; i <= size; i++)
    {
        arr2[i] = arr1[i];
    }
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
#define radix 1024 
int depart[] = {0, 10, 20, 30};      
int get_location(int num, int index) 
{
    return num >> depart[index] & (radix - 1); 
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
    for (i = 0; i < t; i++) 
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








//首先实现期望为线性的选择
int partition(int nums[], int low, int high)
{
    int i = low, j = low-1;
    for (i; i <high; i++)
    {
        if (nums[i] < nums[high])
        {
            if (nums[i] < nums[++j])
            {
                swap(&nums[i], &nums[j]);
            }
        }
    }
    swap(&nums[high], &nums[j + 1]);
    return j + 1;
}
void random_select(int nums[], int low, int high, int target)
{
    srand((unsigned)time(NULL) + rand());
    if (high - low > 1)
    {
        int tmp = (double)rand() / RAND_MAX * (high - low) + low + 1;
        int max = high, min = low;
        if (nums[max] < nums[min])
        {
            max = low, min = high;
        }
        if (nums[tmp] <= nums[max] && nums[tmp] >= nums[min])
            swap(&nums[tmp], &nums[high]);
        else if (nums[tmp] > nums[max])
            swap(&nums[max], &nums[high]);
        else
            swap(nums + min, nums + high);
    }
    int middle = partition(nums, low, high);
    if (middle == target)
        return;
    else if (middle > target)
        random_select(nums, low, middle - 1, target);
    else
        random_select(nums, middle + 1, high, target);
}











//下面实现最坏情况为线性的select算法
void my_select(int nums[], int left, int right, int target);
#define length 5//单组长度
void insertion_sort(int nums[], int left, int right)
{
    if (left == right)
        return;
    int i = left, j = 0;
    while (i <= right)
    {
        int key = nums[i];
        j = i - 1;
        while(j >= left)
        {
            if (key >= nums[j])
            {
                nums[j + 1] = key;
                break;
            }
            nums[j + 1] = nums[j];
            j--;
        }
        if (j == left - 1)
            nums[left] = key;
        i++;
    }
}
int get_mid(int nums[], int left, int right)
{
    if (right - left <= length)
    {
        insertion_sort(nums, left, right);
        return nums[(left + right) / 2];
    }
    int size = (right - left + 1) / length;
    if (size * length < right + left + 1)
        size++;
    int *midnums = (int *)malloc(sizeof(int) * size);
    int i, j;
    for (i = 0, j = 0; i < size - 1; i++)
    {
        midnums[i] = get_mid(nums, left + j, left + j + length - 1);
        j += length;
    }
    midnums[i] = get_mid(nums, left + j, right);
    my_select(midnums,0,size-1,size/2-1);
    int returnNum = midnums[size/2-1];
    free(midnums);
    return returnNum;
}
void my_select(int nums[], int left, int right, int target)
{
    int mid = get_mid(nums, left, right);
    int i = 0;
    for (i = left; i <= right; i++)
    {
        if (nums[i] == mid)
        {
            swap(&nums[i], &nums[right]);
            break;
        }
    }
    int part=partition(nums,left,right);
    if (part==target)
        return;
    else if (part > target)
        my_select(nums, left, part - 1, target);
    else
        my_select(nums, part + 1, right, target);
}











int main()
{
    int n=1000000,min=1,max=10000000,type=0;
    //printf("请依次输入数据量、数据最小值、数据最大值、数据类型、分位数，我们规定，1为顺序，-1为逆序，0为乱序\n");
    //scanf("%d%d%d%d", &n,&min,&max,&type);
    int*nums1=(int*)malloc(sizeof(int)*n);
    int*nums2=(int*)malloc(sizeof(int)*n);
    int*nums3=(int*)malloc(sizeof(int)*n);
    randNumsCreate(nums1,n,min,max,type);
    copy(nums1,nums2,n);
    copy(nums1,nums3,n);
    LARGE_INTEGER start_select,end_select,start_random_sel,end_random_sel,start_merge,end_merge,Tc;
    int key = n*0.4;
    QueryPerformanceFrequency(&Tc);
    QueryPerformanceCounter(&start_select);
    my_select(nums1, 0, n - 1, key - 1);
    QueryPerformanceCounter(&end_select);
    printf("分组选择选择耗时：%f 秒\n",(double)(end_select.QuadPart-start_select.QuadPart)/(double)Tc.QuadPart);
    QueryPerformanceFrequency(&Tc);
    QueryPerformanceCounter(&start_random_sel);
    random_select(nums2,0,n-1,key-1);
    QueryPerformanceCounter(&end_random_sel);
    printf("随机选择耗时：%f 秒\n",(double)(end_random_sel.QuadPart-start_random_sel.QuadPart)/(double)Tc.QuadPart);
    // QueryPerformanceFrequency(&Tc);
    // QueryPerformanceCounter(&start_merge);
    // merge_run(nums3,0,n-1,1);
    // QueryPerformanceCounter(&end_merge);
    // printf("归并排序：%f 秒\n",(double)(end_merge.QuadPart-start_merge.QuadPart)/(double)Tc.QuadPart);
    return 0;
}