#include "socket.h"

st_socketConfigType gsocketclientconfig=
{
	.domain=AF_UNIX,
	.stream=SOCK_DGRAM,
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
		//snprintf(gsocketclientconfig.socketaddr.sa_data,sizeof(gsocketclientconfig.socketaddr.sa_data),"/tmp/u_client.%ld",(long)getpid());
		snprintf(gsocketclientconfig.socketaddr.sa_data,14,"/tmp/u_client");

		if((bind(clientFd,&gsocketclientconfig.socketaddr,sizeof(struct sockaddr)))!=-1)
		{

			struct sockaddr serversockaddr;
			memset(&serversockaddr,0,sizeof(struct sockaddr));
			serversockaddr.sa_family=AF_UNIX;
			strncpy(serversockaddr.sa_data,SOCK_PATH,sizeof(SOCK_PATH)-1);
			int j=0;
			int BUF_SIZE=512;
			char buf[BUF_SIZE];
			strcpy(buf,"Hello jyoti");
			int numRead;
	
			if((sendto(clientFd,buf,strlen(buf),0,(struct sockaddr*)&serversockaddr,sizeof(struct sockaddr)))==strlen(buf))
			{
			char resp[BUF_SIZE];
			numRead=recvfrom(clientFd,resp,BUF_SIZE,0,NULL,NULL);
			if(numRead==-1)
			{
			PRINT_SOCKET_LOG("failed to receive responce from server");
			}
			else
			{
			PRINT_SOCKET_LOG("Received DATA::%s",resp);
			}
			}
			else
			{
			PRINT_SOCKET_LOG("sendto() failed");
			}

			#if 0
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
			#endif

			close(clientFd);



		}
		else
		{
			PRINT_SOCKET_LOG("bind() failed");
		}



	}
	else
	{
		PRINT_SOCKET_LOG("socket() failed");
	}



	return 0;
}
