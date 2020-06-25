#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include<net/if.h>
#include<linux/can.h>
#include<linux/can/raw.h>

#define PORT "vcan0"

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;


typedef struct CANBasicPacketTag
{
    uint16_t canid;
    uint8_t candlc;
    uint8_t candata[8];    
}CANBasicPacketType;




void CANSocketSend(CANBasicPacketType packet,int socketId)
{
struct can_frame framebuf;

framebuf.can_id=packet.canid;
framebuf.can_dlc=packet.candlc;
memcpy(&framebuf.data[0],packet.candata[0],8);

int wbytes=write(socketId,&framebuf,sizeof(framebuf));

if(wbytes==sizeof(framebuf))
{
printf("success -->can send\n ");
}






}
int main()
{


int socketId=socket(PF_CAN,SOCK_RAW,CAN_RAW);
if(socketId==-1)
{
printf("failed to create socket\n");
exit(-1);

}
printf("SocketId::%d\n",socketId);

struct sockaddr_can addr;
addr.can_family=PF_CAN;


struct ifreq ir;
strcpy(ir.ifr_name,PORT);

if(ioctl(socketId,SIOCGIFINDEX,&ir)<0)
{
perror("ioctl\n");
exit(-1);
}
addr.can_ifindex=ir.ifr_ifindex;

if(bind(socketId,(struct sockaddr*)&addr,sizeof(addr))<0)	
{
perror("bind\n");
exit(-1);
}



return 0;
}
