#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define EXAMPLE_PORT 6000
//#define EXAMPLE_GROUP "239.0.0.1"


int main(int argc, char* argv[])    
{
    struct sockaddr_in addr;
    int addrlen, sock, cnt, port;
    struct ip_mreq mreq;
    float value;
    char group[15];

    if(argc != 3)
    {
        printf("Wrong number of arguments: ./consumer <addr> <port>\n");
        exit(1);
    }

    port = atoi(argv[2]);

    strcpy(group, argv[1]);

    /* set up socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) 
    {
        perror("socket");
        exit(1);
    }


    bzero((char *)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    addrlen = sizeof(addr);

    int reuse = 1;

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (int *) &reuse, sizeof(reuse));

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) 
    {        
        perror("bind");
	    exit(1);
    }    
      
    mreq.imr_multiaddr.s_addr = inet_addr(group);         
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
    
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) 
    {
	    perror("setsockopt mreq");
	    exit(1);
    }         
      
    while (1) 
    {
 	    recvfrom(sock, &value, sizeof(float), 0, (struct sockaddr *) &addr, &addrlen);
	    
	 
        printf("Value received: %.2f\n", value);
    }

}