#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int times;
int count;
int endMin;
int startMin;
int Min(int A, int B)
{
    if (A <= B)
        return A;
    return B;
}
typedef struct dis
{
    int Sdis;
    int Edis;
    int Sbefore;
    int Ebefore;
    int Sflag;
    int Eflag;
} dis;
typedef struct link
{
    char *name;
    int location;
    struct link *next;
} link;

typedef struct road
{
    int location;
    struct road *next;
    int distance;
} road;

int search(char *str, link *head) // 把名字转化为数字标记
{
    link *tmp = head;
    link *before = NULL;
    while (tmp != NULL)
    {
        before = tmp;
        if (strcmp(str, tmp->name) == 0)
            return tmp->location;
        tmp = tmp->next;
    }
    tmp = (link *)malloc(sizeof(link));
    tmp->name = (char *)malloc(sizeof(char) * strlen(str));
    strcpy(tmp->name, str);
    tmp->location = count++;
    tmp->next = NULL;
    before->next = tmp;
    return tmp->location;
}

void roadInput(int A, int B, road *roads[], int distance)
{
    if (A == B)
        return;
    road *search = roads[A];
    while (search != NULL)
    {
        if (search->location == B)
        {
            search->distance = Min(distance, search->distance);
            break;
        }
        search = search->next;
    }
    search = roads[B];
    while (search != NULL)
    {
        if (search->location == A)
        {
            search->distance = Min(distance, search->distance);
            break;
        }
        search = search->next;
    }
    if (roads[A] == NULL)
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = B;
        newroad->distance = distance;
        newroad->next = NULL;
        roads[A] = newroad;
    }
    else
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = B;
        newroad->distance = distance;
        newroad->next = NULL;
        road *tmp = roads[A];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newroad;
    }
    if (roads[B] == NULL)
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = A;
        newroad->distance = distance;
        newroad->next = NULL;
        roads[B] = newroad;
    }
    else
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = A;
        newroad->distance = distance;
        newroad->next = NULL;
        road *tmp = roads[B];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newroad;
    }
}

link *Input(road *roads[], int m)
{
    count = 0;
    char name_1[20];
    char name_2[20];
    int distance;
    scanf("%s %s %d", name_1, name_2, &distance);
    link *head = (link *)malloc(sizeof(link));
    head->location = count++;
    head->name = (char *)malloc(sizeof(char) * strlen(name_1));
    strcpy(head->name, name_1);
    head->next = NULL;
    int A = 0, B = search(name_2, head);
    roadInput(A, B, roads, distance);
    int i = 1;
    for (; i < m; i++)
    {
        int dis;
        char x[20];
        char y[20];
        scanf("%s %s %d", x, y, &dis);
        roadInput(search(x, head), search(y, head), roads, dis);
    }
    return head;
}
void updateDistances(dis *Distances[], road *cities[], int location)
{
    road *tmp = cities[location];
    while (tmp != NULL)
    {
        if (Distances[location]->Sflag == 1)
        {
            Distances[tmp->location]->Sdis = Min(Distances[tmp->location]->Sdis, tmp->distance + Distances[location]->Sdis);
            if (Distances[tmp->location]->Sdis == (tmp->distance + Distances[location]->Sdis))
            {
                Distances[tmp->location]->Sbefore = location;
                Distances[tmp->location]->Sbefore = location;
            }
        }
        else
        {
            Distances[tmp->location]->Edis = Min(Distances[tmp->location]->Edis, tmp->distance + Distances[location]->Edis);
            if (Distances[tmp->location]->Edis == (tmp->distance + Distances[location]->Edis))
            {
                Distances[tmp->location]->Ebefore = location;
                Distances[tmp->location]->Ebefore = location;
            }
        }
        tmp = tmp->next;
    }




    int before[count];
    int i=0;
    for (i = 0; i < count; i++)
    {
        before[i] = 1;
    }
    for (i = 0; i < count; i++)
    {
        if (Distances[i]->Eflag == 1 || Distances[i]->Sflag == 1)
        {
            before[i] = 0;
        }
    }
    startMin=100000;
    for(i=0;i<count;i++)
    {
        if(before[i])
        {
            startMin=Min(startMin,Distances[i]->Sdis);
        }
    }
    endMin = 100000;
    for (i = 0; i < count; i++)
    {
        if (before[i])
        {
            endMin = Min(endMin, Distances[i]->Edis);
        }
    }
}
int getMinlocation(dis *Distances[])
{
    int min = 100000;
    int minLocation = count;
    int i = 0;
    int flag = 0;
    for (; i < count; i++)
    {
        if (Distances[i]->Sflag == 0 && Distances[i]->Sdis < min)
        {
            minLocation = i;
            min = Distances[i]->Sdis;
            flag = 1;
        }
        if (Distances[i]->Eflag == 0 && Distances[i]->Edis < min)
        {
            minLocation = i;
            min = Distances[i]->Edis;
            flag = -1;
        }
    }
    if (flag == 1)
        Distances[minLocation]->Sflag = 1;
    else
        Distances[minLocation]->Eflag = 1;
    return minLocation;
}
int computeMindistance(road *cities[], int start, int end)
{
    times=0;
    startMin=100000;
    endMin=100000;
    dis *Distances[count];
    int i = 0;
    for (; i < count; i++)
    {
        dis*newdis=(dis*)malloc(sizeof(dis));
        Distances[i]=newdis;
        Distances[i]->Edis = 100000;
        Distances[i]->Sdis = 100000;
        Distances[i]->Ebefore = -1;
        Distances[i]->Sbefore = -1;
        Distances[i]->Eflag = 0;
        Distances[i]->Sflag = 0;
    }
    Distances[start]->Sflag = 1;
    Distances[start]->Sdis = 0;
    Distances[end]->Eflag = 1;
    Distances[end]->Edis = 0;
    updateDistances(Distances, cities, start);
    updateDistances(Distances, cities, end);
    while (1)
    {
        int newInput = getMinlocation(Distances);
        if (Distances[newInput]->Sflag == 1 && Distances[newInput]->Eflag == 1)
        {
            if (Distances[newInput]->Edis + Distances[newInput]->Sdis <= (startMin + endMin))
            {
                return(Distances[newInput]->Sdis+Distances[newInput]->Edis);
            }
            else
            {
                Distances[newInput]->Sdis=100000;
                Distances[newInput]->Edis=100000;
            }
        }
        updateDistances(Distances, cities, newInput);
        times++;
    }
}
link *getName(int location, link *head)
{
    link *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->location == location)
            return tmp;
        tmp = tmp->next;
    }
    return tmp;
}
int main()
{
    int n = 100, m;
    scanf("%d", &m);
    road *cities[n];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cities[i] = NULL;
    }
    link *head = Input(cities, m);
    char *start = "成都";
    char *end = "江达";
    int s = search(start, head);
    int e = search(end, head);
    computeMindistance(cities, s, e);
    printf("%d", computeMindistance(cities, s, e));
    // i = e;
    // while (1)
    // {
    //     if (i == s)
    //     {
    //         printf(" %s\n", getName(i, head)->name);
    //         break;
    //     }
    //     printf(" %s <--", getName(i, head)->name);
    //     i = before[i];
    // }
    return 0;
}