#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int exponential(int num, int index)
{
    int i = 0;
    int j = 1;
    for (i = 0; i < index; i++)
        j = j * num;
    return j;
}
int randomNum(int max)
{
    return ((rand() << 15 | rand() << 1 | rand() & 1) % max + 1);
}
void randNumsCreate(int *nums, int size, int max)
{
    int i = 0;
    srand((unsigned)time(NULL) + rand());
    for (i = 0; i < size; i++)
        nums[i] = (double)rand() / RAND_MAX * max + 1;
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
    int size, i;
    scanf("%d", &size);
    int *nums = (int *)malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
        scanf("%d", &nums[i]);
    CountSort(nums, size);
    for (i = 0; i < size; i++)
        printf("%d ", nums[i]);
    return 0;
}