#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MESSAGE "Message through the socket" //the message sent to the server

int main(int argc, char * argv[]){

     /*Variables*/
     int sock;
     struct sockaddr_in server;
     struct hostent *hp;
     char buff[1024];


     /*Create socket*/
     sock = socket(AF_INET, SOCK_STREAM, 0);//TCP IP socket
     if(sock < 0){

     	perror("socket failed");
     	exit(0);
     }

     server.sin_family = AF_INET;

     hp = gethostbyname(argv[1]); //ip adress of the interface

     if(hp == 0)
     {
        perror("gethostbyname failed");
        close(sock);
        exit(1);

     }
 

     memcpy(&server.sin_addr, hp->h_addr, hp->h_length);//copy in the memory
     server.sin_port = htons(5000);

     /*connect*/
     if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
     {
     	perror("connect failed");
     	close(sock);
     	exit(0);
     }
      
     /*send*/
     if(send(sock, MESSAGE, sizeof(MESSAGE), 0)< 0)
     {
     	perror("send failed");
     	close(sock);
     	exit(1);
     }
     else {
         printf("The Message was succecfuly sent \n"); 
     }
     
     close(sock);
	return 0;
}