#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int exponential(int num,int index)
{
    int i=0;
    int j=1;
    for(i=0;i<index;i++) j=j*num;
    return j;
}
int randomNum(int max)
{
    return ((rand()<<15|rand()<<1|rand()&1)%max+1);
}
void randNumsCreate(int*nums,int size,int max)
{
    int i=0;
    srand((unsigned)time(NULL)+rand());
    for(i=0;i<size;i++) nums[i]=(double)rand()/RAND_MAX*(max-1)+1;
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
void CardinaHelp(int*nums,int size,int exp,int r)
{
    int bucketsize=exponential(10,r),max=exponential(10,exp),min=exponential(10,exp-r);
    int*returnNums=(int*)malloc(sizeof(int)*size);
    int*bucket=(int*)malloc(sizeof(int)*bucketsize);
    int i=0;
    for(;i<bucketsize;i++)
        bucket[i]=0;
    for(i=0;i<size;i++)
        bucket[nums[i]%max-nums[i]%min]++;
    for(i=1;i<size;i++) 
        bucket[i]+=bucket[i-1];
    for(i=size-1;i>=0;i--) 
        returnNums[--bucket[nums[i]%max-nums[i]%min]]=nums[i];
    for(i=0;i<size;i++) 
        nums[i]=returnNums[i];
    free(returnNums);
    returnNums=NULL;
    free(bucket);
    bucket=NULL;
}
void CardinalSort(int*nums,int size,int exp_max,int R)
{
    int exp,r;
    exp=R,r=R;
    while(exp<=exp_max+1)
    {
        CardinaHelp(nums,size,exp,r);
        exp+=R;
    }
}
int main()
{
    int exp_max,size,i;
    scanf("%d%d",&size,&exp_max);
    int*nums=(int*)malloc(sizeof(int)*size);
    randNumsCreate(nums,size,exponential(10,exp_max));
    for (i = 0; i < size; i++)
        printf("%d ", nums[i]);
    printf("\n");
    CardinalSort(nums,size,exp_max,1);
    for(i=0;i<size;i++) printf("%d ",nums[i]);
    return 0;
}