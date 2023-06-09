#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void swap( int *A, int *B)
{
    int exchange=*(A);
    *(A)=*(B);
    *(B)=exchange;
}
int split(int a[],int low,int high)
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
int returnmid(int nums[],int low,int high)
{
    int mid=(low+high)/2;
    if(nums[low]>nums[mid])
    {
        if(nums[high]<nums[mid]) return mid;
        else if(nums[high]>nums[low]) return low;
        else return high;
    }
    else
    {
        if(nums[high]>nums[mid]) return mid;
        else if(nums[high]<nums[low]) return low;
        else return high;
    }
}
void quicksort(int a[], int low, int high)
{
    if (low >= high)
        return;
    int middle = returnmid(a,low,high);
    swap(&a[low],&a[middle]);
    quicksort(a, low, middle - 1);
    quicksort(a, middle + 1, high);
}
int main()
{
    int arr[10]={1,3,6,2,7,10,5,4,8,0};
    quicksort(arr,0,9);
    int i=0;
    for(i=0;i<10;i++) printf("%d ",arr[i]);
    return 0;
}