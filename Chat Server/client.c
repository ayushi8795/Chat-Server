#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

int main (int argc,char* argv[])
{

	int clientsock,portno,len,n,m;
	struct sockaddr_in myaddr; //our address of socket
	char buffer[1024],message[1024];
	char host[100];
	struct hostent *server;//host information
	struct sockaddr_in servaddr;//server address
	char ip[INET_ADDRSTRLEN];
	if(argc<3)
	{

		fprintf(stderr,"usage %s hostname port\n" , argv[0]);
		exit(0);
	}
	//getting port no as 3rd argument
	portno = atoi(argv[2]);
	strcpy(host,argv[1]);
	//checking if socket can be created and creating it 
	//AF_INET -> internet address family 
	//SOCK_STREAM for sequenced,reliable,two-way byte stream
	if((clientsock =socket(AF_INET , SOCK_STREAM , 0))<0)
	{
		perror("cannot create socket");
		return 0;
	}
	printf("1)client socket created\n");
	//INADDR_ANY is the ip address and 0 is the socket
	//inet_addr is used to connect the client ans server
	//htonl converts long interger to network representation(hostbyte order to network byte order 4 byte)
	//htons converts short integer to network represenation(2 byte)
	//fill in server data and address 
	memset((char *)&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(portno);
	servaddr.sin_addr.s_addr= inet_addr("host");
	//servaddr.sin_addr.s_addr= htonl(INADDR_ANY);
	//look up the address of the server given its name
	server = gethostbyname(host);
	if(!server)
	{

		fprintf(stderr,"could not obtain the address %s\n",argv[1]);
		return 0;
	}
	//put host's address into the server address structure
	//h_addr_list[] == list of address from server
	memcpy((void *)&servaddr.sin_addr,server->h_addr_list[0], server->h_length);
	//connect to server
	if (connect(clientsock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{

		perror("connection failed\n");
		return 0;
	}	
	inet_ntop(AF_INET, (struct sockaddr *)&servaddr, ip, INET_ADDRSTRLEN);
	printf("3)connected to server\n");
		while(1)
		{
    		
    		if(1)
    		{
    			if((n=strcmp(buffer,"exit"))== 0 || (m =strcmp(message,"exit"))==0)
    			{
    					printf("disconection...\n");
    					exit(1);
    			}
    			//sending message to client
				printf("\nenter message to send to server:");
				scanf("%s",buffer);
				send(clientsock,buffer,sizeof(buffer),0);
				if((n=strcmp(buffer,"exit"))== 0 || (m =strcmp(message,"exit"))==0)
    			{
    					printf("disconection...\n");
    					exit(1);
    			}
    			//receiver data from server
				recv(clientsock,&message,sizeof(message),0);
				//print out servers response
				printf("\ndata receive from server:%s\n",message);	
    		}
    		continue;
    		close(clientsock);
    		
  			
    	}	
return 0;
}