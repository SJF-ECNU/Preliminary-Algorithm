#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
// 实验需要的外部函数 交换、复制、排序、生成
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
    int t, max = nums[0];
    for (i = 1; i < size; i++)
    {
        if (nums[i] > max)
            max = nums[i];
    }
    if (max >= 1073741824 || max <= -1073741824)
        t = 4;
    else if (max >= 1048576 || max <= -1048576)
        t = 3;
    else if (max >= 1024 || max <= -1024)
        t = 2;
    else
        t = 1;
    t = 4;
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
        nums[i] = ((rand() << 15) | (rand() << 1) | (rand() & 1)) % (max - min + 1) + min;
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

// 首先实现期望为线性的选择
int partition(int nums[], int low, int high)
{
    int i = high, j = high + 1;
    for (i; i > low; i--)
    {
        if (nums[i] > nums[low])
        {
            if (nums[i] > nums[--j])
            {
                swap(&nums[i], &nums[j]);
            }
        }
    }
    swap(&nums[low], &nums[j - 1]);
    return j - 1;
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
            swap(&nums[tmp], &nums[low]);
        else if (nums[tmp] > nums[max])
            swap(&nums[max], &nums[low]);
        else
            swap(nums + min, nums + low);
    }
    int middle = partition(nums, low, high);
    if (middle == target)
        return;
    else if (middle > target)
        random_select(nums, low, middle - 1, target);
    else
        random_select(nums, middle + 1, high, target);
}




// 下面实现最坏情况为线性的select算法
int flag_threshold=0;
void my_select(int nums[], int left, int right, int target, int flag);
void mixselect(int nums[], int left, int right, int target, int flag);
#define length 5 // 单组长度
void insertion_sort(int nums[], int left, int right)
{
    if (left == right)
        return;
    int i = left, j = 0;
    while (i <= right)
    {
        int key = nums[i];
        j = i - 1;
        while (j >= left)
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
    my_select(midnums, 0, size - 1, size / 2 - 1, 0);
    int returnNum = midnums[size / 2 - 1];
    free(midnums);
    return returnNum;
}




void my_select(int nums[], int left, int right, int target, int flag)
{
    int mid = get_mid(nums, left, right);
    int i = 0;
    for (i = left; i <= right; i++)
    {
        if (nums[i] == mid)
        {
            swap(&nums[i], &nums[left]);
            break;
        }
    }
    int middle = partition(nums, left, right);
    double index = (double)(left - middle) / (double)(right - left + 1);
    if (middle == target)
        return;
    if (index < 0.5 || index > 0.95)//设定阈值，与mixselect相互调用
    {
        if (middle > target)
            my_select(nums, left, middle - 1, target, flag);
        else
            my_select(nums, middle + 1, right, target, flag);
    }
    else
    {
        if (middle > target)
            mixselect(nums, left, middle - 1, target, 0);
        else
            mixselect(nums, middle + 1, right, target, 0);
    }
}



//mixselect函数，用于联合随机选择与SELECT算法
void mixselect(int nums[], int left, int right, int target, int flag)
{



    srand((unsigned)time(NULL) + rand());
    if (right - left > 1)
    {
        int tmp = (double)rand() / RAND_MAX * (right - left) + left + 1;
        int max = right, min = left;
        if (nums[max] < nums[min])
        {
            max = left, min = right;
        }
        if (nums[tmp] <= nums[max] && nums[tmp] >= nums[min])
            swap(&nums[tmp], &nums[left]);
        else if (nums[tmp] > nums[max])
            swap(&nums[max], &nums[left]);
        else
            swap(nums + min, nums + left);
    }
    int middle = partition(nums, left, right);
    if (middle == target)
        return;


//以上与随机选择算法相同
    double index = (double)(left - middle) / (double)(right - left + 1);
    if (index < 0.05 || index > 0.95)
    {
        flag++;
        if (flag == flag_threshold)
        {
            if (middle > target)
                my_select(nums, left, middle - 1, target, flag);
            else
                my_select(nums, middle + 1, right, target, flag);
        }
        else
        {
            if (middle > target)
                mixselect(nums, left, middle - 1, target, flag);
            else
                mixselect(nums, middle + 1, right, target, flag);
        }
    }
    else
    {
        flag = 0;
        if (middle > target)
            mixselect(nums, left, middle - 1, target, 0);
        else
            mixselect(nums, middle + 1, right, target, 0);
    }
}




int main()
{
    int n, min, max, type;   
    int size = 10, i = 0;
    printf("请依次输入数据量、数据最小值、数据最大值、数据类型、循环次数、flag阈值，我们规定，1为顺序，-1为逆序，0为乱序\n");
    scanf("%d%d%d%d%d%d", &n, &min, &max, &type,&size,&flag_threshold);
    printf("数据量=%d  数据最小值=%d  数据最大值=%d  数据类型=%d  循环次数=%d  flag阈值=%d\n实验开始\n",n,min,max,type,size,flag_threshold);
    double t1=0,t2=0;
    for (i = 0; i < size; i++)
    {
        int *nums1 = (int *)malloc(sizeof(int) * n);
        int *nums2 = (int *)malloc(sizeof(int) * n);
        randNumsCreate(nums1, n, min, max, type);
        copy(nums1, nums2, n);
        LARGE_INTEGER start_select, end_select, start_random_sel, end_random_sel, Tc;
        int key = n / 2;
        QueryPerformanceFrequency(&Tc);
        QueryPerformanceCounter(&start_select);
        mixselect(nums1, 0, n - 1, key - 1, 0);
        QueryPerformanceCounter(&end_select);
        //printf("混合选择耗时：%f 秒\n", (double)(end_select.QuadPart - start_select.QuadPart) / (double)Tc.QuadPart);
        t1+=(double)(end_select.QuadPart - start_select.QuadPart) / (double)Tc.QuadPart;
        QueryPerformanceFrequency(&Tc);
        QueryPerformanceCounter(&start_random_sel);
        random_select(nums2, 0, n - 1, key - 1);
        QueryPerformanceCounter(&end_random_sel);
        //printf("随机选择耗时：%f 秒\n", (double)(end_random_sel.QuadPart - start_random_sel.QuadPart) / (double)Tc.QuadPart);
        t2+=(double)(end_random_sel.QuadPart - start_random_sel.QuadPart) / (double)Tc.QuadPart;
        //printf("\n");
        free(nums1);
        nums1=NULL;
        free(nums2);
        nums2=NULL;
    }
    printf("混合平均选择耗时：%f 秒\n随机平均选择耗时: %f 秒\n",t1/size,t2/size);
    return 0;
}