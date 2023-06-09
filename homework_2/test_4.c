#include <stdio.h>
#include <stdlib.h>
void Free_matrix(int **matrix, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix=NULL;
    return;
}
int **NULLmatrixCreate(int size)
{
    int **returnMatrix = (int **)malloc(sizeof(int *) * size);
    int i = 0,j=0;
    for (i = 0; i < size; i++)
    {
        returnMatrix[i] = (int *)malloc(sizeof(int) * size);
        for(j=0;j<size;j++) returnMatrix[i][j]=0;
    }
    return returnMatrix;
}
void print(int **matrix, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (j == size - 1)
                printf("%d", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
void sum_matrix(int **A, int **B, int **C ,int size)
{
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
    return;
}
void sub_matrix(int **A, int **B,int**C,int size)
{
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
           C[i][j] = A[i][j] - B[i][j];
    }
    return;
}
void Strassen_multi(int **A, int **B,int**C,int size)
{
    if(size==1)
    {
        C[0][0]=A[0][0]*B[0][0];
        return;
    }
    int**A11=NULLmatrixCreate(size/2);
    int**A12=NULLmatrixCreate(size/2);
    int**A21=NULLmatrixCreate(size/2);
    int**A22=NULLmatrixCreate(size/2);
    int**B11=NULLmatrixCreate(size/2);
    int**B12=NULLmatrixCreate(size/2);
    int**B21=NULLmatrixCreate(size/2);
    int**B22=NULLmatrixCreate(size/2);
    int**M1=NULLmatrixCreate(size/2);
    int**M2=NULLmatrixCreate(size/2);
    int**M3=NULLmatrixCreate(size/2);
    int**M4=NULLmatrixCreate(size/2);
    int**M5=NULLmatrixCreate(size/2);
    int**M6=NULLmatrixCreate(size/2);
    int**M7=NULLmatrixCreate(size/2);
    int i,j;
    for(i=0;i<size/2;i++)
    {
        for(j=0;j<size/2;j++)
        {
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j+size/2];
            A21[i][j]=A[i+size/2][j];
            A22[i][j]=A[i+size/2][j+size/2];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+size/2];
            B21[i][j]=B[i+size/2][j];
            B22[i][j]=B[i+size/2][j+size/2];
        }
    }
    int**G1=NULLmatrixCreate(size/2);
    int**G2=NULLmatrixCreate(size/2);

    sub_matrix(A12,A22,G1,size/2);
    sum_matrix(B21,B22,G2,size/2);
    Strassen_multi(G1,G2,M1,size/2);

    sum_matrix(A11,A22,G1,size/2);
    sum_matrix(B11,B22,G2,size/2);
    Strassen_multi(G1,G2,M2,size/2);

    sub_matrix(A21,A11,G1,size/2);
    sum_matrix(B11,B12,G2,size/2);
    Strassen_multi(G1,G2,M3,size/2);
    
    sum_matrix(A11,A12,G1,size/2);
    Strassen_multi(G1,B22,M4,size/2);

    sub_matrix(B12,B22,G1,size/2);
    Strassen_multi(A11,G1,M5,size/2);

    sub_matrix(B21,B11,G1,size/2);
    Strassen_multi(A22,G1,M6,size/2);

    sum_matrix(A21,A22,G1,size/2);
    Strassen_multi(G1,B11,M7,size/2);

    for(i=0;i<size/2;i++)
    {
        for(j=0;j<size/2;j++)
        {
            C[i][j]=M1[i][j]+M2[i][j]+M6[i][j]-M4[i][j];
            C[i][j+size/2]=M4[i][j]+M5[i][j];
            C[i+size/2][j]=M6[i][j]+M7[i][j];
            C[i+size/2][j+size/2]=M2[i][j]+M3[i][j]+M5[i][j]-M7[i][j];
        }
    }
    Free_matrix(A11,size/2);
    Free_matrix(A12,size/2);
    Free_matrix(A21,size/2);
    Free_matrix(A22,size/2);
    Free_matrix(B11,size/2);
    Free_matrix(B12,size/2);
    Free_matrix(B21,size/2);
    Free_matrix(B22,size/2);
    Free_matrix(M1,size/2);
    Free_matrix(M2,size/2);
    Free_matrix(M3,size/2);
    Free_matrix(M4,size/2);
    Free_matrix(M5,size/2);
    Free_matrix(M6,size/2);
    Free_matrix(M7,size/2);
    Free_matrix(G1,size/2);
    Free_matrix(G2,size/2);
    return;
}
int **MatrixCreate(int size, int min, int max)
{
    int i = 0;
    int **ReturnMatrix = (int **)malloc(sizeof(int *) * size);
    srand((unsigned int)time(NULL) + rand());
    for (i; i < size; i++)
    {
        int j = 0;
        ReturnMatrix[i] = (int *)malloc(sizeof(int) * size);
        for (j = 0; j < size; j++)
        {
            int num = rand();
            ReturnMatrix[i][j] = (min + num % (max - min + 1));
        }
    }
    return ReturnMatrix;
}
void NormalMulti(int **A, int **B, int**C,int size)
{
    int i;
    int j = 0, i_move, j_move;
    int sum = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            for (i_move = 0, j_move = 0; i_move < size; i_move++, j_move++)
            {
                sum += A[i][i_move] * B[j_move][j];
            }
            C[i][j] = sum;
            sum = 0;
        }
    }
}
int main()
{
    int size=1024;
    int **A = MatrixCreate(size,0,10);
    int **B = MatrixCreate(size,0,10);
    int**C=NULLmatrixCreate(size);
    time_t start_strassen,end_strassen;
    start_strassen=clock();
    Strassen_multi(A, B,C, size);
    end_strassen=clock();
    printf("time_strassen_multi=%f\n",(double)(end_strassen-start_strassen)/CLOCKS_PER_SEC);
    Free_matrix(A, size);
    Free_matrix(B, size);
    Free_matrix(C, size);
    return 0;
}
