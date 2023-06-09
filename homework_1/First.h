#ifndef FIRST_H
#define FIRST_H
#include<time.h>
extern int *RandomNums(int N, int min, int max, int type);
extern void InsertionSort(int nums[],int N,int type);
extern void merge(int*nums,int min,int max,int type);
extern void merge(int nums[], int min, int max, int type);
extern void merge_run(int nums[], int min, int max, int type);
extern void bubble(int nums[],int N);
#endif