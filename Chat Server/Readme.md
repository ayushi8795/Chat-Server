Chat Server Application

Client - server application that can chat(send and receive data) to each other.

Instruction to Run:

Platform: Linux with gcc compiler
Compiling server and client: gcc filename.c -o filename
Running the server: ./filename portno
Running the client: ./filename host portno
clossing connection between client and socket: exit command in message
stopping client or server in between the process :ctrl+c.
Note: The portno should be same for client and server.
      Server should be run first and then client.
      Message passed should be without spaces.
	  host is the ip address of the server

Implemented and Tested:

1)single client and server
2)Program run on same machine with two terminal windows 
3)For stopping the program both server and client can stop the program sending "exit" as message
4)Tested on local machine and remote.cs.binghamton

Not implemented and Not Tested:

1)Multiple client 
2)Not tested on two different computers in lab G7 and Q22.
 
 
*Unable to get thread and select() concept to implement multiple client


Description of code

Server:

1)Begining with the main function the loop will test if the argument given by the user is correct or not and appropriate action will be taken.
2)argv[1] value will be assigned to the variable portno. 
3)socket named serversocket will be created and tested if it is correctly created or not.
4)setsockopt will help to reuse the port.
5)memset is use to fill block with particular value.
6)using bind() the socket created is binded to our specified ip and port and checked if it is binded correctly or not.
7)listen() is use for telling the socket that it should be capable to accept the request from client.
8)accept() is uded to accept the client request(data connection) and to carry out communication.
9)recv() and Send() is use to communicate(data transfer) with client
recv() will receive the message from client and later send() the message to the client.
10)while reciving and sending the data the message will be compared with "exit" string if it matches then the program will exit and the connection will be closed. 
11)countinue will carry out the next instruction in the code.
12)close() will close the socket created in step 3) above.

Client:

1)Begining with the main function the loop will test if the argument given by the user is correct or not and appropriate action will be taken.
2)argv[1] value will be assigned to the variable host and argv[2] will be assigned to portno. 
3)socket named clientsocket will be created and tested if it is correctly created or not. 
4)memset is use to fill block with particular value.
5)gethostbyname() is used to assign host by name to the server.
6)memcpy() is used to copy host's address to server address structure.
7)connect() is use to connect the client to server and condition is checked if it is true.
10)recv() and Send() is use to communicate(data transfer) with client
recv() will receive the message from client and later send() the message to the client.
11)while reciving and sending the data the message will be compared with "exit" string if it matches then the program will exit and the connection will be closed. 
12)countinue will carry out the next instruction in the code
13)close() will close the socket created in step 3) above.
























 
