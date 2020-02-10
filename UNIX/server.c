#include "socket.h"


st_socketConfigType gsocketconfig=
{
	.domain=AF_UNIX,
	.stream=SOCK_STREAM,
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


		/* 
		 *** initialize all elements of socket struct to 0
		 */

		if(access(SOCK_PATH,F_OK)!=-1)
		{
		unlink(SOCK_PATH);
		}
			
		memset(&gsocketconfig.socketaddr,0,sizeof(struct sockaddr));
		#if 1
		gsocketconfig.socketaddr.sa_family=gsocketconfig.domain;
		strncpy(gsocketconfig.socketaddr.sa_data,SOCK_PATH,strlen(SOCK_PATH));
		if(bind(socketFd,(struct sockaddr*)&gsocketconfig.socketaddr,sizeof(struct sockaddr))!=-1)
		{
			PRINT_SOCKET_LOG("bind() success");
			if(listen(socketFd,BACKLOG)!=-1)
			{
			PRINT_SOCKET_LOG("listen() success");
			int BUF_SIZE=512,numBytes;
			char buf[BUF_SIZE];
				for(;;)
				{
				clientFd=accept(socketFd,NULL,NULL);
				if(clientFd!=-1)
				{
					while((numBytes=read(clientFd,buf,BUF_SIZE))>0)	
					{	
						if(write(STDOUT_FILENO,buf,numBytes)!=numBytes)
							PRINT_SOCKET_LOG("failed to print data");
					}
					close(clientFd);
				}	
				else
				{
					PRINT_SOCKET_LOG("failed accept()");
					break;
				}
				
				}
			}
			else
			{
			PRINT_SOCKET_LOG("listen() failed");
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
