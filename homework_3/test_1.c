#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
void randomnumsCreate(int size,int *nums,int min, int max)
{
    srand((unsigned)time(NULL)+rand());
    int i=1;
    for(i=1;i<=size;i++)
    {
        nums[i]=(rand()%(max-min+1)+min);
    }
}
void swap(int *nums, int A, int B)
{
    int exchange=nums[A];
    nums[A]=nums[B];
    nums[B]=exchange;
}
void judge_exchange(int *nums, int size, int locate)
{
    int left=locate*2;
    int right=locate*2+1;
    int largest=locate;
    if(right<=size&&nums[right]>nums[largest]) largest=right;
    if(left<=size&&nums[left]>nums[largest]) largest=left;
    if(largest==locate) return;
    swap(nums,largest,locate);
    judge_exchange(nums,size,largest);
}
void heap_create(int *nums,int size)//big root
{
    int i=size/2;
    for(i;i>=1;i--)
    {
        judge_exchange(nums,size,i);
    }
}
void heap_sort(int *nums,int size)
{
    int i=size;
    for(i;i>=2;)
    {
        swap(nums,1,i);
        i--;
        judge_exchange(nums,i,1);
    }
}
void copy(int *arr1,int *arr2,int size)
{
    int i=1;
    for(i=1;i<=size;i++)
    {
        arr2[i]=arr1[i];
    }
}
int split(int *a,int low,int high)
{
    int part=a[low];
    for(;;)
    {
        while(low<high&&part<=a[high]) high--;//从最右端寻找小于part的数字
        if(low>=high) break;//运行到low==high都没找到，退出
        a[low++]=a[high];//把找到的小于part的数字放在整体的最左端，把进行运算的最左端往右移一位，此时被找到的那个数的原位置空缺，位置下标目前为high
        while(low<high&&part>=a[low]) low++;//从左端（如果找到了个小于part的highhigh，已经右移了）开始寻找大于part的数字
        if(low>=high) break;//运行到low==high时都没找到，退出
        a[high--]=a[low];//把找到的小于part的最小值赋值给high的那个空缺，此时此个low空缺，同时把进行运算的最右端往左移一位
    }
    a[high]=part;//最后的最后，空缺汇合于high=low，令a[low]=a[high]=part即可
    //此时，part左侧的数字都比part小，右侧都比part大
    return high;
}
void quicksort(int *a, int low, int high)
{
    int middle;
    if (low >= high)
        return;
    middle = split(a, low, high);
    quicksort(a, low, middle - 1);
    quicksort(a, middle + 1, high);
}
int main()
{
    time_t start_heapsort,end_heapsort,start_quicksort,end_quicksort;
    int size=100000;
    //scanf("%d",&size);
    int nums1=(int*)malloc(sizeof(int)*(size+1));
    int nums2=(int*)malloc(sizeof(int)*(size+1));
    randomnumsCreate(size,nums1,0,1000);
    copy(nums1,nums2,size)
    //for(i=1;i<=size;i++) scanf("%d",&nums[i]);
    start_heapsort=clock();
    heap_create(nums1,size);
    heap_sort(nums1,size);
    end_heapsort=clock();
    printf("time_heapsort= %f second\n",(double)(end_heapsort-start_heapsort)/CLOCKS_PER_SEC);
    start_quicksort=clock();
    quicksort(nums2,1,size);
    end_quicksort=clock();
    printf("time_quicksort= %f second\n",(double)(end_quicksort-start_quicksort)/CLOCKS_PER_SEC);
    return 0;
}