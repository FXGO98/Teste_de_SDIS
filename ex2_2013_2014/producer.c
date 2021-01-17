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
    int addrlen, sock, cnt, port, i;
    struct ip_mreq mreq;
    char message[50];
    char group[15];
    float *values;

    if(argc < 4)
    {
        printf("Missing arguments: ./producer <addr> <port> <val1> ... <valn>\n");
        exit(1);
    }

    port = atoi(argv[2]);

    strcpy(group, argv[1]);


    values = (float*)malloc(sizeof(float)*(argc-3));

    for(i=0; i<(argc-3); i++)
    {
        values[i] = atof(argv[i+3]);
    }

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



    /* send */
    addr.sin_addr.s_addr = inet_addr(group);
    
    for(i=0; i<argc-3; i++)
    {
	    //sprintf(message, "time is %-24.24s", ctime(&t));
	    printf("Value sent: %.2f\n", values[i]);
	    sendto(sock, &values[i], sizeof(float), 0,(struct sockaddr *) &addr, addrlen);
	     
	 
        sleep(1);
    }

    exit(1);
   
}
