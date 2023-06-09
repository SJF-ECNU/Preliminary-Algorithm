#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
int main()
{
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    FILE*pf_r=fopen("D:\\Code\\CODE_C\\homework_11\\decode\\normal.txt","r");
    FILE*pf_w=fopen("D:\\Code\\CODE_C\\homework_11\\decode\\output.txt","w");
    if(pf_r==NULL||pf_w==NULL)
    {
        printf("Failed to open file!!!\n");
        return 0;
    }
    char codeTab[15000]={'\0'};
    int i=0;
    int size=0;
    fscanf(pf_r,"%d",&size);
    for(i=0;i<size;i++)
    {
        char ch;
        char*str=(char*)malloc(sizeof(char)*20);
        fgetc(pf_r);
        fscanf(pf_r,"%c : %s",&ch,str);
        int length=strlen(str);
        int j=0;
        int locate=0;
        for(j=0;j<length;j++)
        {
            char step=str[j];
            if(step=='0')
            {
                locate=locate*2+1;
            }
            else
            {
                locate=locate*2+2;
            }
        }
        codeTab[locate]=ch;
        free(str);
    }
    char *code = (char *)malloc(sizeof(char) * 10000000);
    fscanf(pf_r,"%s",code);
    int length=strlen(code);
    int locate=0;
    for(i=0;i<=length;i++)
    {
        if(codeTab[locate]!='\0') 
        {
            fprintf(pf_w,"%c",codeTab[locate]);
            locate=0;
        }
        if(code[i]=='0') locate=locate*2+1;
        else locate=locate*2+2;
    }
    fclose(pf_r);
    fclose(pf_w);
    QueryPerformanceCounter(&t2);
    printf("Successfully finished!\ntime_cost= %.7f second",(double)(t2.QuadPart - t1.QuadPart) / ((double)tc.QuadPart));
    return 0;
}