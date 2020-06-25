#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>

int in=0;
static int timerExp=0;
void timerExpireFunc(union sigval arg)
{

	printf("Timer is expired\n");
	timerExp=1;
#if 1	
	char buf=49;
	if(write(STDIN_FILENO,&buf,1)==-1)
	{
	printf("failed -->write\n");
	}
	write(STDOUT_FILENO,'\n',1);
	in=1;
#endif

}

void getTime(timer_t timerid)
{


	struct itimerspec itimer;
	int remSec=-1;
	//while(timerExp!=1)
	while(remSec!=0)
	{
	timer_gettime(timerid,&itimer);
	remSec=itimer.it_value.tv_sec;
	printf("remaining time::%d\n",remSec);
		//printf("wait....\n");
	}
	printf("Timer expired\n");
	
}

void setTime(timer_t timerid,int value)
{


	struct itimerspec itimer;
	itimer.it_value.tv_sec=value;
	itimer.it_interval.tv_sec=0;
	itimer.it_value.tv_nsec=0;
	itimer.it_interval.tv_nsec=0;
	if(timer_settime(timerid,0,&itimer,NULL)!=0)
	{

		printf("failed to set timer\n");
		exit(-1);
	}
//	timerExp=1;
//	printf("Timer expired\n");
	
}
int main()
{


	struct sigevent eventbuf;
	struct itimerspec timerbuf;

	timer_t timerid;

	//eventbuf.sigev_notify=SIGEV_NONE;//no notification ,monitor using gettimer here we are using getTime function
	eventbuf.sigev_notify=SIGEV_THREAD;
	eventbuf.sigev_signo=0;
	eventbuf.sigev_value.sival_int=0;
	eventbuf.sigev_notify_function=timerExpireFunc;
	eventbuf.sigev_notify_attributes=NULL;


	timerbuf.it_interval.tv_sec=5;
	timerbuf.it_value.tv_sec=5;

	timerbuf.it_interval.tv_nsec=0;
	timerbuf.it_value.tv_nsec=0;





	if(timer_create(CLOCK_REALTIME,&eventbuf,&timerid)!=0)
	{

		printf("failed to create timer\n");
		exit(-1);
	}

	printf("TimerID::%ld\n",timerid);


	if(timer_settime(timerid,0,&timerbuf,NULL)!=0)
	{

		printf("failed to set timer\n");
		exit(-1);
	}

	
	//getTime(timerid);
	
	#if 1
	char buf=0;
	while(timerExp!=1)
	{
		printf("want  to stop timer::");
		int numRead=read(STDIN_FILENO,&buf,1);
		(numRead>0&&buf==49)?setTime(timerid,0):printf("timer is running...\n");
		printf("wait....\n");
	}
	#endif
	printf("Sucess\n");

	return 0;
}
