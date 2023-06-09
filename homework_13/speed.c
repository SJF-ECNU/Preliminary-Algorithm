#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count;
double Min(int A, int B)
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
    double time;
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

void roadInput(int A, int B, road *roads[], int distance, int speed)
{
    if (A == B)
        return;
    road *search = roads[A];
    while (search != NULL)
    {
        if (search->location == B)
        {
            search->time = Min((double)distance / (double)speed, search->time);
            break;
        }
        search = search->next;
    }
    search = roads[B];
    while (search != NULL)
    {
        if (search->location == A)
        {
            search->time = (double)distance / (double)speed;
            break;
        }
        search = search->next;
    }
    if (roads[A] == NULL)
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = B;
        newroad->time = (double)distance / (double)speed;
        newroad->next = NULL;
        roads[A] = newroad;
    }
    else
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = B;
        newroad->time = (double)distance / (double)speed;
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
        newroad->time = (double)distance / (double)speed;
        newroad->next = NULL;
        roads[B] = newroad;
    }
    else
    {
        road *newroad = (road *)malloc(sizeof(road));
        newroad->location = A;
        newroad->time = (double)distance / (double)speed;
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
    int speed_0;
    int distance;
    scanf("%s %s %d %d", name_1, name_2, &distance, &speed_0);
    link *head = (link *)malloc(sizeof(link));
    head->location = count++;
    head->name = (char *)malloc(sizeof(char) * strlen(name_1));
    strcpy(head->name, name_1);
    head->next = NULL;
    int A = 0, B = search(name_2, head);
    roadInput(A, B, roads, distance, speed_0);
    int i = 1;
    for (; i < m; i++)
    {
        int dis;
        char x[20];
        char y[20];
        int speed;
        scanf("%s %s %d %d", x, y, &dis, &speed);
        roadInput(search(x, head), search(y, head), roads, dis, speed);
    }
    return head;
}
void updateDistances(double times[], road *cities[], int location, int before[], int flag[])
{
    road *tmp = cities[location];
    while (tmp != NULL)
    {
        if (flag[tmp->location])
        {
            times[tmp->location] = Min(times[tmp->location], tmp->time + times[location]);
            if (times[tmp->location] - (tmp->time + times[location]) <= 0.1)
            {
                before[tmp->location] = location;
            }
        }
        tmp = tmp->next;
    }
}
int getMinlocation(double times[], int n, int flag[])
{
    double min = 100000;
    int minLocation = n;
    int i = 0;
    for (; i < n; i++)
    {
        if (flag[i] && times[i] < min)
        {
            minLocation = i;
            min = times[i];
        }
    }
    return minLocation;
}
double computeMindistance(road *cities[], int before[], int start, int end)
{
    int n = count;
    double times[n];
    int i = 0;
    int flag[n];
    for (i = 0; i < n; i++)
    {
        times[i] = 100000;
        flag[i] = 1;
    }
    times[start] = 0;
    flag[start] = 0;
    updateDistances(times, cities, start, before, flag);
    while (1)
    {
        int newInput = getMinlocation(times, n, flag);
        if (newInput == end)
            break;
        flag[newInput] = 0;
        updateDistances(times, cities, newInput, before, flag);
    }
    return times[end];
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
    char *start = "理塘"; //起点，可修改
    char *end = "江达";   //终点，可修改
    int s = search(start, head);
    int e = search(end, head);
    printf("%lf", computeMindistance(cities, before, s, e));
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