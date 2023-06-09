#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int **NormalMulti(int **A, int **B, int size)
{
    int **ReturnMatrix = (int **)malloc(sizeof(int *) * size);
    int i;
    for (i = 0; i < size; i++)
        ReturnMatrix[i] = (int *)malloc(sizeof(int) * size);
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
            ReturnMatrix[i][j] = sum;
            sum = 0;
        }
    }
    return ReturnMatrix;
}
int**repair(int**A,int size,int repair_size)
{

}
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
    int i = 0;
    for (i = 0; i < size; i++)
        returnMatrix[i] = (int *)malloc(sizeof(int) * size);
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
int **sum_matrix(int **A, int **B, int size)
{
    int **returnMatrix = (int **)malloc(sizeof(int *) * size);
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
    {
        returnMatrix[i] = (int *)malloc(sizeof(int) * size);
        for (j = 0; j < size; j++)
            returnMatrix[i][j] = A[i][j] + B[i][j];
    }
    return returnMatrix;
}
int **sub_matrix(int **A, int **B, int size)
{
    int **returnMatrix = (int **)malloc(sizeof(int *) * size);
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
    {
        returnMatrix[i] = (int *)malloc(sizeof(int) * size);
        for (j = 0; j < size; j++)
            returnMatrix[i][j] = A[i][j] - B[i][j];
    }
    return returnMatrix;
}
int **Strassen_multi(int **A, int **B, int size)
{
    if (size == 2)
    {
        int M1 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
        int M2 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        int M3 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
        int M4 = (A[0][0] + A[0][1]) * B[1][1];
        int M5 = A[0][0] * (B[0][1] - B[1][1]);
        int M6 = A[1][1] * (B[1][0] - B[0][0]);
        int M7 = (A[1][0] + A[1][1]) * B[0][0];
        int **returnMinMatrix = (int **)malloc(sizeof(int *) * 2);
        returnMinMatrix[0] = (int *)malloc(sizeof(int) * 2);
        returnMinMatrix[1] = (int *)malloc(sizeof(int) * 2);
        returnMinMatrix[0][0] = M1 + M2 + M6 - M4;
        returnMinMatrix[0][1] = M4 + M5;
        returnMinMatrix[1][0] = M6 + M7;
        returnMinMatrix[1][1] = M2 + M3 + M5 - M7;
        return returnMinMatrix;
    }
    int i = 0, j = 0;
    int **A11 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = 0; j < size / 2; j++)
            A11[i][j] = A[i][j];
    }
    int **A21 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = 0; j < size / 2; j++)
        {
            A21[i - size / 2][j] = A[i][j];
        }
    }
    int **A22 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = size / 2; j < size; j++)
            A22[i - size / 2][j - size / 2] = A[i][j];
    }
    int **A12 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = size / 2; j < size; j++)
            A12[i][j - size / 2] = A[i][j];
    }
    int **G1 = sub_matrix(A12, A22, size / 2);
    int **G7 = sum_matrix(A11, A12, size / 2);
    Free_matrix(A12, size / 2);
    int **G5 = sub_matrix(A21, A11, size / 2);
    int **G10 = sum_matrix(A21, A22, size / 2);
    Free_matrix(A21, size / 2);
    int **G3 = sum_matrix(A11, A22, size / 2);
    int **B11 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = 0; j < size / 2; j++)
            B11[i][j] = B[i][j];
    }
    int **B21 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = 0; j < size / 2; j++)
            B21[i - size / 2][j] = B[i][j];
    }
    int **B22 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = size / 2; j < size; j++)
            B22[i - size / 2][j - size / 2] = B[i][j];
    }
    int **G2 = sum_matrix(B21, B22, size / 2); 
    int **G9 = sub_matrix(B21, B11, size / 2);
    Free_matrix(B21, size / 2);
    int **G4 = sum_matrix(B11, B22, size / 2);
    int **B12 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = size / 2; j < size; j++)
            B12[i][j - size / 2] = B[i][j];
    }
    int **G6 = sum_matrix(B11, B12, size / 2);
    int **G8 = sub_matrix(B12, B22, size / 2);
    Free_matrix(B12, size / 2);
    int **M1 = NULLmatrixCreate(size / 2);
    int **M2 = NULLmatrixCreate(size / 2);
    int **M3 = NULLmatrixCreate(size / 2);
    int **M4 = NULLmatrixCreate(size / 2);
    int **M5 = NULLmatrixCreate(size / 2);
    int **M6 = NULLmatrixCreate(size / 2);
    int **M7 = NULLmatrixCreate(size / 2);
    M1 = Strassen_multi(G1, G2, size / 2);
    Free_matrix(G1, size / 2);
    Free_matrix(G2, size / 2);
    M2 = Strassen_multi(G3, G4, size / 2);
    Free_matrix(G3, size / 2);
    Free_matrix(G4, size / 2);
    M3 = Strassen_multi(G5, G6, size / 2);
    M4 = Strassen_multi(G7, B22, size / 2);
    M5 = Strassen_multi(A11, G8, size / 2);
    M6 = Strassen_multi(A22, G9, size / 2);
    M7 = Strassen_multi(G10, B11, size / 2);
    Free_matrix(G3, size / 2);
    Free_matrix(G4, size / 2);
    Free_matrix(G5, size / 2);
    Free_matrix(G6, size / 2);
    Free_matrix(G7, size / 2);
    Free_matrix(G8, size / 2);
    Free_matrix(G9, size / 2);
    Free_matrix(G10, size / 2);
    Free_matrix(A11, size / 2);
    Free_matrix(A22, size / 2);
    Free_matrix(B11, size / 2);
    Free_matrix(B22, size / 2);
    int **G11 = sum_matrix(M1, M2, size / 2);
    int **G12 = sub_matrix(M6, M4, size / 2);
    int **G13 = sum_matrix(M2, M3, size / 2);
    int **G14 = sub_matrix(M5, M7, size / 2);
    int **R11 = sum_matrix(G11, G12, size / 2);
    int **R12 = sum_matrix(M4, M5, size / 2);
    int **R21 = sum_matrix(M6, M7, size / 2);
    int **R22 = sum_matrix(G13, G14, size / 2);
    int **returnMatrix = NULLmatrixCreate(size);
    Free_matrix(G11, size / 2);
    Free_matrix(G12, size / 2);
    Free_matrix(G13, size / 2);
    Free_matrix(G14, size / 2);
    Free_matrix(M1, size / 2);
    Free_matrix(M2, size / 2);
    Free_matrix(M3, size / 2);
    Free_matrix(M4, size / 2);
    Free_matrix(M5, size / 2);
    Free_matrix(M6, size / 2);
    Free_matrix(M7, size / 2);
    int col, row;
    for (i = 0, row = 0; i < size / 2; i++, row++)
    {
        for (j = 0, col = 0; j < size / 2; j++, col++)
            returnMatrix[i][j] = R11[row][col];
    }
    for (i = 0, row = 0; i < size / 2; i++, row++)
    {
        for (j = size / 2, col = 0; j < size; j++, col++)
            returnMatrix[i][j] = R12[row][col];
    }
    for (i = size / 2, row = 0; i < size; i++, row++)
    {
        for (j = 0, col = 0; j < size / 2; j++, col++)
            returnMatrix[i][j] = R21[row][col];
    }
    for (i = size / 2, row = 0; i < size; i++, row++)
    {
        for (j = size / 2, col = 0; j < size; j++, col++)
            returnMatrix[i][j] = R22[row][col];
    }
    Free_matrix(R11, size / 2);
    Free_matrix(R12, size / 2);
    Free_matrix(R21, size / 2);
    Free_matrix(R22, size / 2);
    return returnMatrix;
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
int main()
{
    int size=512;
    int **A = MatrixCreate(size,0,10);
    int **B = MatrixCreate(size,0,10);
    time_t start_strassen,end_strassen,start_normal,end_normal;
    start_strassen=clock();
    int **C = Strassen_multi(A, B, size);
    end_strassen=clock();
    printf("time_strassen_multi=%f\n",(double)(end_strassen-start_strassen)/CLOCKS_PER_SEC);
    Free_matrix(C, size);
    start_normal=clock();
    int **D = NormalMulti(A, B, size);
    end_normal=clock();
    printf("time_normal_multi=%f\n",(double)(end_normal-start_normal)/CLOCKS_PER_SEC);
    Free_matrix(A, size);
    Free_matrix(B, size);
    Free_matrix(D,size);
    return 0;
}
