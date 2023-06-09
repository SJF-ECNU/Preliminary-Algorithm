#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count;
int Min(int A, int B)
{
    if (A <= B)
        return A;
    return B;
}
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
void updateDistances(int Distances[], road *cities[], int location, int before[])
{
    road *tmp = cities[location];
    while (tmp != NULL)
    {
        Distances[tmp->location] = Min(Distances[tmp->location], tmp->distance + Distances[location]);
        if (Distances[tmp->location] == (tmp->distance + Distances[location]))
        {
            before[tmp->location] = location;
        }
        tmp = tmp->next;
    }
}
int getMinlocation(int Distances[], int n, int flag[])
{
    int min = 100000;
    int minLocation = n;
    int i = 0;
    for (; i < n; i++)
    {
        if (flag[i] && Distances[i] < min)
        {
            minLocation = i;
            min = Distances[i];
        }
    }
    return minLocation;
}
int computeMindistance(road *cities[], int before[], int start, int end)
{
    int n = count;
    int Distances[n];
    int i = 0;
    int flag[n];
    for (i = 0; i < n; i++)
    {
        Distances[i] = 100000;
        flag[i] = 1;
    }
    Distances[start] = 0;
    flag[start] = 0;
    updateDistances(Distances, cities, start, before);
    while (1)
    {
        int newInput = getMinlocation(Distances, n, flag);
        if (newInput == end)
            break;
        flag[newInput] = 0;
        updateDistances(Distances, cities, newInput, before);
    }
    return Distances[end];
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
    int before[n];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cities[i] = NULL;
        before[i] = 0;
    }
    link *head = Input(cities, m);
    char *start = "成都";
    char *end = "江达";
    int s = search(start, head);
    int e = search(end, head);
    printf("%d", computeMindistance(cities, before, s, e));
    i = e;
    while (1)
    {
        if (i == s)
        {
            printf(" %s\n", getName(i, head)->name);
            break;
        }
        printf(" %s <--", getName(i, head)->name);
        i = before[i];
    }
    return 0;
}