#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

     /*Variables*/
	 int sock; //return the value of socket function
	 struct sockaddr_in server;
	 int mysock; // the socket that will hold the connection when the 
               //client connect to it 
     char buff[1024];//a buffer that holds the deta 
     int rval; //return value for the function that calculate
                // the lengh of the strean sent in the buffer


	/*Create socket*/
     sock = socket(AF_INET, SOCK_STREAM, 0); //TCP IP socket 
     if(sock < 0 ){
     	perror("Failed to create socket");
     	exit(1);
     }
      
      server.sin_family = AF_INET;
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_port = htons(5000);
     
	/*Call bind*/

      if(bind(sock, (struct sockaddr *)&server, sizeof(server)))
      {
           perror("bind failed");
           exit(1);
      }


	/*Listen*/
      listen (sock, 5);


	/*Accept*/
     do {

        mysock = accept(sock, (struct sockaddr *) 0, 0);
        if(mysock == -1){
        	perror("accept failed");

        }
        else
        {
          /*Treatment*/
        	memset(buff, 0, sizeof(buff));
        	if((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
        		perror("reading stream message error");
        	else if(rval == 0)
        		printf("Ending connection\n");
        	else
        		
                printf("MESSAGE RECEIVED FROM CLIENT : %s\n", buff);//print the 
                                                         //message
                                                        //received

              close(mysock);//close socket
        	
        }
     }while(1);


	return 0;
}