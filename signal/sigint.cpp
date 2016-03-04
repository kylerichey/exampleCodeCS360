#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>

void handler (int status);   /* definition of signal handler */
int  counter = 0;

main()
{
	int rc1, rc2;

	// First set up the signal handler
	struct sigaction sigold, signew;

	signew.sa_handler=handler;
	sigemptyset(&signew.sa_mask);
	sigaddset(&signew.sa_mask,SIGINT);
	signew.sa_flags = SA_RESTART;
	sigaction(SIGINT,&signew,&sigold);
	sigaction(SIGINT,&signew,&sigold);
	sigaction(SIGINT,&signew,&sigold);


	for(;;);

	exit(0);
}

void handler (int status)
{
	printf("received signal %d\n",status);
}
