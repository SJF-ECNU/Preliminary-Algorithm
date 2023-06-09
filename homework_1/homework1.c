#include "First.h"
#include <stdio.h>
#include <stdlib.h>
//1顺序 -1逆序 0随机
int main()
{
    clock_t start_merge, end_merge,start_insertion,end_insertion,start_bubble,end_bubble;//定义6个时间变量分别记录三个算法的起始于完成时间
    int N = 1000000, min = 0, max = 1000000, type = -1;
    scanf("%d %d %d %d",&N,&min,&max,&type);
    printf("数据规模：%d 数据排列类型：%d\n", N, type);
    int *nums = (int *)malloc(sizeof(int) * N);
    nums = RandomNums(N, min, max, type);//根据四个变量生成随机数
    int *UsingNums = (int *)malloc(sizeof(int) * N);
    int i=0
    ;
    //merge
    for(i=0;i<N;i++) UsingNums[i]=nums[i];//初始化要使用的数组
    start_merge = clock();
    merge_run(UsingNums, 0, N - 1, 1);
    end_merge = clock();
    printf("time_merge=%lf\n", (double)(end_merge - start_merge) / CLOCKS_PER_SEC);
    //insertion
    for(i=0;i<N;i++) UsingNums[i]=nums[i];//初始化要使用的数组
    start_insertion=clock();
    InsertionSort(UsingNums,N,1);
    end_insertion=clock();
    printf("time_insertion=%lf\n", (double)(end_insertion - start_insertion) / CLOCKS_PER_SEC);
    //bubble
    for(i=0;i<N;i++) UsingNums[i]=nums[i];//初始化要使用的数组
    start_bubble=clock();
    bubble(UsingNums,N);
    end_bubble=clock();
    printf("time_bubble=%lf\n", (double)(end_bubble - start_bubble) / CLOCKS_PER_SEC); 
    free(nums);
    nums=NULL;
    return 0;
}