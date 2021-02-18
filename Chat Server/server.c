#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <errno.h>
int main (int argc,char* argv[])
{
	printf("\n");
	//declaration
	int serversock,portno,newsocket,svc,n,m;
	int rqst;//socket accepting the request
	struct sockaddr_in myaddr;//address of this server
	struct sockaddr_in client_addr;//address of client
	socklen_t alen;//length of address structure
	char buffer[1024] , message[1024];
	int sockoptval = 1;
	//checking for port number
	if(argc<2 || argc>2)
	{

		printf("please put port number or else too many arguments\n");
		exit(1);
	}
	portno = atoi(argv[1]);
	//checking if socket can be created and creating it 
	//AF_INET -> internet address family 
	//SOCK_STREAM for sequenced,reliable,two-way byte stream
	if((serversock = socket(AF_INET , SOCK_STREAM , 0))<0)
	{
		perror("cannot create socket");
		return 0;
	}
		printf("1)socket created\n");
	// allow immediate reuse of the port
	setsockopt(svc, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int));
	//bind to an arbitary address as this is client side 
	//INADDR_ANY is the ip address and 0 is the socket
	//htonl converts long interger to network representation(hostbyte order to network byte order 4 byte)
	//htons converts short integer to network represenation(2 byte)
	memset((char *)&myaddr,0,sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr= htonl(INADDR_ANY);
	myaddr.sin_port = htons(portno);
	//bind the socket to our specified IP and port
	if(bind(serversock,(struct sockaddr *)&myaddr,sizeof(myaddr))<0)
	{

		perror("cannot bind");
		return 0;
	}
	printf("2)bind to port\n");
	//set socket for listening upto 10 clients not for accepting the data
	if(listen(serversock,10)<0)
	{

		perror("listen failed");
		exit(1);
	}
		printf("3)server listening......\n");	
		
	alen = sizeof(client_addr);
		//loops accepting connection request and perform service
		//accept()is use to accept the data connection
		//rqst is the integer to hold client socket
		rqst=accept(serversock,(struct sockaddr *)&client_addr, &alen);
		printf("connection accepted from %s:%d",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	while(1)	
	{	
		if(1)
		{
			//receiver data from client
			recv(rqst,&buffer,sizeof(buffer),0);
			//print out servers response
			printf("\ndata receive from client:%s\n",buffer);
			if((n=strcmp(buffer,"exit"))== 0 || (m =strcmp(message,"exit"))==0)
    			{
    					printf("disconection...\n");
    					exit(1);
    			}
			//sending message to client
			printf("\nenter message to send to client:");
			scanf("%s",message);
			send(rqst,message,sizeof(message),0);	
		}
		if((n=strcmp(buffer,"exit"))== 0 || (m =strcmp(message,"exit"))==0)
    		{
    			printf("disconection...\n");
    			exit(1);
    		}
		continue;
		close(serversock);
		
		
	}
	return 0;
}
