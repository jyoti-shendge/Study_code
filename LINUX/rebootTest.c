#include<stdio.h>
#include<unistd.h>
#include<linux/reboot.h>


int main()
{




int data=reboot(RB_AUTOBOOT);


return 0;
}
