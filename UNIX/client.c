#include "socket.h"

st_socketConfigType gsocketclientconfig=
{
	.domain=AF_UNIX,
	.stream=SOCK_STREAM,
	.protocol=0

};

int main()
{

	int clientFd=socket(gsocketclientconfig.domain,gsocketclientconfig.stream,gsocketclientconfig.protocol);

	if(clientFd!=-1)
	{
		PRINT_SOCKET_LOG("socket() success");

		memset(&gsocketclientconfig.socketaddr,0,sizeof(struct sockaddr));

		gsocketclientconfig.socketaddr.sa_family=gsocketclientconfig.domain;
		strncpy(gsocketclientconfig.socketaddr.sa_data,SOCK_PATH,sizeof(SOCK_PATH)-1);

		if(connect(clientFd,&gsocketclientconfig.socketaddr,sizeof(gsocketclientconfig.socketaddr))!=-1)
		{
				int BUF_SIZE=512;
			char buf[BUF_SIZE];
			int numRead;

			PRINT_SOCKET_LOG("connect() success");
			while((numRead=read(STDIN_FILENO,buf,BUF_SIZE))>0)
			{

				if(write(clientFd,buf,numRead)!=numRead)
				{
					PRINT_SOCKET_LOG("write failed");
				}
				else
				{
					PRINT_SOCKET_LOG("write success");
				}

			}

			close(clientFd);



		}
		else
		{
			PRINT_SOCKET_LOG("connect() failed");
		}



	}
	else
	{
		PRINT_SOCKET_LOG("socket() failed");
	}



	return 0;
}
