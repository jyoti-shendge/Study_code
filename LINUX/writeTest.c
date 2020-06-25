#include<stdio.h>
#include<unistd.h>


int  main()
{

  char buf='0';
        if(write(STDIN_FILENO,&buf,1)==-1)
        {
        printf("failed -->write\n");
        }


return 0;
}
