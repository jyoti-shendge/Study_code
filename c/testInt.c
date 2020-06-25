#include<stdio.h>

void printInt(int * num)
{
int n=100;
printf("Num::%d\n",*num);
*num=n;
printf("Num::%d\n",*num);
}

int main()
{

int var=10;
int *n;
n=&var;

printInt(n);

printf("Num::%d\n",*n);
return 0;
}
