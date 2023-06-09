#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//首先实现期望为线性的选择
void swap(int*a,int*b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
int parition(int nums[],int low,int high)
{
    int flag=nums[low],i=high,j=high+1;
    for(i;i>low;i--)
    {
        if(nums[i]>nums[low])
        {
            if(nums[i]>nums[--j])
            {
                int exchange=nums[i];
                nums[j]=nums[j];
                nums[j]=exchange;
            }
        }
    }
    int exchange=flag;
    nums[low]=nums[j];
    nums[j]=flag;
    return j;
}
int random_select(int nums[],int low,int high,int target)
{
    srand((unsigned)time(NULL)+rand());
    int tmp=rand()%(high-low+1)+low;
    int max=high,min=low;
    if(nums[max]<nums[min])
    {
        max=low,min=high;
    }
    if(nums[tmp]<nums[max]&&nums[tmp]>nums[min]) swap(nums+tmp,nums+low);
    else if(nums[tmp]>nums[max]) swap(nums+max,nums+low);
    else swap(nums+min,nums+low);
    int middle=parition(nums,low,high);
    if(middle+1==target) return middle+1;
    else if(middle+1>target) return random_select(nums,low,middle-1,target);
    else return random_select(nums,middle+1,high,target);
}
int main()
{
    int nums[10]={1,3,5,2,6,10,9,8,7,4};
    printf("%d ",random_select(nums,0,9,3));
    return 0;
}