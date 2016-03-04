#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <iostream>

#define SOCKET_ERROR        -1
#define BUFFER_SIZE         10000
#define HOST_NAME_SIZE      255
#define NSOCKETS 10

int  main(int argc, char* argv[])
{
	struct timeval oldtime[NSOCKETS];
struct timeval newtime[NSOCKETS];
    int hSocket[NSOCKETS];                 /* handle to socket */
    struct hostent* pHostInfo;   /* holds info about a machine */
    struct sockaddr_in Address;  /* Internet socket address stuct */
    long nHostAddress;
    char pBuffer[BUFFER_SIZE];
    unsigned nReadAmount;
    char strHostName[HOST_NAME_SIZE];
    int nHostPort;

    if(argc < 3)
      {
        printf("\nUsage: client host-name host-port\n");
        return 0;
      }
    else
      {
        strcpy(strHostName,argv[1]);
        nHostPort=atoi(argv[2]);
      }

    printf("\nMaking a socket");
    /* make a socket */
	for(int i = 0; i < NSOCKETS; i++) {
	    hSocket[i]=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		if(hSocket[i] == SOCKET_ERROR)
		{
			printf("\nCould not make a socket\n");
			return 0;
		}
	}

    /* get IP address from name */
    pHostInfo=gethostbyname(strHostName);
    /* copy address into long */
    memcpy(&nHostAddress,pHostInfo->h_addr,pHostInfo->h_length);

    /* fill address struct */
    Address.sin_addr.s_addr=nHostAddress;
    Address.sin_port=htons(nHostPort);
    Address.sin_family=AF_INET;

	int epollFD = epoll_create(1);
	// Send the requests and set up the epoll data
	for(int i = 0; i < NSOCKETS; i++) {
		/* connect to host */
		if(connect(hSocket[i],(struct sockaddr*)&Address,sizeof(Address)) 
		   == SOCKET_ERROR)
		{
			printf("\nCould not connect to host\n");
			return 0;
		}
		char request[] = "GET /test.html HTTP/1.0\r\n\r\n";

	    	write(hSocket[i],request,strlen(request));
		struct epoll_event event;
		event.data.fd = hSocket[i];
		event.events = EPOLLIN;
		int ret = epoll_ctl(epollFD,EPOLL_CTL_ADD,hSocket[i],&event);
		if(ret)
			perror ("epoll_ctl");
		gettimeofday(&oldtime[i],NULL);
	}
	for(int i = 0; i < NSOCKETS; i++) {
		struct epoll_event event;
		int rval = epoll_wait(epollFD,&event,1,-1);
		if(rval < 0)
			perror("epoll_wait");
		read(event.data.fd,pBuffer,BUFFER_SIZE);
		gettimeofday(&newtime[i], NULL);
		double usec = (newtime[i].tv_sec - oldtime[i].tv_sec)*(double)1000000+(newtime[i].tv_usec-oldtime[i].tv_usec);
		std::cout << "Time "<<usec/1000000<<std::endl;
		
		printf("got from %d\n",event.data.fd);

		printf("\nClosing socket\n");
		/* close socket */                       
		if(close(hSocket[i]) == SOCKET_ERROR)
		{
			printf("\nCould not close socket\n");
			return 0;
		}
	}
}
