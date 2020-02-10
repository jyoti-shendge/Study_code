#include "socket.h"

char toUpper(char ch)
{
#if 1
if(ch>=97&&ch<=122)
	return ch-32;
#endif
	return ch;
}

st_socketConfigType gsocketconfig=
{
	.domain=AF_UNIX,
	.stream=SOCK_DGRAM,
	.protocol=0,
};


int main()
{
	
	int clientFd;

	/*
	 *** create socket
	 */
	int socketFd=socket(gsocketconfig.domain,gsocketconfig.stream,gsocketconfig.protocol);

	if(socketFd!=-1)
	{

		PRINT_SOCKET_LOG("socket() success");



		#if 0
		if((access(SOCK_PATH,F_OK))==0)
		{
		remove(SOCK_PATH);
		PRINT_SOCKET_LOG("asdgjasd");
		}
		else
		{
		PRINT_SOCKET_LOG("failed access()");
		}
		#endif

		#if 1
		if(remove(SOCK_PATH)==-1&&errno!=ENOENT)
		PRINT_SOCKET_LOG("failed to remove");
		else
		PRINT_SOCKET_LOG("Sucess removing socket path");
		#endif

		memset(&gsocketconfig.socketaddr,0,sizeof(struct sockaddr));
		#if 1
		gsocketconfig.socketaddr.sa_family=gsocketconfig.domain;
		strncpy(gsocketconfig.socketaddr.sa_data,SOCK_PATH,sizeof(SOCK_PATH)-1);
		if(bind(socketFd,(struct sockaddr*)&gsocketconfig.socketaddr,sizeof(struct sockaddr))!=-1)
		{
			PRINT_SOCKET_LOG("bind() success");
			int BUF_SIZE=512;
			char buf[BUF_SIZE];
			int numBytes,i;
			struct sockaddr clientaddr;
			int len=sizeof(struct sockaddr);
			for(;;)
			{
			numBytes=recvfrom(socketFd,buf,sizeof(struct sockaddr),0,&clientaddr,&len);
			if(numBytes!=-1)
			{	
				PRINT_SOCKET_LOG("data from client::%s",buf);
				for(i=0;i<numBytes;i++)
				buf[i]=toUpper(buf[i]);
				buf[i]='\0';
				if(sendto(socketFd,buf,numBytes,0,&clientaddr,len)==-1)
				{
				PRINT_SOCKET_LOG("failed sendto()");
				}
			}
			else
			{
				PRINT_SOCKET_LOG("failed recvfrom()");
			}
			
			}	
		}
		else
		{
			if(errno==EADDRINUSE)
			PRINT_SOCKET_LOG("socket is already in use ");
			PRINT_SOCKET_LOG("bind() failed");
		}
		#endif


	}
	else
	{
		PRINT_SOCKET_LOG("socket() failed");
	}

	return 0;
}
