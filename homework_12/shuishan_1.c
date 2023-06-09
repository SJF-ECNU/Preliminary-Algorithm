#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct link
{
    int distance;
    int location;
    struct link *next;

} link;
typedef struct node
{
    struct link *dis;
} node;
int Min(int x, int y)
{
    if (x >= y)
        return y;
    return x;
}
int GetMinVillage(int distance[], int n)
{
    int i = 0;
    int min = 1000;
    int location = 0;
    for (; i < n; i++)
    {
        if (distance[i] != 0 && distance[i] < min)
        {
            location = i;
            min = distance[i];
        }
    }
    return location;
}
int GetMinDistance(node *villages[], int n)
{
    int sum = 0;
    int *distance = (int *)malloc(sizeof(int));
    int i = 0;
    for (i = 0; i < n; i++)
        distance[i] = 1000;
    distance[0] = 0;
    link *start = villages[0]->dis;
    while (start != NULL)
    {
        distance[start->location] = Min(start->distance, distance[start->location]);
        start = start->next;
    }
    for (i = 0; i < n - 1; i++)
    {
        int newInput = GetMinVillage(distance, n);
        sum += distance[newInput];
        distance[newInput] = 0;
        link *tmp = villages[newInput]->dis;
        while (tmp != NULL)
        {
            distance[tmp->location] = Min(tmp->distance, distance[tmp->location]);
            tmp = tmp->next;
        }
    }
    return sum;
}
void inputDis(node *village, int locate, int D)
{
    link *tmp = village->dis;
    if (tmp == NULL)
    {
        tmp->distance = D;
        tmp->location = locate;
        tmp->next = NULL;
        return;
    }
    link *nexttmp = tmp->next;
    while (nexttmp != NULL)
    {
        tmp = nexttmp;
        nexttmp = nexttmp->next;
    }
    link *newdis = (link *)malloc(sizeof(link));
    newdis->next = NULL;
    newdis->distance = D;
    newdis->location = locate;
    tmp->next = newdis;
    return;
}
int main()
{
    int n, m, i;
    scanf("%d", &n);
    scanf("%d", &m);
    node *villages[1000];
    for (i = 0; i < n; i++)
    {
        node *newVillage = (node *)malloc(sizeof(node));
        newVillage->dis = NULL;
    }
    for (i = 0; i < m; i++)
    {
        int x = 0;
        int y = 0;
        int D = 0;
        scanf("%d%d%d", &x, &y, &D);
        inputDis(villages[x-1],y-1,D);
        inputDis(villages[y-1],x-1,D);        
    }
    printf("%d\n",GetMinDistance(villages,n));
    return 0;
}
