#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int i=0;
    int size=0;
    scanf("%d",&size);
    char codeTab[15000]={'\0'};
    for(i=0;i<size;i++)
    {
        char ch;
        char*str=(char*)malloc(sizeof(char)*20);
        getchar();
        scanf("%c : %s",&ch,str);
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
    char *code = (char *)malloc(sizeof(char) * 100000);
    scanf("%s",code);
    int length=strlen(code);
    int locate=0;
    for(i=0;i<=length;i++)
    {
        if(codeTab[locate]!='\0') 
        {
            printf("%c",codeTab[locate]);
            locate=0;
        }
        if(code[i]=='0') locate=locate*2+1;
        else locate=locate*2+2;
    }
    return 0;
}