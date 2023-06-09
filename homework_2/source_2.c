#include "head.h"
int **MatrixCreate(int size, int min, int max)
{
    int i = 0;
    int **ReturnMatrix = (int **)malloc(sizeof(int *) * size);
    srand((unsigned int)time(NULL)+rand());
    i=i*i;
    for(i=0; i < size; i++)
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
void print(int **matrix, int size)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
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
int **NULLmatrixCreate(int size)
{
    int **returnMatrix = (int **)malloc(sizeof(int *) * size);
    int i = 0;
    for (i = 0; i < size; i++)
        returnMatrix[i] = (int *)malloc(sizeof(int) * size);
    return returnMatrix;
}
int **Strassen_multi(int **A, int **B, int size) //, int WN_I_A, int WN_J_A, int WN_I_B, int WN_J_B)
{
    if (size == 2)
    {
        int M1 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]); //(A[WN_I_A][WN_J_A + 1] - A[WN_I_A + 1][WN_J_A + 1]) * (B[WN_I_B + 1][WN_J_B] + B[WN_I_B][WN_J_B]);
        int M2 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]); //(A[WN_I_A][WN_J_A] + A[WN_I_A + 1][WN_J_A + 1]) * (B[WN_I_B][WN_J_B] + B[WN_I_B + 1][WN_J_B + 1]);
        int M3 = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]); //(A[WN_I_A + 1][WN_J_A] - A[WN_I_A][WN_J_A]) * (B[WN_I_B][WN_J_B] + B[WN_I_B][WN_J_B + 1]);
        int M4 = (A[0][0] + A[0][1]) * B[1][1];             //(A[WN_I_A][WN_J_A] + A[WN_I_A][WN_J_A + 1]) * B[WN_I_B + 1][WN_J_B + 1];
        int M5 = A[0][0] * (B[0][1] - B[1][1]);             // A[WN_I_A][WN_J_A] * (B[WN_I_B][WN_J_B + 1] - B[WN_I_B + 1][WN_J_B + 1]);
        int M6 = A[1][1] * (B[1][0] - B[0][0]);             // A[WN_I_A + 1][WN_J_A + 1] * (B[WN_I_B + 1][WN_J_B] - B[WN_I_B][WN_J_B]);
        int M7 = (A[1][0] + A[1][1]) * B[0][0];             //(A[WN_I_A + 1][WN_J_A] + A[WN_I_A + 1][WN_J_A + 1]) * B[WN_I_B][WN_J_B];
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
    int **A12 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = size / 2; j < size; j++)
            A12[i][j-size/2] = A[i][j];
    }
    int **A21 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = 0; j < size / 2; j++)
        {
            A21[i-size/2][j] = A[i][j];
        }
    }
    int **A22 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = size / 2; j < size; j++)
            A22[i-size/2][j-size/2] = A[i][j];
    }
    int **B11 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = 0; j < size / 2; j++)
            B11[i][j] = B[i][j];
    }
    int **B12 = NULLmatrixCreate(size / 2);
    for (i = 0; i < size / 2; i++)
    {
        for (j = size / 2; j < size; j++)
            B12[i][j-size/2] = B[i][j];
    }
    int **B21 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = 0; j < size / 2; j++)
            B21[i-size/2][j] = B[i][j];
    }
    int **B22 = NULLmatrixCreate(size / 2);
    for (i = size / 2; i < size; i++)
    {
        for (j = size / 2; j < size; j++)
            B22[i-size/2][j-size/2] = B[i][j];
    }
    int **M1/*, **M2, **M3, **M4, **M5, **M6, **M7;*/
         = NULLmatrixCreate(size / 2);
          int **M2 = NULLmatrixCreate(size / 2);
          int **M3 = NULLmatrixCreate(size / 2);
          int **M4 = NULLmatrixCreate(size / 2);
          int **M5 = NULLmatrixCreate(size / 2);
          int **M6 = NULLmatrixCreate(size / 2);
          int **M7 = NULLmatrixCreate(size / 2);
    M1 = Strassen_multi(sub_matrix(A12, A22, size / 2), sum_matrix(B21, B22, size / 2), size / 2);
    M2 = Strassen_multi(sum_matrix(A11, A22, size / 2), sum_matrix(B11, B22, size / 2), size / 2);
    M3 = Strassen_multi(sub_matrix(A11, A21, size / 2), sum_matrix(B11, B12, size / 2), size / 2);
    M4 = Strassen_multi(sum_matrix(A11, A12, size / 2), B22, size / 2);
    M5 = Strassen_multi(A11, sub_matrix(B12, B22, size / 2), size / 2);
    M6 = Strassen_multi(A22, sub_matrix(B21, B11, size / 2), size / 2);
    M7 = Strassen_multi(sum_matrix(A21, A22, size / 2), B11, size / 2);
    int **R11 = sum_matrix(sum_matrix(M1, M2, size / 2), sub_matrix(M6, M4, size / 2), size / 2);
    int **R12 = sum_matrix(M4, M5, size / 2);
    int **R21 = sum_matrix(M6, M7, size / 2);
    int **R22 = sum_matrix(sum_matrix(M2, M3, size / 2), sub_matrix(M5, M7, size / 2), size / 2);
    int **returnMatrix = NULLmatrixCreate(size);
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
    /*free(A11);
    A11 = NULL;
    free(A12);
    A12 = NULL;
    free(A21);
    A21 = NULL;
    free(B11);
    B11 = NULL;
    free(B12);
    B12 = NULL;
    free(B21);
    B21 = NULL;
    free(B22);
    B22 = NULL;
    free(R11);
    R11 = NULL;
    free(R12);
    R12 = NULL;
    free(R21);
    R21 = NULL;
    free(R22);
    R22 = NULL;*/
    return returnMatrix;
}