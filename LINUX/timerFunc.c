#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 1024

static int remSec;

static void handler(int sigNum)
{

	printf("Inside Handler\n");
	printf("remSec::%d\n",remSec);
}


int main()
{
	struct sigaction sa;
	sa.sa_handler=&handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;
	
	if(sigaction(SIGALRM||SIGINT,&sa,NULL)==-1)
	printf("failed-->sigaction\n");


	//alarm(2);
	remSec=sleep(5);
	printf("remSec::%d\n",remSec);

	printf("enter data\n");

	size_t numRead;
	char buf[BUF_SIZE];
	numRead=read(STDIN_FILENO,buf,BUF_SIZE);

	if(numRead==-1)
	{
		printf("Read failed\n");
	}
	else
	{
		printf("Data::%s\n",buf);
	}


	printf("After Timer\n");



	return 0;
}
