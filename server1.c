#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h> 
#define MAX 80
  
// Function designed for chat between client and server. 
void func(int sockfd, float average) 
{ 
    char buff[MAX]; 
    
    // infinite loop for chat  
    bzero(buff, MAX); 

    // read the message from client and copy it in buffer 
    read(sockfd, buff, sizeof(buff)); 
    // print buffer which contains the client contents 
    printf("Request from the Client: %s\n", buff); 
    
    bzero(buff, MAX); 
    // and send that buffer to client 
    write(sockfd, &average, sizeof(average)); 

    printf("Sending answer to client...\n");    
    
} 
  
// Driver function 
int main(int argc, char* argv[]) 
{ 
    int sockfd, connfd, len, port;
    float average;
    struct sockaddr_in servaddr, cli;

    if(argc != 3)
    {
        printf("Wrong number of arguments: ./server1 <port> <average>\n");
        exit(1);
    } 

    port = atoi(argv[1]);
    average = atof(argv[2]);
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    while(1)
    {
        // Now server is ready to listen and verification 
        if ((listen(sockfd, 5)) != 0) { 
            printf("Listen failed...\n"); 
            exit(0); 
        } 
        else
            printf("Server listening..\n"); 
        len = sizeof(cli); 
    
        // Accept the data packet from client and verification 
        connfd = accept(sockfd, (struct sockaddr*)&cli, &len); 
        if (connfd < 0) { 
            printf("server acccept failed...\n"); 
            exit(0); 
        } 
        else
            printf("server acccept the client...\n"); 
    
        // Function for chatting between client and server 
        func(connfd, average); 
    
        // After chatting close the socket 
        close(connfd);
    }
} 