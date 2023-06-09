#ifndef HEAD_H
#define HEAD_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
extern int power(int num,int index);
extern int**MatrixCreate(int size,int min, int max);
extern int **NormalMulti(int **A, int **B, int size);
extern void print(int**matrix,int size);
extern int **Strassen_multi(int **A, int **B, int size);
extern int **sum_matrix(int **A, int **B, int size);
extern int **sub_matrix(int **A, int **B, int size);
extern int **NULLmatrixCreate(int size);
#endif