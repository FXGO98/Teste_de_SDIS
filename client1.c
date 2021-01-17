#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80 
//#define PORT 8080 
//#define SA struct sockaddr 
void func(int sockfd) 
{ 
    char buff[MAX];
    float ans; 

    bzero(buff, sizeof(buff));

    strcpy(buff, "Send me the Average");

    printf("Sending Request to Server...\n"); 
    
    write(sockfd, buff, sizeof(buff));

    bzero(buff, sizeof(buff));

    read(sockfd, &ans, sizeof(ans));

    printf("Server Response: Average = %.2f\n", ans); 
    
} 
  
int main(int argc, char* argv[]) 
{ 
    int sockfd, connfd, port; 
    struct sockaddr_in servaddr, cli; 
    struct hostent *ip;
  
    if(argc != 3)
    {
        printf("Wrong number of arguments: ./client1 <addr> <port>\n");
        exit(1);
    }

    ip = gethostbyname(argv[1]);
    port = atoi(argv[2]);

    // socket create and varification 
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
    memcpy(&servaddr.sin_addr, ip->h_addr, ip->h_length); 
    servaddr.sin_port = htons(port); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 