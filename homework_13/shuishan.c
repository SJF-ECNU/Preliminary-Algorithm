#include <stdio.h>
#include <stdlib.h>

typedef struct link
{
    struct link *next;
    int location;
    int price;
} link;
int Min(int A, int B)
{
    if (A <= B)
        return A;
    return B;
}

void roadInput(int A, int B, link *cities[], int price)
{
    if (A == B)
        return;
    link *search = cities[A];
    while (search != NULL)
    {
        if (search->location == B)
		{
			search->price=Min(price,search->price);
		}
        search = search->next;
    }
    if (cities[A] == NULL)
    {
        link *newroad = (link *)malloc(sizeof(link));
        newroad->location = B;
        newroad->price = price;
        newroad->next = NULL;
        cities[A] = newroad;
    }
    else
    {
        link *newroad = (link *)malloc(sizeof(link));
        newroad->location = B;
        newroad->price = price;
        newroad->next = NULL;
        link *tmp = cities[A];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newroad;
    }
}

void cityInput(link *cities[], int m)
{
    int i = 0;
    for (i = 1; i <= m; i++)
    {
        int A = 0, B = 0, price = 0;
        scanf("%d%d%d", &A, &B, &price);
        roadInput(A, B, cities, price);
    }
}

void updateDistances(int Prices[], link *cities[], int location)
{
    link *tmp = cities[location];
    while (tmp != NULL)
    {
        Prices[tmp->location] = Min(Prices[tmp->location], tmp->price + Prices[location]);
        tmp = tmp->next;
    }
}

int getMinlocation(int Prices[], int n, int flag[])
{
    int min = 100000;
    int minLocation = 0;
    int i = 1;
    for (; i <= n; i++)
    {
        if (flag[i] && Prices[i] < min)
        {
            minLocation = i;
            min = Prices[i];
        }
    }
    return minLocation;
}
int computeMindistance(link *cities[], int n)
{
    int Prices[n + 1];
    Prices[1] = 0;
    int i = 0;
    int flag[n + 1];
    flag[1] = 1;
    for (i = 2; i <= n; i++)
    {
        Prices[i] = 100000;
        flag[i] = 1;
    }
    updateDistances(Prices, cities, 1);
    while (1)
    {
        int newInput = getMinlocation(Prices, n, flag);
        if (newInput == 0)
            break;
        flag[newInput] = 0;
        updateDistances(Prices, cities, newInput);
    }
    if (Prices[n] == 100000)
        return -1;
    else
        return Prices[n];
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    link*cities[n+1];
    int i=0;
    for(i=1;i<=n;i++) cities[i]=NULL;
    cityInput(cities,m);
    printf("%d",computeMindistance(cities,n));
    return 0;
}