#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//首先实现期望为线性的选择
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int parition(int nums[], int low, int high)
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
    int middle = parition(nums, low, high);
    if (middle == target)
        return;
    else if (middle > target)
        random_select(nums, low, middle - 1, target);
    else
        random_select(nums, middle + 1, high, target);
}
//下面实现最坏情况为线性的select算法
#define length 5
void insertion_sort(int nums[], int left, int right)
{
    if (left == right)
        return;
    int i = 0, j = 0;
    for (i = left; i <= right; i++)
    {
        int key = nums[i];
        j = i - 1;
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
    int returnNum = get_mid(midnums, 0, size - 1);
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
            swap(&nums[i], &nums[left]);
            break;
        }
    }
    int part=parition(nums,left,right);
    if (part==target)
        return;
    else if (part > target)
        my_select(nums, left, part - 1, target);
    else
        my_select(nums, part + 1, right, target);
}
int main()
{
    int nums[45000] = {0};
    int n;
    scanf("%d", &n);
    int i = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }
    int key = n / 2;
    my_select(nums, 0, n - 1, key - 1);
    printf("%d", nums[key - 1]);
    return 0;
}