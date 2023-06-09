#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define size 34
#define R 6371.004

typedef struct city
{
    char name[10];
    double lon;
    double lat;
}city;



double Min(double x, double y)
{
    if (x >= y)
        return y;
    return x;
}



void inPutCities(city*cities[],FILE*pf_r)
{
    int i=0;
    for(i=0;i<size;i++)
    {
        city*newCity=(city*)malloc(sizeof(city));
        fscanf(pf_r,"%s %lf,%lf\n",newCity->name,&newCity->lon,&newCity->lat);
        cities[i]=newCity;
    }
}



double distance(city*A,city*B)
{
    if(A==B) return 0;
    double MlonA=A->lon*acos(-1)/180;
    double MlonB=B->lon*acos(-1)/180;
    double MlatA=A->lat*acos(-1)/180;
    double MlatB=B->lat*acos(-1)/180;
    double C = cos(MlatA)*cos(MlatB)*cos(MlonA-MlonB) + sin(MlatA)*sin(MlatB);
    double dis=(R*acos(C));
    return dis;
}



void computeDistance(city*cities[],double DistanceMatrix[][34])
{
    int i=0;
    for(;i<size;i++)
    {
        int j=0;
        for(;j<size;j++)
        {
            DistanceMatrix[i][j]=distance(cities[i],cities[j]);
        }
    }
    DistanceMatrix[32][33]=1000000;
    DistanceMatrix[33][32]=1000000;
    DistanceMatrix[20][33]=1000000;
    DistanceMatrix[33][20]=1000000;
}


int GetMinlocation(double Distances[],double distanceMatrix[][34],FILE*pf_w,city*cities[])
{
    int i=0,min_location=0;
    double min=1000000;
    for(i=0;i<size;i++)
    {
        if(Distances[i]!=0&&Distances[i]<min)
        {
            min=Distances[i];
            min_location=i;
        }
    }
    int start=34;
    for(i=0;i<34;i++)
    {
        if((min-distanceMatrix[min_location][i])<=0.01&&(min-distanceMatrix[min_location][i])>=-0.01)
        {
            start=i;
            break;
        }
    }
    fprintf(pf_w,"%s -- %s : %fkm\n",cities[start]->name,cities[min_location]->name,min);
    return min_location;
}



double GetMinDistanceSum(double DistanceMatrix[][size],FILE*pf_w,city*cities[])
{
    double Distances[size];
    int i=0;
    double Sum=0;
    for(i=0;i<size;i++) Distances[i]=1000000;
    Distances[0]=0;
    for(i=1;i<size;i++)
    {
        Distances[i]=Min(Distances[i],DistanceMatrix[0][i]);
    }
    for(i=1;i<size;i++)
    {
        int newInput=GetMinlocation(Distances,DistanceMatrix,pf_w,cities);
        Sum+=Distances[newInput];
        Distances[newInput]=0;
        for(int j=0;j<size;j++)
        {
            Distances[j]=Min(Distances[j],DistanceMatrix[newInput][j]);
        }
    }
    return Sum;
}



int main()
{
    FILE*pf_r=fopen("D:\\Code\\CODE_C\\homework_12\\input.txt","r");
    FILE*pf_w=fopen("D:\\Code\\CODE_C\\homework_12\\output.txt","w");    
    if(pf_r==NULL)
    {
        printf("Failed to open file!!!\n");
        return 0;
    }
    double DistanceMatrix[size][size];
    city*cities[size];
    inPutCities(cities,pf_r);
    computeDistance(cities,DistanceMatrix);
    printf("%lf\n",GetMinDistanceSum(DistanceMatrix,pf_w,cities));
    int i=0,j=0;
    for(;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            fprintf(pf_w,"%-8lf  ",DistanceMatrix[i][j]);
        }
        fprintf(pf_w,"\n\n");
    }
    fclose(pf_r);
    fclose(pf_w);
    for(i=0;i<34;i++) free(cities[i]);
    return 0;
}