#include"head.h"
int main()
{
    time_t start_normal,end_normal,start_strassen,end_strassen;
    int size=256;
    int**A=MatrixCreate(size,0,10);
    int**B=MatrixCreate(size,0,10);
    start_normal=clock();
    int**C=NormalMulti(A,B,size);
    end_normal=clock();
    printf("time_normal_multi=%f\n",(double)(end_normal-start_normal)/CLOCKS_PER_SEC);
    start_strassen=clock();
    int**D=Strassen_multi(A,B,size);
    end_strassen=clock();
    printf("time_strassen_multi=%f\n",(double)(end_strassen-start_strassen)/CLOCKS_PER_SEC);
    return 0;
}