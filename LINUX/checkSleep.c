#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

void handler(int sigNum)
{

printf("Inside handler \t");
printf("signum::%d\n",sigNum);
}

int main()
{

signal(SIGALRM,handler);
printf("Inside main\n");

while(1)
{
sleep(1);

printf("Inside main\n");
}

return 0;
}
