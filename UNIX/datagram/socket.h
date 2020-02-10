#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


#define SOCK_PATH "/tmp/unix_dsock"
//#define SOCK_PATH "org.DCS.Test" /**abstract name*/
#define BACKLOG 5

typedef struct socketConfig
{
	int domain;
	int stream;
	int protocol;

	struct sockaddr socketaddr;

}st_socketConfigType;



void PRINT_SOCKET_LOG(const char *fmt,...)
{
	char buf[256]={0};

	va_list args;

	sprintf(buf,"SOCKET LOG----->%s\n",fmt);

	va_start(args,fmt);
	vprintf(buf,args);
	va_end(args);


}
